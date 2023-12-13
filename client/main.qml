import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15


ApplicationWindow {
    visible: true
    width: 400
    height: 200
    title: "WiseWallet"

    Rectangle {
        width: parent.width
        height: parent.height

        ColumnLayout {
            anchors.centerIn: parent

            TextField {
                id: inputTextField
                placeholderText: "Enter message"
                Layout.fillWidth: true
                Layout.preferredHeight: 30
            }

            TextField {
                id: outputTextField
                Layout.fillWidth: true
                Layout.preferredHeight: 30
                text: MainBackend.response
                readOnly: true
            }

            Button {
                id: sendButton
                text: "Send message"

                onClicked: {
                    MainBackend.sendMessage(inputTextField.text)
                }
            }
        }
    }
}
