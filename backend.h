//
// Created by ICraveSleep on 12-Mar-23.
//

#ifndef INVERTED_PENDULUM_SIMULATION_BACKEND_H_
#define INVERTED_PENDULUM_SIMULATION_BACKEND_H_

#include <QObject>
#include <QString>
#include <QTimer>
#include <qqml.h>
#include <cmath>
#include <iostream>
#include <thread>
#include <windows.h>

class BackEnd : public QObject {
 Q_OBJECT
  Q_PROPERTY(float angle READ angle WRITE setUserName NOTIFY angleChanged)
  Q_PROPERTY(float pos READ getPos NOTIFY posChanged)
  Q_PROPERTY(float count READ getCount NOTIFY countChanged)
  QML_ELEMENT

 public:
  explicit BackEnd(QObject *parent = nullptr);
  ~BackEnd(){
    delete q_timer_;
    do_run = false;
    runner->join();
    qWarning("Joined thread");
    delete runner;
  }
  int angle();
  void setUserName(const int &angle);
  void increment() {count_+= 0.25f;
    if (count_ >= 360.0f){
      count_ = count_ - 360.0f;
    }
    emit countChanged();
  }

  void init(){
    qInfo("Running Init");
  }

  void runPos(){  // Called at Qtimer q_timer_'s interval
//    pos_ = static_cast<float>(0.4*sin(timer_*0.5));
//    timer_ += 17.0/1000.0;
    pos_ = thread_pos;
    qInfo("timer: %f", timer_);
    emit posChanged();
  }

  void task(){

    std::cout << "Hello" << std::endl;
    while(do_run){
      thread_pos = static_cast<float>(0.4*sin(timer_*0.5));
      timer_ += 10.0/1000.0;
      Sleep(10.0);
    }

  }



  Q_INVOKABLE
  float getCount() const {return count_;}

  Q_INVOKABLE
  float getPos() const {return pos_;}

 signals:
  void countChanged();
  void posChanged();
  void angleChanged();

 private:
  int m_angle;
  float count_;
  float pos_;
  QTimer* q_timer_;
  double timer_;
  std::thread *runner;
  bool do_run = true;
  float thread_pos;
};

#endif //INVERTED_PENDULUM_SIMULATION_BACKEND_H_
