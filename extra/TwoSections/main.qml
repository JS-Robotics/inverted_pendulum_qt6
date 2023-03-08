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
        x: 0
        y: 120

        View3D {
            anchors.fill: parent
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
            anchors.leftMargin: 0
            anchors.topMargin: 0
            camera: camera
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
                    running: true
                    duration: 500
                    from: -360
                    loops: Animation.Infinite
                    to: 0
                }
                PropertyAnimation on eulerRotation.x  {
                    running: true
                    duration: 500
                    from: 360
                    loops: Animation.Infinite
                    to: 0
                }
                materials: [
                    greenColor
                ]
            }
            Model {
                position: Qt.vector3d(0, 350, 0)
                scale: Qt.vector3d(150, 150, 150)
                source: "duck.mesh"

                PropertyAnimation on eulerRotation.y  {
                    running: true
                    duration: 5000
                    from: 360
                    loops: Animation.Infinite
                    to: 0
                }
                materials: [
                    eyes_material,
                    body_material,
                    beack_material,
                    hat1_material,
                    hat2_material
                ]
            }
            Text {
                id: text1
                font.pixelSize: 12
                height: 49
                text: qsTr("So this is the text")
                width: 119
                x: 304
                y: 330
            }
            LabelSlider {
                id: labelSlider
                x: 99
                y: 94
            }
        }
    }
    Item {
        id: __materialLibrary__
        DefaultMaterial {
            id: redColor
            diffuseColor: "red"
            objectName: "Red"
        }

        DefaultMaterial {
            id: greenColor
            diffuseColor: "#4aee45"
            objectName: "Green"
        }
        DefaultMaterial {
            id: eyes_material
            diffuseColor: "#ff000000"
        }
        DefaultMaterial {
            id: body_material
            diffuseColor: "#ffff9001"
        }
        DefaultMaterial {
            id: beack_material
            diffuseColor: "#ffcc0800"
        }
        DefaultMaterial {
            id: hat1_material
            diffuseColor: "#ff2c00cc"
        }
        DefaultMaterial {
            id: hat2_material
            diffuseColor: "#ffcc5500"
        }
    }

    Item {
        id: __animationLibrary__

    }

    Text {
        id: text2
        x: 31
        y: 29
        text: qsTr("Text")
        font.pixelSize: 12
    }

    Button {
        id: button1
        height: 31
        text: "Hello"
        width: 85
        x: 142
        y: 34
    }

    View3D {
        id: view3D
        x: 880
        y: 320
        width: 400
        height: 400
        SceneEnvironment {
            id: sceneEnvironment
            antialiasingMode: SceneEnvironment.MSAA
            antialiasingQuality: SceneEnvironment.High
        }

        Node {
            id: scene1
            DirectionalLight {
                id: directionalLight
            }

            PerspectiveCamera {
                id: sceneCamera
                z: 350
            }

            Model {
                id: cubeModel
                source: "#Cube"
                materials: redColor
                eulerRotation.y: 45
                eulerRotation.x: 30

                PropertyAnimation on eulerRotation.y  {
                    running: true
                    duration: 5000
                    from: -360
                    loops: Animation.Infinite
                    to: 0
                }
            }
        }
        environment: sceneEnvironment
    }

}
