import QtQuick
import QtQuick3D

Node {
    // Materials
    DefaultMaterial {
        id: black_008_material
        diffuseColor: "#ff060606"
    }
    DefaultMaterial {
        id: white_008_material
        diffuseColor: "#ffdbdbad"
    }
    // end of Materials

    Node {
        id: rootNode
        Model {
            id: pendulum
            rotation: Qt.quaternion(0.707107, 0, 0, -0.707107)
            scale.x: 100
            scale.y: 100
            scale.z: 100
            source: "meshes/pendulum.mesh"
            materials: [
                black_008_material,
                white_008_material
            ]
        }
    }
}
