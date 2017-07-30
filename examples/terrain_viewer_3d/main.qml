import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import TerrainML 1.0
import TerrainML3D 1.0

import QtQuick 2.2 as QQ2
import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Input 2.0
import Qt3D.Extras 2.0
import QtQuick.Scene3D 2.0

ApplicationWindow
{
  id: root
  visible: true
  
  width: 600
  height: 600
  

  Scene3D {
    anchors.fill: parent
    Entity {
      id: sceneRoot

      Camera {
        id: camera
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 45
        aspectRatio: 16/9
        nearPlane : 0.1
        farPlane : 1000.0
        position: Qt.vector3d( 0.0, -40.0, 10.0 )
        upVector: Qt.vector3d( 0.0, 1.0, 0.0 )
        viewCenter: Qt.vector3d( 0.0, 0.0, 0.0 )
      }

      OrbitCameraController {
        camera: camera
      }

      components: [
        RenderSettings {
          activeFrameGraph: ForwardRenderer {
            clearColor: Qt.rgba(1, 1, 1, 1)
            camera: camera
          }
        },
        // Event Source will be set by the Qt3DQuickWindow
        InputSettings { }
      ]

      
      PhongMaterial {
        id: material
      }

      HeightMapMesh
      {
        id: heightMapMesh
        baseAltitude: 100
        QQ2.Component.onCompleted:
        {
          var hm = HeightMap.create(-10, -10, 20, 20, 20/60)
          hm = HeightMap.fill(hm, 100.0)
          hm = HeightMap.raise(hm, 0, 0, 4, 5, 2)
          hm = HeightMap.noise(hm, -3, 3, 2414, 0.2)
          heightMapMesh.heightMap = hm
        }
      }
      Transform {
        id: heightMapTransform
        property real userAngle: 0.0
        matrix: {
          var m = Qt.matrix4x4();
          m.rotate(-userAngle, Qt.vector3d(0, 0, 1));
          return m;
        }
      }
      QQ2.NumberAnimation {
        target: heightMapTransform
        property: "userAngle"
        duration: 10000
        from: 0
        to: 360

        loops: QQ2.Animation.Infinite
        running: true
      }

      Entity {
        id: torusEntity
        components: [ heightMapMesh, heightMapTransform, material ]
      }

      PointLight {
        id: pointLight
        color: "white"
        intensity: 0.3
        constantAttenuation: 1.0
        linearAttenuation: 0.0
        quadraticAttenuation: 0.0025

        QQ2.NumberAnimation on intensity {
          from: 0.3; to: 0.8;
          running: true
          loops: QQ2.Animation.Infinite
          duration: 4000
          easing.type: Easing.CosineCurve
        }
      }

      Transform {
        id: pointLightTransform
        property real userAngle: 0.0
        matrix: {
          var m = Qt.matrix4x4();
          m.rotate(userAngle, Qt.vector3d(0, 0, 1));
          m.translate(Qt.vector3d(40, 20, 100));
          return m;
        }
      }

      QQ2.NumberAnimation {
        target: pointLightTransform
        property: "userAngle"
        duration: 10000
        from: 0
        to: 360

        loops: QQ2.Animation.Infinite
        running: true
      }

      Entity {
        id: sphereEntity
        components: [ pointLight, pointLightTransform ]
      }
    }
  }
}
