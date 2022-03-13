import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import GuiStyle 1.0

TextField {
    id: control
    placeholderTextColor: GuiStyle.color6

    background: Rectangle {
        implicitWidth: 200
        implicitHeight: 40
        color: "#ffffff"
    }
}
