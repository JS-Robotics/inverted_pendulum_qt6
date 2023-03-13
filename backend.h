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
  }
  int angle();
  void setUserName(const int &angle);
  void increment() {count_+= 0.25f;
    if (count_ >= 360.0f){
      count_ = count_ - 360.0f;
    }
    emit countChanged();
  }

  void runPos(){
    pos_ = static_cast<float>(0.4*sin(timer_*0.5));
    timer_ += 17.0/1000.0;
    emit posChanged();
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
};

#endif //INVERTED_PENDULUM_SIMULATION_BACKEND_H_
