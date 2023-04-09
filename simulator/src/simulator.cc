//
// Created by ICraveSleep on 15-Mar-23.
//

#include <cmath>

#include "simulator/simulator.h"

Simulator::Simulator() {
  step_ = 1;  // Must start at 1 to avoid zero division.
  thread_ = nullptr;
}

Simulator::~Simulator() {
  Stop();
}

bool Simulator::Init() {
  thread_stop = false;
  time_step = 1.f / 500.f;
  time_start = std::chrono::steady_clock::now();
  time_end = time_start;
  time_elapsed_ = std::chrono::duration<float>(time_end - time_start).count();
  return true;
}

void Simulator::Start() {
  thread_ = new std::thread(&Simulator::Run, this);
}

void Simulator::Stop() {
  thread_stop = true;

  if (thread_) {
    std::cout << "Stopping simulator thread" << std::endl;
    thread_->join();
    std::cout << "Joined Simulator thread" << std::endl;
    delete thread_;
    thread_ = nullptr;
    std::cout << "Stopped simulator thread" << std::endl;
  }
}

uint32_t Simulator::Run() {
  std::chrono::steady_clock::time_point time_init = std::chrono::steady_clock::now();
  float x_dd = 0;
  float x_d = 0;
  float x = 0.0f;  // max: 0.42f - min: 0.42f
  float w_dd = 0;
  float w_d = 0;
  float w = 3.14f; //1.57079632679f;

  float m_p = 0.071f;
  float m_c = 0.288f;
  float L_p = (0.685f - 0.246f);
  float I_p = 0.00466;
  float g = 9.81f;
  float F_m = 0;
  float b_c = 0.095f;
//  float b_c = 0.545f;
  float b_p = 0.00112297f;
  float rail_limit = 0.42f;
  while (!thread_stop) {
    time_start = std::chrono::steady_clock::now();
//    F_m = 0.4f*static_cast<float>(std::sin(2*time_elapsed_));

    x_dd = (F_m - b_c * x_d - m_p * L_p * w_dd * cos(w) + m_p * L_p * w_d * w_d * sin(w)) / (m_p + m_c);
    x_d = x_dd * time_step + x_d;
    x = x_d * time_step + x;

    if(x >= rail_limit){
      x_dd = 0;
      x_d = -x_d;
      x = rail_limit;
    }

    if(x <= -rail_limit){
      x_dd = 0;
      x_d = -x_d;
      x = -rail_limit;
    }

    w_dd = (-m_p * L_p * g * sin(w) - m_p * L_p * x_dd * cos(w) - b_p * w_d) / (I_p + m_p * L_p * L_p);
    w_d = w_dd * time_step + w_d;
    w = w_d * time_step + w;

    //UpdateSimulation();

    mutex_.lock();
    position_ = x;
    angle_ = w;
    mutex_.unlock();

    time_elapsed_ = std::chrono::duration<float>(std::chrono::steady_clock::now() - time_init).count();
    time_end = std::chrono::steady_clock::now();
    float duration = std::chrono::duration<float>(time_end - time_start).count();
    UpdateLoopAverage(duration);
    if (duration < time_step) {
      std::this_thread::sleep_for(std::chrono::duration<float>(time_step - duration));
    }
  }
  return 0;
}

void Simulator::GetState(float &position, float &angle) {
  mutex_.lock();
  position = position_;
  angle = angle_ * 180.f / 3.14159265359f;  // Convert to DEG
  mutex_.unlock();
}

void Simulator::GetStats(float &simulation_time, float &elapsed_time) {
  mutex_.lock();
  simulation_time = simulation_time_;
  elapsed_time = time_elapsed_;
  mutex_.unlock();
}

void Simulator::UpdateLoopAverage(float duration) {
  // Moving average
  simulation_time_ = simulation_time_ + (duration - simulation_time_) / step_;
  step_++;
}

void Simulator::UpdateSimulation() {


}


