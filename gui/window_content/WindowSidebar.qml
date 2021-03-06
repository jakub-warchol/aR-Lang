import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import GuiStyle 1.0

import "qrc:/gui/components/text/"
import "qrc:/gui/components/errors/"

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
            horizontalAlignment: Text.AlignHCenter
            readOnly: true

            Connections {
                target: guiEngine

                function onCalculationStarted() {
                    resultTf.clear()
                }

                function onCalculationSucceeded(result) {
                    resultTf.text = Number(result).toFixed(6) * 1 // * 1 to remove unsignificant 0s
                }
            }

            Connections {
                target: guiEngine.filesManager

                function onLoadSuccess(file, creator, date) {
                    resultTf.clear()
                }

                function onError(file, error) {
                    resultTf.clear()
                }
            }
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
            id: logsRct
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: GuiStyle.color5

            ErrorsList {
                anchors.fill: parent
                errorsModel: guiEngine.errorsModel
            }
        }
    }
}
