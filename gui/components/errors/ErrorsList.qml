import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import GuiStyle 1.0

import "qrc:/"
import "qrc:/gui/components/text/"

Item {
    id: root
    property alias errorsModel: errorsLv.model
    property alias errorsCount: errorsLv.count

    ListView {
        id: errorsLv
        readonly property int scrollWidth: 10
        anchors.fill: parent
        anchors.leftMargin: scrollWidth
        boundsBehavior: ListView.StopAtBounds
        spacing: 5
        clip: true
        delegate: Rectangle {
            width: ListView.view.width - ListView.view.scrollWidth
            height: 60
            radius: 5

            border.width: 3
            border.color: GuiStyle.color8

            Rectangle {
                anchors.fill: parent
                color: GuiStyle.color8
                opacity: 0.3
            }

            AppTextField {
                bgColor: "transparent"
                anchors.fill: parent
                padding: 5
                wrapMode: Text.WordWrap
                text: model.error
                readOnly: true
            }
        }

        ScrollBar.vertical: ScrollBar{
            width: errorsLv.scrollWidth
        }
    }
}
