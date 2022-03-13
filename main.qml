import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import GuiStyle 1.0

import "qrc:/gui/components/menu/"
import "qrc:/gui/components/toolbar/"
import "qrc:/gui/window_content/"

ApplicationWindow {
    id: mainWindow
    width: 1920
    height: 1080
    minimumWidth: 800
    minimumHeight: 600
    visible: true
    title: qsTr("aR-Lang")

    menuBar: AppMenuBar{}
    header: AppToolbar{}

    AppWindowContent {
        anchors.fill: parent
    }
}
