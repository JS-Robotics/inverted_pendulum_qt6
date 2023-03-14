//
// Created by ICraveSleep on 12-Mar-23.
//

#include "backend.h"

BackEnd::BackEnd(QObject *parent) :
    QObject(parent)
{
  count_ = 0;
  pos_ = 0;
  timer_ = 0;
  q_timer_ = new QTimer(this);
  connect(q_timer_, &QTimer::timeout, this, &BackEnd::increment);
  connect(q_timer_, &QTimer::timeout, this, &BackEnd::runPos);
  q_timer_->start(17);
  runner = new std::thread(&BackEnd::task, this);
}

int BackEnd::angle()
{
  return m_angle;
}

void BackEnd::setUserName(const int &angle)
{
  if (angle == m_angle)
    return;

  m_angle = angle;
  emit angleChanged();
}
