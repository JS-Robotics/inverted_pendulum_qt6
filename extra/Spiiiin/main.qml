// Copyright (C) 2019 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

//! [import]
import QtQuick
import QtQuick3D

//! [import]
Window {
    id: window
    height: 720
    visible: true
    width: 1280

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
    View3D {
        id: view
        anchors.fill: parent

        //! [environment]
        environment: SceneEnvironment {
            backgroundMode: SceneEnvironment.Color
            clearColor: "#222222"
        }

        //! [environment]

        //! [camera]
        PerspectiveCamera {
            eulerRotation.x: -30
            position: Qt.vector3d(0, 200, 300)
        }
        //! [camera]

        //! [light]
        DirectionalLight {
            eulerRotation.x: -30
            eulerRotation.y: -70
        }
        //! [light]

        //! [objects]
        Model {
            position: Qt.vector3d(0, -200, 0)
            scale: Qt.vector3d(2, 0.2, 1)
            source: "#Cylinder"

            materials: [
                DefaultMaterial {
                    diffuseColor: "red"
                }
            ]
        }
        Model {
            materials: [eyes_material, body_material, beack_material, hat1_material, hat2_material]
            position: Qt.vector3d(0, 0, 0)
            scale: Qt.vector3d(100, 100, 100)
            source: "meshes/patitodegoma2.mesh"

            PropertyAnimation on eulerRotation.y  {
                duration: 5000
                from: -360
                loops: Animation.Infinite
                to: 0
            }
        }
        Model {
            position: Qt.vector3d(150, 100, -300)
            scale: Qt.vector3d(50, 50, 50)
            source: "meshes/teapot.mesh"

            PropertyAnimation on eulerRotation.x  {
                duration: 5000
                from: -360
                loops: Animation.Infinite
                to: 0
            }
            materials: [
                PrincipledMaterial {
                    baseColor: "#41cd52"
                    metalness: 0.0
                    opacity: 1.0
                    roughness: 0.1
                }
            ]
        }
    }
}
