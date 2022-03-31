import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Dialogs 1.2
import GuiStyle 1.0

import "qrc:/gui/components/menu/"
import "qrc:/gui/components/toolbar/"
import "qrc:/gui/window_content/"
import "qrc:/gui/windows/about_app"

ApplicationWindow {
    id: mainWindow
    property Window addBlocksWindow: null
    width: 1920
    height: 1080
    minimumWidth: 800
    minimumHeight: 600
    visible: true
    title: Qt.application.name

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

    AboutApplication {
        id: aboutApp
        parent: Overlay.overlay
        visible: false
        modal: true
        closePolicy: AboutApplication.CloseOnEscape | AboutApplication.CloseOnPressOutsideParent

        x: Math.round((parent.width - width) / 2)
        y: Math.round((parent.height - height) / 2)
        width: 400
        height: 400
    }

    MessageDialog {
        id: messageDialog
        visible: false
    }

    Connections {
        target: guiEngine.filesManager

        function onLoadSuccess(file, creator, date) {
            messageDialog.icon  = StandardIcon.Information
            messageDialog.title = qsTr("Load file successful")
            messageDialog.text  = qsTr("File %1 was successfully loaded.\nCreator:\t\t%2\nLast modified:\t%3").arg(file).arg(creator).arg(date)
            messageDialog.visible = true
        }

        function onError(file, error) {
            messageDialog.icon  = StandardIcon.Critical
            messageDialog.title = qsTr("Load file failed")
            messageDialog.text  = qsTr("Error occured during loading file %1:\n%2").arg(file).arg(error)
            messageDialog.visible = true
        }
    }
}
