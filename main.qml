import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import GuiStyle 1.0

import "qrc:/gui/components/menu/"
import "qrc:/gui/components/toolbar/"
import "qrc:/gui/window_content/"

ApplicationWindow {
    id: mainWindow
    property Window addBlocksWindow: null
    width: 1920
    height: 1080
    minimumWidth: 800
    minimumHeight: 600
    visible: true
    title: qsTr("aR-Lang")

    function openAddBlocksWindow() {
        if(mainWindow.addBlocksWindow === null) {
            const addBlocksComponent    = Qt.createComponent("qrc:/gui/windows/add_blocks_window/AddBlocksWindow.qml")
            mainWindow.addBlocksWindow  = addBlocksComponent.createObject(mainWindow, {
                                                                              width: mainWindow.width * 0.2,
                                                                              height: mainWindow.height * 0.4,
                                                                              x: mainWindow.width * 0.2,
                                                                              y: mainWindow.height * 0.2,
                                                                          })
            mainWindow.addBlocksWindow.closing.connect(() => mainWindow.addBlocksWindow = null)
            mainWindow.addBlocksWindow.show()
        } else {
            mainWindow.addBlocksWindow.requestActivate()
        }
    }

    menuBar: AppMenuBar{}
    header: AppToolbar{}

    AppWindowContent {
        anchors.fill: parent
    }
}
