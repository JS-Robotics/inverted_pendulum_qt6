//
// Created by ICraveSleep on 28.03.23.
//

#ifndef INVERTED_PENDULUM_SIMULATION_COMMUNICATION_INCLUDE_COMMUNICATION_COMMUNICATION_H_
#define INVERTED_PENDULUM_SIMULATION_COMMUNICATION_INCLUDE_COMMUNICATION_COMMUNICATION_H_

#include <mutex>
#include <chrono>
#include <thread>
#include "iostream"
#include "simulator/simulator.h"
#include "../../src/ros_subscriber.h"
#include "../../src/ros_publisher.h"
#include "../../src/message_types/Float32/Float32PubSubTypes.h"
#include "../../src/message_types/Vector3/Vector3PubSubTypes.h"


class Communication{
 public:
  Communication(Simulator& simulator);
  ~Communication();

  bool Init();
  void Start();
  uint32_t Run();
  void Stop();

 private:
  bool thread_stop;
  std::mutex mutex_;
  float time_step_;
  std::chrono::time_point<std::chrono::steady_clock> time_start_;
  std::chrono::time_point<std::chrono::steady_clock> time_end_;
  std::chrono::time_point<std::chrono::steady_clock> heart_beat_;
  std::thread* thread_;
  Simulator& simulator_;
  float pos_filtered_;
  float vel_filtered_;
  float kFilterAlpha = 0.5f;
  float kPi = 3.14159265359;
  float kHearBeatTimeout = 0.1f; // 100[ms]

  eprosima::fastdds::dds::DomainParticipant* participant_;


  RosPublisher<std_msgs::msg::Float32PubSubType>* publisher_cart_position_;
  std_msgs::msg::Float32 message_cart_position_;

  RosPublisher<geometry_msgs::msg::Vector3PubSubType>* publisher_pendulum_state_;
  geometry_msgs::msg::Vector3 message_pendulum_state;

  RosSubscriber<Communication, std_msgs::msg::Float32PubSubType, const std_msgs::msg::Float32&>* subscriber_torque_setpoint_;
  float torque_setpoint_;
  void TopicCallback(const std_msgs::msg::Float32& msg) {
    heart_beat_ =  std::chrono::steady_clock::now();
    torque_setpoint_ = msg.data();
//    std::cout << "Received value: " << msg.data() << std::endl;
  }

  void CleanDds();

};

#endif //INVERTED_PENDULUM_SIMULATION_COMMUNICATION_INCLUDE_COMMUNICATION_COMMUNICATION_H_
