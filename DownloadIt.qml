import QtQuick 2.7
import QtQuick.Controls 1.5

ApplicationWindow {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("Download It")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")

            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    TextField {
        id: teLink
        width: root.width/2
        height: 50
        text: "http://www.youtube.com/watch?v=6DBi41reeF0"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }

    Button {
        id: btDownload
        anchors.horizontalCenter: teLink.horizontalCenter
        anchors.top : teLink.bottom
        text: "Download It"
        onClicked: {
            console.debug("Going to download = " + teLink.text)
            downloader.download(teLink.text)
        }
    }
}
