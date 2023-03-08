import QtQuick
import QtQuick3D
import QtQuick.Controls.Material
import QtQuick.Controls
import QtQuick.Layouts
import QtQml

Window {
    id: window
    height: 720
    minimumHeight: 600
    minimumWidth: 800
    title: "RobotArm"
    visible: true
    width: 1280

    // Copyright (C) 2022 The Qt Company Ltd.
    // SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause
    Pane {
        id: root

        property real buttonMinWidth: 65
        property real buttonRowWidth: width * 0.12
        readonly property bool horizontal: width > height
        readonly property bool mobile: Qt.platform.os === "android"
        property real sliderWidth: width * 0.15

        bottomPadding: 50
        height: 600
        leftPadding: 60
        rightPadding: 60
        state: "mobileHorizontal"
        topPadding: 50
        width: 800
        x: 219
        y: 49

        View3D {
            anchors.fill: parent
            camera: camera

            Button {
                id: button1
                height: 31
                text: "Hello"
                width: 85
                x: 100
                y: 179
            }
            Node {
                id: scene
                PointLight {
                    brightness: 1
                    quadraticFade: 0
                    x: 760
                    z: 770
                }
                DirectionalLight {
                    eulerRotation.y: -165
                    eulerRotation.z: 30
                }
                DirectionalLight {
                    brightness: 0.4
                    eulerRotation.x: -90
                    eulerRotation.y: 90
                    eulerRotation.z: -180
                    y: 1000
                }
                PerspectiveCamera {
                    id: camera
                    eulerRotation.y: 85
                    pivot.x: 200
                    x: 1050
                    y: 375
                    z: -40
                }
            }
            Model {
                position: Qt.vector3d(0, 0, 0)
                scale: Qt.vector3d(100, 100, 100)
                source: "duck.mesh"

                PropertyAnimation on eulerRotation.y  {
                    duration: 5000
                    from: -360
                    loops: Animation.Infinite
                    to: 0
                }
                materials: [
                    DefaultMaterial {
                        diffuseColor: "red"
                        objectName: "test"
                    }
                ]
            }
            Text {
                id: text1
                font.pixelSize: 12
                height: 49
                text: qsTr("So this is the text")
                width: 119
                x: 313
                y: 257
            }
            Slider {
                id: slider
                height: 0
                value: 0.5
                width: 251
                x: 100
                y: 83
            }
            LabelSlider {
                id: labelSlider
                x: 300
                y: 150
            }
        }
    }
    Item {
        id: __materialLibrary__
        DefaultMaterial {
            diffuseColor: "red"
            objectName: ""
        }
    }
}
