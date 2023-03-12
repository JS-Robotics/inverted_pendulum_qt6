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
    title: "Assembly"
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
        // height: 600
        height: 600
        // width: 800
        width: 628
        leftPadding: 60
        rightPadding: 60
        state: "mobileHorizontal"
        topPadding: 50

        x: 0
        y: 120

        View3D {
            anchors.bottomMargin: -37
            anchors.fill: parent
            anchors.leftMargin: -52
            anchors.rightMargin: -49
            anchors.topMargin: -38
            camera: camera

            Node {
                id: scene
                PointLight {
                    brightness: 1
                    quadraticFade: 0
                    x: 100
                    z: 700
                }
                DirectionalLight {
                    x: 0
                    y: 0
                    z: 0
                    eulerRotation.x: -103
                    eulerRotation.y: 0
                    eulerRotation.z: 0
                }
                PerspectiveCamera {
                    id: camera
                    x: 0
                    y: 41
                    pivot.z: -173
                    pivot.x: 0
                    eulerRotation.z: 0
                    eulerRotation.y: 0
                    eulerRotation.x: 0
                    z: 1330
                }
            }
            Model {
                opacity: 1
                materials: [black_006_material, steel_005_material]
                position: Qt.vector3d(0, -600, 0)
                scale: Qt.vector3d(1000, 1000, 1000)
                source: "meshes/meshes/base.mesh"
                castsShadows: true
                receivesReflections: false

                Model {
                    // materials: black_006_material
                    materials: [white_007_material, black_006_material, dark_Gray_006_material]
                    source: "meshes/meshes/cart.mesh"
                    // position: Qt.vector3d(0, 0.9, 0.255363)
                    x: 0.0
                    y: 0.9
                    z: 0.255363
                    Model {
                        // materials: black_006_material
                        materials: [black_006_material, white_008_material]
                        position: Qt.vector3d(0, 0, 0)
                        source: "meshes/meshes/pendulum.mesh"
                    }
                }
            }
            Text {
                id: text1
                font.pixelSize: 12
                height: 49
                text: qsTr("So this is the text")
                width: 119
                x: 360
                y: 276
            }
        }
    }
    Item {
        id: __materialLibrary__
        // Materials
        DefaultMaterial {
            id: black_006_material
            diffuseColor: "#ff333333"
        }
        DefaultMaterial {
            id: steel_005_material
            diffuseColor: "#ff727272"
        }
        DefaultMaterial {
            id: white_007_material
            diffuseColor: "#ffa0a0a0"
        }
        DefaultMaterial {
            id: dark_Gray_006_material
            diffuseColor: "#ff353535"
        }
        DefaultMaterial {
            id: white_008_material
            diffuseColor: "#ffdbdbdb"
        }
        // end of Materials
    }
}
