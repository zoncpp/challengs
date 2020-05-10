import QtQuick 2.14
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.Window 2.12

Item
{
    id: id_mylayout

    property var colors:["red","green","blue","yellow","mediumspringgreen","chocolate","indianred","darkred","deeppink","olivedrab"]
    property int startIndex: 0
    property int endIndex: 0
    property int my_col_count: 0
    property int my_row_count: 0
    property int my_spacing: 0

    GridLayout
    {
        id: grid_ayout
        //anchors.fill: parent
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20

        flow: GridLayout.TopToBottom | GridLayout.LeftToRight

        columns: my_col_count
        rows: my_row_count

        rowSpacing: my_spacing
        columnSpacing: my_spacing

        Rectangle {
            id: recRed
            width: 100
            height: 100
            color: colors[0]
            visible: (startIndex <= 0 && endIndex >= 0)
        }
        Rectangle {
            id: recGreen
            width: 100
            height: 100
            color: colors[1]
            visible: (startIndex <= 1 && endIndex >= 1)
        }
        Rectangle {
            id: recBlue
            width: 100
            height: 100
            color: colors[2]
            visible: (startIndex <= 2 && endIndex >= 2)
        }
        Rectangle {
            id: recYellow
            width: 100
            height: 100
            color: colors[3]
            visible: (startIndex <= 3 && endIndex >= 3)
        }
        Rectangle {
            id: recDarkBlue
            width: 100
            height: 100
            color: colors[4]
            visible: (startIndex <= 4 && endIndex >= 4)
        }
        Rectangle {
            id: recGray
            width: 100
            height: 100
            color: colors[5]
            visible: (startIndex <= 5 && endIndex >= 5)
        }
        Rectangle {
            id: recDarkGray
            width: 100
            height: 100
            color: colors[6]
            visible: (startIndex <= 6 && endIndex >= 6)
        }
        Rectangle {
            id: recDarkRed
            width: 100
            height: 100
            color: colors[7]
            visible: (startIndex <= 7 && endIndex >= 7)
        }

        Rectangle {
            id: recLightRed
            width: 100
            height: 100
            color: colors[8]
            visible: (startIndex <= 8 && endIndex >= 8)
        }
        Rectangle {
            id: recLightGray
            width: 100
            height: 100
            color: colors[9]
            visible: (startIndex <= 9 && endIndex >= 9)
        }
    }
}
