import QtQuick
import QtQuick3D

Node {
    // Materials
    DefaultMaterial {
        id: black_006_material
        diffuseColor: "#ff060606"
    }
    DefaultMaterial {
        id: steel_005_material
        diffuseColor: "#ff727272"
    }
    DefaultMaterial {
        id: white_007_material
        diffuseColor: "#ffa0a07e"
    }
    DefaultMaterial {
        id: dark_Gray_006_material
        diffuseColor: "#ff212121"
    }
    DefaultMaterial {
        id: white_008_material
        diffuseColor: "#ffdbdbad"
    }
    // end of Materials

    Node {
        id: rootNode
        Model {
            id: base
            rotation: Qt.quaternion(0.707107, 0, 0, -0.707107)
            scale.x: 100
            scale.y: 100
            scale.z: 100
            source: "meshes/base.mesh"
            materials: [
                black_006_material,
                steel_005_material
            ]
        }
        Model {
            id: cart
            x: 25.5363
            y: -4.37114e-07
            z: -2.50218
            rotation: Qt.quaternion(0.707107, 0, 0, -0.707107)
            scale.x: 100
            scale.y: 100
            scale.z: 100
            source: "meshes/cart.mesh"
            materials: [
                white_007_material,
                black_006_material,
                dark_Gray_006_material
            ]
        }
        Model {
            id: pendulum
            x: 25.5363
            y: -4.37114e-07
            z: -2.50218
            rotation: Qt.quaternion(0.707107, 0, 0, -0.707107)
            scale.x: 100
            scale.y: 100
            scale.z: 100
            source: "meshes/pendulum.mesh"
            materials: [
                black_006_material,
                white_008_material
            ]
        }
    }
}
