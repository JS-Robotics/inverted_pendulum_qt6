//! [import]
import QtQuick
import QtQuick3D

//! [import]
Window {
    id: window
    height: 720
    minimumHeight: 720
    minimumWidth: 1280
    title: qsTr("Inverted Pendulum Simulation")
    visible: true
    color: "#3c3c3c"
    maximumWidth: 1280
    maximumHeight: 720
    width: 1280

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
                eulerRotation.y: 0
                eulerRotation.x: 330
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
                    // position: Qt.vector3d(0, 0.9, 0.255363)
                    x: 0.0
                    y: 0.916091
                    z: 0.072269

                    Model {
                        id: pendulumModel
                        materials: [black_material, white_material]
                        position: Qt.vector3d(0, 0, 0)
                        source: "imports/meshes/pendulum.mesh"
                        eulerRotation.z: 0
                    }
                }
            }
        }
    }
}
