//
// Created by ICraveSleep on 28.03.23.
//

#include "communication/communication.h"

Communication::Communication(Simulator* simulator): simulator_(simulator) {
  time_step_ = 0.0f;
  thread_ = nullptr;
  thread_stop = false;
}

Communication::~Communication() {
  Stop();
}

bool Communication::Init() {
  thread_stop = false;
  time_step_ = 0.01f; // 10[ms]
  time_start_ = std::chrono::steady_clock::now();
  time_end_ = time_start_;
  return true;
}

void Communication::Start() {
  thread_ = new std::thread(&Communication::Run, this);
}

uint32_t Communication::Run() {
  // Do message publishes
  while(!thread_stop){
    time_start_ = std::chrono::steady_clock::now();
    float a;
    float b;
    simulator_->GetState(a, b);
    std::cout << a << std::endl;
    time_end_ = std::chrono::steady_clock::now();
    float duration = std::chrono::duration<float>(time_end_ - time_start_).count();
    if (duration < time_step_) {
      std::this_thread::sleep_for(std::chrono::duration<float>(time_step_ - duration));
    }
  }
  std::cout << "RUN STOPPING" << std::endl;
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
    std::cout << "Stopped communication thread" << std::endl;
  }
}
