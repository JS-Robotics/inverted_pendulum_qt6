#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QtGui>
#include <QtQuick3D/qquick3d.h>
#include "backend.h"
#include "iostream"


int main(int argc, char *argv[])
{

  QGuiApplication app(argc, argv);

  BackEnd back_end;

  QSurfaceFormat::setDefaultFormat(QQuick3D::idealSurfaceFormat(4));
//  QQmlApplicationEngine engine;
//  engine.rootContext()->setContextProperty("backend", &back_end);

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("backend", &back_end);


  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return QGuiApplication::exec();
}
