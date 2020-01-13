import QtQuick 2.0
import QtQuick.Particles 2.0

Rectangle {
    id: root
     color: "#00000000"
    width: 1000
    height: 300
    ParticleSystem {
        id: sys
    }
    ImageParticle {
        system: sys
        source: "qrc:/theme/theme/I.png"
        colorVariation: 1.0
        alpha: 0.1
    }

    Component {
        id: emitterComp
        Emitter {
            id: container
            Emitter {
                id: emitMore
                system: sys
                emitRate: 128
                lifeSpan: 600
                size: 16
                endSize: 8
                velocity: AngleDirection {angleVariation:360; magnitude: 60}
            }

            property int life: 2600
            property real targetX: 0
            property real targetY: 0
            function go() {
                xAnim.start();
                yAnim.start();
                container.enabled = true
            }
            system: sys
            emitRate: 32
            lifeSpan: 600
            size: 24
            endSize: 8
            NumberAnimation on x {
                id: xAnim;
                to: targetX
                duration: life
                running: false
            }
            NumberAnimation on y {
                id: yAnim;
                to: targetY
                duration: life
                running: false
            }
            Timer {
                interval: life
                running: true
                onTriggered: container.destroy();
            }
        }
    }

    function customEmit(x,y) {
        //! [0]
        for (var i=0; i<1; i++) {
            var obj = emitterComp.createObject(root);
            obj.x = x
            obj.y = y
           // obj.targetX = Math.random() * 240 - 120 + obj.x
           // obj.targetY = Math.random() * 240 - 120 + obj.y
            obj.targetX = obj.x+ 100;
            obj.targetY = obj.y
            obj.life = Math.round(Math.random() * 2400) + 200
            obj.emitRate = Math.round(Math.random() * 32) + 32
            obj.go();
        }
        //! [0]
    }

    Timer {
        interval: 100
        triggeredOnStart: true
        running: true
        repeat: true
        onTriggered: customEmit(Math.random() * 320, Math.random() * 480)
    }
    MouseArea {
        anchors.fill: parent
        onClicked: customEmit(mouse.x, mouse.y);
    }
}


