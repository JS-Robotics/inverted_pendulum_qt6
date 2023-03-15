#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QtGui>
#include <QtQuick3D/qquick3d.h>
#include "backend.h"
#include "iostream"
#include "thread"

void task(std::string msg){
  std::cout << "task says: " << msg << std::endl;
}


int main(int argc, char *argv[])
{

  QGuiApplication app(argc, argv);
  BackEnd back_end;
  back_end.init();
  qInfo("Back_end created");
  QSurfaceFormat::setDefaultFormat(QQuick3D::idealSurfaceFormat(4));
//  QQmlApplicationEngine engine;
//  engine.rootContext()->setContextProperty("backend", &back_end);

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("backend", &back_end);


  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

//  qInfo("Is this blocking??");
//  qInfo("Starting simulator stopping");
//  back_end.stop();

  return QGuiApplication::exec();
}
