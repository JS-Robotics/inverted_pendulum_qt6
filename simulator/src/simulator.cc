//
// Created by ICraveSleep on 15-Mar-23.
//

#include "simulator/simulator.h"

Simulator::Simulator() {
  thread_ = nullptr;
}

Simulator::~Simulator() {
  Stop();
}

bool Simulator::Init() {
  thread_stop = false;
  time_step = 1.f / 750.f;
  time_start = std::chrono::steady_clock::now();
  time_end = time_start;
  time_elapsed_ = std::chrono::duration<float>(time_end - time_start).count();
  return true;
}

uint32_t Simulator::Run() {
  std::chrono::steady_clock::time_point time_init = std::chrono::steady_clock::now();
  float x_dd = 0;
  float x_d = 0;
  float x = 0;
  float w_dd = 0;
  float w_d = 0;
  float w = 3.01f;

  float m_p = 0.071f;
  float m_c = 0.288f;
  float L_p = (0.685f - 0.246f);
  float I_p = 0.0000005f; //0.006f;
  float g = 9.81f;
  float F_m = 0;
  float b_c = 0.0001f;//1.15f;
  float b_p = 0.0005f;//0.35f; //1.17f;

  while (!thread_stop) {
    time_start = std::chrono::steady_clock::now();

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    x_dd = (F_m - b_c * x_d - m_p * L_p * w_dd * cos(w) + m_p * L_p * w_d * w_d * sin(w)) / (m_p + m_c);
    x_d = x_dd * time_step + x_d;
    x = x_d * time_step + x;

    w_dd = (-m_p * L_p * g * sin(w) - m_p * L_p * x_dd * cos(w) - b_p * w_d) / (I_p + m_p * L_p * L_p);
    w_d = w_dd * time_step + w_d;
    w = w_d * time_step + w;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    mutex_.lock();
    position_ = x;
    angle_ = w;
    mutex_.unlock();
    time_end = std::chrono::steady_clock::now();
    simulation_time_ = std::chrono::duration<float>(time_end - time_start).count();
    time_elapsed_ = std::chrono::duration<float>(std::chrono::steady_clock::now() - time_init).count();
    float duration = std::chrono::duration<float>(time_end - time_start).count();
    if (duration < time_step) {
      std::this_thread::sleep_for(std::chrono::duration<float>(time_step - duration));
    }
  }
  return 0;
}

void Simulator::Stop() {
  thread_stop = true;

  if(thread_){
    std::cout << "Stopping simulator thread" << std::endl;
    thread_->join();
    std::cout << "Joined Simulator thread" << std::endl;
    delete thread_;
    thread_ = nullptr;
    std::cout << "Stopped simulator thread" << std::endl;
  }
}

void Simulator::GetState(float &position, float &angle) {
  mutex_.lock();
  position = position_;
  angle = angle_*180.f/3.14159265359f;  // Convert to DEG
  mutex_.unlock();
}

void Simulator::GetStats(float &simulation_time, float &elapsed_time){
  mutex_.lock();
  simulation_time = simulation_time_;
  elapsed_time = time_elapsed_;
  mutex_.unlock();
}

void Simulator::Start() {
  thread_ = new std::thread(&Simulator::Run, this);
}


