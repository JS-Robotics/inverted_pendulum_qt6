#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QtGui>
#include <QtQuick3D/qquick3d.h>

#include "iostream"

void do_cpp(){
  std::cout << "Hello" << std::endl;
}

int main(int argc, char *argv[])
{

  QGuiApplication app(argc, argv);
//  std::cout << "Bob kååre" << std::endl;
//  qInfo("Hello");
//  do_cpp();

  QSurfaceFormat::setDefaultFormat(QQuick3D::idealSurfaceFormat(4));

  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
//  QUrl u = QUrl(QStringLiteral("qrc:/main.qml"));
//  QString a = u.toString();
//  QString b = QStringLiteral("qrc:/main.qml");
//  std::cout << "Path is: " << a.toUtf8().constData() << std::endl;
//  std::cout << "Path is: " << b.toUtf8().constData() << std::endl;
//  std::cout << "Bob kååre" << std::endl;
  if (engine.rootObjects().isEmpty())
    return -1;

  return QGuiApplication::exec();
}
