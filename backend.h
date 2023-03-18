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
#include "simulator/simulator.h"

class BackEnd : public QObject {
 Q_OBJECT
  Q_PROPERTY(float angle READ getAngle NOTIFY angleChanged)
  Q_PROPERTY(float pos READ getPos NOTIFY posChanged)
  Q_PROPERTY(float sim READ getSim NOTIFY simChanged)
  QML_ELEMENT

 public:
  explicit BackEnd(QObject *parent = nullptr);
  ~BackEnd();

  void init();

  void stop();

  void getPose();

  Q_INVOKABLE
  [[nodiscard]] float getPos() const {return pos_;}

  Q_INVOKABLE
  [[nodiscard]] float getAngle() const {return angle_;}

  Q_INVOKABLE
  [[nodiscard]] float getSim() const {return sim_time_;}

 signals:
  void simChanged();
  void posChanged();
  void angleChanged();

 private:
  float pos_;
  float angle_;
  float sim_time_;
  float elapsed_time_;
  QTimer* q_timer_;
  double timer_;
  Simulator* simulator_;
};

#endif //INVERTED_PENDULUM_SIMULATION_BACKEND_H_
