//! [import]
import QtQuick
import QtQuick3D

//! [import]
Window {
    id: window
    color: "#3c3c3c"
    height: 720
    maximumHeight: 720
    maximumWidth: 1280
    minimumHeight: 720
    minimumWidth: 1280
    title: qsTr("Inverted Pendulum Simulation")
    visible: true
    width: 1280

    property real count: 0.0
    property real pos: 0.0

    Connections {
        target: backend
        onCountChanged: count = backend.getCount()
        onPosChanged: pos = backend.getPos()
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
                        eulerRotation.z: count
                        materials: [black_material, white_material]
                        position: Qt.vector3d(0, 0, 0)
                        source: "imports/meshes/pendulum.mesh"
                    }
                }
            }
        }
    }
    Column {
        id: column
        height: 400
        width: 200
        x: 1064
        y: 11


        Text {
            id: angle_text
            color: "#ffffff"
            text: "Angle:     " + (count*0.01745329251).toFixed(3)
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
                width: 200
                height: 39
                color: "#ffffff"
                text: "Position:  " + pos.toFixed(3)
                font.pixelSize: 26
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignTop
                font.styleName: "Regular"
                font.weight: Font.Normal
            }

        }
}
