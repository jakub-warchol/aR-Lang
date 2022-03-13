import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import GuiStyle 1.0

ToolButton {
    id: control

    contentItem: Image {
        source: control.icon.source
        opacity: enabled ? 1. : 0.3
        horizontalAlignment: Image.AlignHCenter
        verticalAlignment: Image.AlignVCenter
        fillMode: Image.PreserveAspectFit
    }

    background: Rectangle{
        implicitWidth: 40
        implicitHeight: 40
        color: Qt.darker(GuiStyle.color2, 1.5)
        opacity: enabled ? 1. : 0.3
        visible: control.down || (control.enabled && (control.checked || control.highlighted))
    }
}
