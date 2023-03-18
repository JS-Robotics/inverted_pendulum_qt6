//
// Created by ICraveSleep on 12-Mar-23.
//

#include "backend.h"

BackEnd::BackEnd(QObject *parent) : QObject(parent) {
  pos_ = 0;
  angle_ = 0;
  sim_time_ = 1.0f;
  q_timer_ = new QTimer(this);
  connect(q_timer_, &QTimer::timeout, this, &BackEnd::getPose);
  q_timer_->start(17);
  simulator_ = new Simulator();
  simulator_->Init();
}

BackEnd::~BackEnd() {
  delete q_timer_;
  simulator_->Stop();
  delete simulator_;
  simulator_ = nullptr;
}

void BackEnd::getPose() { // Called at Qtimer q_timer_'s interval
  simulator_->GetState(pos_, angle_);
  simulator_->GetStats(sim_time_, elapsed_time_);
  sim_time_ = 1000000*sim_time_;
  emit simChanged();
  emit angleChanged();
  emit posChanged();
}

void BackEnd::init() {
  qInfo("Running Init");
  simulator_->Start();
}

void BackEnd::stop() {
  simulator_->Stop();
  delete simulator_;
  simulator_ = nullptr;
}
