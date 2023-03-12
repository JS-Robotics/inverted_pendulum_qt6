//
// Created by ICraveSleep on 12-Mar-23.
//

#include "backend.h"

BackEnd::BackEnd(QObject *parent) :
    QObject(parent)
{
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
