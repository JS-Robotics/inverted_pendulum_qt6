//
// Created by ICraveSleep on 28.03.23.
//

#include "communication/communication.h"

Communication::Communication(Simulator &simulator) : simulator_(simulator) {
  pos_filtered_ = 0.0f;
  vel_filtered_ = 0.0f;
  time_step_ = 0.0f;
  torque_setpoint_ = 0.0f;
  thread_ = nullptr;
  thread_stop = false;
  participant_ = nullptr;
  publisher_cart_state_ = nullptr;
  publisher_pendulum_state_ = nullptr;
  subscriber_torque_setpoint_ = nullptr;

  // Init messages to zero state
  message_cart_state_.x() = 0.0;
  message_cart_state_.y() = 0.0;
  message_cart_state_.z() = 0.0;
  message_pendulum_state.x() = 0.0;
  message_pendulum_state.y() = 0.0;
  message_pendulum_state.z() = 0.0;

}

Communication::~Communication() {
  CleanDds();
  Stop();
}

bool Communication::Init() {
  thread_stop = false;
  time_step_ = 0.02f; // 20[ms]
  time_start_ = std::chrono::steady_clock::now();
  time_end_ = time_start_;
  heart_beat_ = time_start_;

  eprosima::fastdds::dds::DomainParticipantQos turns_qos;
  turns_qos.name("pendulum_simulator_participant");
  eprosima::fastdds::dds::DomainId_t domain_id = 0;
  participant_ =
      eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->create_participant(domain_id, turns_qos);

  publisher_cart_state_ = new RosPublisher<geometry_msgs::msg::Vector3PubSubType>(participant_, "rt/ivp/cart_state");
  publisher_cart_state_->Init();

  publisher_pendulum_state_ =
      new RosPublisher<geometry_msgs::msg::Vector3PubSubType>(participant_, "rt/ivp/pendulum_state");
  publisher_pendulum_state_->Init();

  subscriber_torque_setpoint_ = new RosSubscriber<Communication,
                                                  std_msgs::msg::Float32PubSubType,
                                                  const std_msgs::msg::Float32 &>(&Communication::TopicCallback,
                                                                                  participant_,
                                                                                  "rt/ivp/force_setpoint",
                                                                                  this);
  subscriber_torque_setpoint_->Init();
  return true;
}

void Communication::Start() {
  thread_ = new std::thread(&Communication::Run, this);
}

uint32_t Communication::Run() {
  float position = 0;
  float velocity = 0;
  float angle = 0;
  float angle_old = 0;
  float delta_theta;

  while (!thread_stop) {
    time_start_ = std::chrono::steady_clock::now();
    simulator_.GetState(position, velocity, angle);

    delta_theta = angle - angle_old;
    // Turnover overflow check. Check if overflow is over the threshold 1.65
    if (delta_theta > 1.65 * kPi) {
      delta_theta = (angle - 2 * kPi) - angle_old;
    } else if (delta_theta < -1.65 * kPi) {
      delta_theta = (angle + 2 * kPi) - angle_old;
    }

    vel_filtered_ = kFilterAlpha * (delta_theta) / time_step_ + ((1 - kFilterAlpha) * vel_filtered_);
    angle_old = angle;

    pos_filtered_ = kFilterAlpha * angle + ((1 - kFilterAlpha) * pos_filtered_);

    // Publish cart position
    message_cart_state_.x() = position;
    message_cart_state_.y() = velocity;
    publisher_cart_state_->Publish(message_cart_state_);

    // Publish pendulum state
    message_pendulum_state.x() = pos_filtered_;
    message_pendulum_state.y() = vel_filtered_;
    publisher_pendulum_state_->Publish(message_pendulum_state);

    // Set torque from subscription
    if (std::chrono::duration<float>(time_start_ - heart_beat_).count() > kHearBeatTimeout) {
      simulator_.SetTorque(0.0f);
    } else {
      simulator_.SetTorque(torque_setpoint_);
    }

    time_end_ = std::chrono::steady_clock::now();
    float duration = std::chrono::duration<float>(time_end_ - time_start_).count();

    if (duration < time_step_) {
      std::this_thread::sleep_for(std::chrono::duration<float>(time_step_ - duration));
    }

  }

  return 0;
}

void Communication::Stop() {
  thread_stop = true;

  if (thread_) {
    std::cout << "Stopping communication thread" << std::endl;
    thread_->join();
    std::cout << "Joined communication thread" << std::endl;
    delete thread_;
    thread_ = nullptr;
    std::cout << "Communication thread deleted" << std::endl;
  }
}

void Communication::CleanDds() {

  if (publisher_cart_state_ != nullptr) {
    delete publisher_cart_state_;
    publisher_cart_state_ = nullptr;
  }

  if (publisher_pendulum_state_ != nullptr) {
    delete publisher_pendulum_state_;
    publisher_pendulum_state_ = nullptr;
  }

  if (participant_ != nullptr) {
    eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->delete_participant(participant_);
  }
}
