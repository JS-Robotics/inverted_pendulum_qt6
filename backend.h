//
// Created by ICraveSleep on 12-Mar-23.
//

#ifndef INVERTED_PENDULUM_SIMULATION_BACKEND_H_
#define INVERTED_PENDULUM_SIMULATION_BACKEND_H_

#include <QObject>
#include <QString>
#include <qqml.h>

class BackEnd : public QObject {
 Q_OBJECT
  Q_PROPERTY(int angle READ angle WRITE setUserName NOTIFY angleChanged)
  QML_ELEMENT

 public:
  explicit BackEnd(QObject *parent = nullptr);

  int angle();
  void setUserName(const int &angle);

 signals:
  void angleChanged();

 private:
  int m_angle;
};

#endif //INVERTED_PENDULUM_SIMULATION_BACKEND_H_
