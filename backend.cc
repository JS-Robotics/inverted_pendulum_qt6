//
// Created by ICraveSleep on 12-Mar-23.
//

#include "backend.h"

BackEnd::BackEnd(QObject *parent) : QObject(parent) {
  timer_ = 0.0f;
  pos_ = 0.0f;
  angle_ = 0.0f;
  sim_time_ = 0.0f;
  elapsed_time_ = 0.0f;
  q_timer_ = new QTimer(this);
  connect(q_timer_, &QTimer::timeout, this, &BackEnd::getPose);
  q_timer_->start(17);

  simulator_ = new Simulator();
  simulator_->Init();

  if (simulator_) {
    communication_ = new Communication(*simulator_);
    communication_->Init();
  } else {
    std::cout << "Unable to create communication object due to simulator object being null" << std::endl;
  }
}

BackEnd::~BackEnd() {
  delete q_timer_;
  stop();
}

void BackEnd::getPose() { // Called at Qtimer q_timer_'s interval
  simulator_->GetState(pos_, angle_);
  simulator_->GetStats(sim_time_, elapsed_time_);
  sim_time_ = 1000000 * sim_time_;
  emit simChanged();
  emit angleChanged();
  emit posChanged();
  emit elapsedChanged();
}

void BackEnd::init() {
  qInfo("Running Init");
  simulator_->Start();
  communication_->Start();
}

void BackEnd::stop() {

  if (communication_) {
    std::cout << "Deleting communication object" << std::endl;
    simulator_->Stop();
    delete communication_;
    communication_ = nullptr;
  }

  if (simulator_) {
    std::cout << "Deleting simulator object" << std::endl;
    simulator_->Stop();
    delete simulator_;
    simulator_ = nullptr;
  }

}
