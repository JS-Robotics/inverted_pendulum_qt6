//
// Created by ICraveSleep on 15-Mar-23.
//

#ifndef INVERTED_PENDULUM_SIMULATION_SIMULATOR_INCLUDE_SIMULATOR_H_
#define INVERTED_PENDULUM_SIMULATION_SIMULATOR_INCLUDE_SIMULATOR_H_

#include <mutex>
#include <chrono>
#include <thread>
#include <cmath>
#include "iostream"

class Simulator {
 public:
  Simulator();
  ~Simulator();

  bool Init();
  void Start();
  uint32_t Run();
  void Stop();

  void GetState(float &position, float &Angle);
  void GetStats(float &simulation_time, float &elapsed_time);

 private:
  bool thread_stop;
  std::mutex mutex_;
  float position_;
  float angle_;
  float time_step;
  std::chrono::time_point<std::chrono::steady_clock> time_start;
  std::chrono::time_point<std::chrono::steady_clock> time_end;
  float time_elapsed_;
  float simulation_time_;
  std::thread* thread_;


};

#endif //INVERTED_PENDULUM_SIMULATION_SIMULATOR_INCLUDE_SIMULATOR_H_
