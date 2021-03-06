import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import QtQuick.Shapes 1.15
import GuiStyle 1.0

Shape {
    id: root
    property alias lineWidth: path.strokeWidth
    property alias lineColor: path.strokeColor
    property alias startX: path.startX
    property alias startY: path.startY
    property int endX: 0
    property int endY: 0
    property bool selected: false
    property color selectedLineColor: "black"

    signal lineRemoved()
    containsMode: Shape.FillContains

    ShapePath {
        id: path
        fillColor: "transparent"
        PathLine{x: root.endX; y: root.endY}
    }

    states: State {
        name: "line_selected"
        when: root.selected

        PropertyChanges {
            target: path
            strokeColor: root.selectedLineColor
        }
    }
}
