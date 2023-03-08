#include <QCoreApplication>
#include <QDebug>
#include <QUrl>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtGui>
#include <QtQuick3D/qquick3d.h>
#include "iostream"


int main(int argc, char *argv[])
{

  QGuiApplication app(argc, argv);

  QSurfaceFormat::setDefaultFormat(QQuick3D::idealSurfaceFormat(4));

  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
//  engine.load(QUrl(QStringLiteral("qrc:/DuckPimp.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return QGuiApplication::exec();
}

