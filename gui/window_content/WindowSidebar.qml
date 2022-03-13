import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import GuiStyle 1.0

import "qrc:/gui/components/text/"

Item {
    id: root

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        AppTextField {
            id: resultTf
            Layout.fillWidth: true
            Layout.minimumHeight: 40
            Layout.maximumHeight: 40
            placeholderText: qsTr("Result:")
            verticalAlignment: Text.AlignVCenter
            readOnly: true
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.minimumHeight: 80
            color: GuiStyle.color4
        }

        AppTextField {
            Layout.fillWidth: true
            Layout.minimumHeight: 40
            Layout.maximumHeight: 40
            placeholderText: qsTr("Logs:")
            readOnly: true
        }

        Rectangle {
            id: logsRct // TODO: add ListView
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: GuiStyle.color5
        }
    }
}
