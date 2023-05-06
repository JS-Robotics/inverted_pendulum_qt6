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

  void GetState(float &position, float &velocity, float &Angle);
  void GetStats(float &simulation_time, float &elapsed_time);
  void UpdateLoopAverage(float duration);
  void SetTorque(float torque);
  void UpdateSimulation();
  void ResetSimulation();

 private:
  bool thread_stop;
  std::mutex mutex_;
  float position_;
  float velocity_;
  float angle_;
  float time_step;
  std::chrono::time_point<std::chrono::steady_clock> time_start;
  std::chrono::time_point<std::chrono::steady_clock> time_end;
  float time_elapsed_;
  float simulation_time_;
  float step_;
  float torque_;
  std::thread* thread_;
  bool reset_simulation_;
  float kPi = 3.14159265359f;


};

#endif //INVERTED_PENDULUM_SIMULATION_SIMULATOR_INCLUDE_SIMULATOR_H_
