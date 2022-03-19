import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import QtQuick.Shapes 1.15
import GuiStyle 1.0

Shape {
    id: root
    property color fillColor: "black"
    property color borderColor: "black"
    property bool canMove: false

    containsMode: Shape.FillContains

    ShapePath {
        strokeColor: root.borderColor
        fillColor: root.fillColor
        strokeWidth: 1

        startX: 0; startY: 0
        PathLine{x: 0; y: root.height}
        PathLine{x: root.width; y: root.height * 0.5}
        PathLine{x: 0; y: 0}
    }
}
