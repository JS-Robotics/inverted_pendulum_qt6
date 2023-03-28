//
// Created by ICraveSleep on 28.03.23.
//

#include "communication/communication.h"

Communication::Communication() {
  thread_ = nullptr;
  thread_stop = false;
}

Communication::~Communication() {
  Stop();
}

bool Communication::Init() {
  thread_stop = false;
  return true;
}

void Communication::Start() {
  thread_ = new std::thread(&Communication::Run, this);
}

uint32_t Communication::Run() {
  // Do message publishes
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
