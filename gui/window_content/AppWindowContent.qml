import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import GuiStyle 1.0

import "qrc:/"

Rectangle {
    id: root
    color: "black"

    RowLayout {
        anchors.fill: parent
        spacing: 1

        Scope {
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: GuiStyle.color3
        }

        WindowSidebar {
            Layout.fillHeight: true
            Layout.preferredWidth: 145
            Layout.minimumWidth: 100
        }
    }
}
