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

class Communication{
 public:
  Communication();
  ~Communication();

  bool Init();
  void Start();
  uint32_t Run();
  void Stop();

 private:
  bool thread_stop;
  std::mutex mutex_;
  std::chrono::time_point<std::chrono::steady_clock> time_start;
  std::chrono::time_point<std::chrono::steady_clock> time_end;
  std::thread* thread_;
};

#endif //INVERTED_PENDULUM_SIMULATION_COMMUNICATION_INCLUDE_COMMUNICATION_COMMUNICATION_H_
