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

    View3D {
        id: view
        anchors.fill: parent

        //! [environment]
        environment: SceneEnvironment {
            backgroundMode: SceneEnvironment.Color
            clearColor: "skyblue"
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
            position: Qt.vector3d(0, 150, 0)
            source: "#Sphere"

            materials: [
                DefaultMaterial {
                    diffuseColor: "blue"
                }
            ]

            //! [animation]
            SequentialAnimation on y  {
                loops: Animation.Infinite

                NumberAnimation {
                    duration: 3000
                    easing.type: Easing.InQuad
                    from: 150
                    to: -150
                }
                NumberAnimation {
                    duration: 3000
                    easing.type: Easing.OutQuad
                    from: -150
                    to: 150
                }
            }
            //! [animation]
        }
        //! [objects]
    }
}
