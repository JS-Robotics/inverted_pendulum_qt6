//! [import]
import QtQuick
import QtQuick3D

//! [import]
import QtQuick.Controls 6.3
Window {
    id: window

    property real angle: 0.0
    property real pos: 0.0
    property real sim: 0.0
    property real elapsed: 0.0

    color: "#3c3c3c"
    height: 720
    maximumHeight: 720
    maximumWidth: 1280
    minimumHeight: 720
    minimumWidth: 1280
    title: qsTr("Inverted Pendulum Simulation")
    visible: true
    width: 1280

    Connections {
        target: backend
        // @disable-check M16
        onAngleChanged: angle = backend.getAngle()   // Angle is received in rad
        // @disable-check M16
        onPosChanged: pos = backend.getPos()        // Position is received in meters
        // @disable-check M16
        onSimChanged: sim = backend.getSim()
        // @disable-check M16
        onElapsedChanged: elapsed = backend.getElapsed()
    }
    Item {
        id: __materialLibrary__

        // Materials
        DefaultMaterial {
            id: black_material
            diffuseColor: "#ff272727"
        }
        DefaultMaterial {
            id: white_material
            diffuseColor: "#ffd2d2d2"
        }
        // end of Materials
    }
    View3D {
        id: view3D
        environment: sceneEnvironment
        height: 720
        width: 849
        x: 0
        y: 0

        SceneEnvironment {
            id: sceneEnvironment
            antialiasingMode: SceneEnvironment.MSAA
            antialiasingQuality: SceneEnvironment.High
            backgroundMode: SceneEnvironment.Transparent
        }
        Node {
            id: scene
            DirectionalLight {
                id: directionalLight
                eulerRotation.x: 330
                eulerRotation.y: 0
                eulerRotation.z: 0
            }
            PerspectiveCamera {
                id: sceneCamera
                z: 170
            }
            Model {
                id: baseModel
                eulerRotation.x: 0
                eulerRotation.y: 0
                materials: [black_material, white_material]
                position: Qt.vector3d(0, -83, 0)
                scale: Qt.vector3d(100, 100, 100)
                source: "imports/meshes/base.mesh"

                Model {
                    id: cartModel
                    materials: [black_material, white_material]
                    source: "imports/meshes/cart.mesh"
                    x: pos
                    y: 0.916091
                    z: 0.072269

                    Model {
                        id: pendulumModel

                        eulerRotation.z: angle * (57.2957795131)
                        materials: [black_material, white_material]
                        position: Qt.vector3d(0, 0, 0)
                        source: "imports/meshes/pendulum.mesh"
                    }
                }
            }
        }
    }
    Button {
        id: button_reset
        x: 1144
        y: 646
        text: qsTr("Reset")
        onClicked: backend.handleButtonReset()
    }

    Column {
        id: column
        height: 400
        width: 200
        x: 1024
        y: 11

        Text {
            id: angle_text
            color: "#ffffff"
            text: "Angle:      " + (angle).toFixed(2) + "[rad]"
            font.pixelSize: 26
            font.styleName: "Regular"
            font.weight: Font.Normal
            height: 39
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignTop
            width: 200
        }
        Text {
            id: position_text
            color: "#ffffff"
            text: "Position:   " + pos.toFixed(2) + "[m]"
            font.pixelSize: 26
            font.styleName: "Regular"
            font.weight: Font.Normal
            height: 39
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignTop
            width: 200
        }

        Text {
            id: sim_time_text
            color: "#ffffff"
            text: "Sim Time:  " + (sim).toFixed(2) + "[us]"
            font.pixelSize: 26
            font.styleName: "Regular"
            font.weight: Font.Normal
            height: 39
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignTop
            width: 200
        }
        Text {
            id: elapsed_time_text
            color: "#ffffff"
            font.pixelSize: 26
            font.styleName: "Regular"
            font.weight: Font.Normal
            height: 39
            horizontalAlignment: Text.AlignLeft
            text: "Elapsed:  " + (elapsed).toFixed(1) + "[s]"
            verticalAlignment: Text.AlignTop
            width: 200
        }
    }

}
