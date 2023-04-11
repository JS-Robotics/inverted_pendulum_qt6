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
  std::thread* thread_;
  Simulator& simulator_;

  eprosima::fastdds::dds::DomainParticipant* participant_;


  RosPublisher<std_msgs::msg::Float32PubSubType>* publisher_cart_position_;
  std_msgs::msg::Float32 message_cart_position_;

  RosPublisher<geometry_msgs::msg::Vector3PubSubType>* publisher_pendulum_state_;
  geometry_msgs::msg::Vector3 message_pendulum_state;

  RosSubscriber<std_msgs::msg::Float32PubSubType, std_msgs::msg::Float32>* subscriber_torque_setpoint_;
  void topic_callback(const std_msgs::msg::Float32& msg) {
    std::cout << "Received value: " << msg.data() << std::endl;
  }

  void CleanDds();

};

#endif //INVERTED_PENDULUM_SIMULATION_COMMUNICATION_INCLUDE_COMMUNICATION_COMMUNICATION_H_
