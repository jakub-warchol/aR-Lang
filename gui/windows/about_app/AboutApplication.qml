import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import QtQuick.Shapes 1.15
import GuiStyle 1.0

Popup {
    id: popup

    contentItem: Flickable {
        anchors.fill: parent
        contentWidth: parent.width
        contentHeight: column.implicitHeight + 10
        boundsBehavior: Flickable.StopAtBounds
        clip: true
        ScrollBar.vertical: ScrollBar {}

        Column {
            id: column
            anchors.fill: parent
            anchors.margins: 5
            spacing: 10

            Image {
                id: wutLogo
                source: "qrc:/resources/icons/pw_logo.png"
                fillMode: Image.PreserveAspectFit
                width: parent.width
            }

            Text {
                width: parent.width
                text: qsTr("<b>aR-Lang %1</b>").arg(Qt.application.version)
            }

            Text {
                width: parent.width
                text: qsTr("  Program allows user to create an arythmetic expression in a visual way.\n  The chain of the graphical blocks may be proceeded in order to gain the result of that equation.")
                wrapMode: Text.WordWrap
            }

            Text {
                width: parent.width
                text: qsTr("It is a students' project written during <i>Advanced C++</i> course at Warsaw University of Technology.\n")
                wrapMode: Text.WordWrap
            }

            Text {
                width: parent.width
                text: qsTr("<ul>
                                <li>
                                    <b>Project supervisior:</b> Paweł Wnuk, PhD
                                </li>
                                <li>
                                    <b>Creators:</b>
                                        <ul>
                                            <li>
                                                Bartosz Srebro
                                            </li>
                                            <li>
                                                 Jakub Warchoł
                                            </li>
                                        </ul>
                                </li>
                            </ul>")
                wrapMode: Text.WrapAnywhere
            }

        }
    }
}
