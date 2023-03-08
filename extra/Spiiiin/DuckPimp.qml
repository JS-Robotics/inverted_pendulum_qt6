import QtQuick
import QtQuick3D

Node {
    // Materials
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
    // end of Materials

    Node {
        id: rootNode
        PointLight {
            id: light
            x: 407.625
            y: 590.386
            z: -100.545
            rotation: Qt.quaternion(0.707107, -0.707107, 0, 0)
            brightness: 1000
            quadraticFade: 0.00222222
        }
        PerspectiveCamera {
            id: camera
            x: 735.889
            y: 495.831
            z: 692.579
            rotation: Qt.quaternion(0.707107, 0, -0.707107, 0)
            fieldOfView: 39.5978
            fieldOfViewOrientation: PerspectiveCamera.Horizontal
        }
        Model {
            id: patitodegoma2
            scale.x: 100
            scale.y: 100
            scale.z: 100
            source: "meshes/patitodegoma2.mesh"
            materials: [
                eyes_material,
                body_material,
                beack_material,
                hat1_material,
                hat2_material
            ]
        }
    }
}
