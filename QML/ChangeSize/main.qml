import QtQuick 2.14
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.Window 2.12

ApplicationWindow
{
    width: 500
    height: 500
    title: qsTr("Zohreh Naderi")
    visible: true

    //--- defines
    property int recCount: 10
    property int recSize: 100
    property int recSpaging: 50

    //--- variables
    property int rowCount: 0
    property int colCount: 0
    property int recCount_perPage: 0
    property int pageNumber: 0

    Component
    {
        id:viewComp
        MyLayout
        {
            id : idLyout
            property int start: 2
            anchors.fill:parent

            startIndex: start
            endIndex: 5
        }
    }

    TabView
    {
        id:my_tab

        anchors.fill:parent
        tabPosition: Qt.BottomEdge

        function loadTab(start,end)
        {
            var current_tab = currentIndex
            var name = "page " + (++pageNumber).toString()
            var t = my_tab.addTab(name,viewComp)
            currentIndex=count-1

            t.item.startIndex = start
            t.item.endIndex = end
            t.item.my_col_count = colCount
            t.item.my_row_count = rowCount
            t.item.my_spacing = recSpaging

            currentIndex = current_tab
        }
    }

    //----------------------------------------------------------
    function calcWidthSize()
    {
        colCount = width / (recSize + recSpaging)
    }
    function calcHeightSize()
    {
        rowCount = height / (recSize + recSpaging)
    }
    function calcSize()
    {
        recCount_perPage = rowCount * colCount
    }

    function show()
    {
        var count = my_tab.count
        while(count-- > 0)
            my_tab.removeTab(0)
        pageNumber = 0

        calcSize()

        my_tab.loadTab(0,recCount_perPage-1) //--- start and end "index" of Rectangles
        var nextStart = recCount_perPage
        while(recCount - nextStart > 0 && recCount - nextStart < 10)
        {
            my_tab.loadTab(nextStart,nextStart+recCount_perPage-1)
            nextStart += recCount_perPage
        }
    }
    //---------------------------------------------------------

    onWidthChanged:
    {
        var old = colCount
        calcWidthSize()
        if(colCount !== old)
            show()
    }
    onHeightChanged:
    {
        var old = rowCount
        calcHeightSize()
        if(rowCount !== old)
            show()
    }

    onVisibleChanged:
    {
        if(visible)
        {
            calcWidthSize()
            calcHeightSize()
            show()
        }
    }
}
/*##^##
Designer {
    D{i:2;anchors_x:142;anchors_y:20}D{i:3;anchors_x:270;anchors_y:20}D{i:4;anchors_x:142;anchors_y:20}
D{i:5;anchors_x:20;anchors_y:20}D{i:6;anchors_x:260;anchors_y:20}
}
##^##*/
