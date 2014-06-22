import QtQuick 2.1
import Sailfish.Silica 1.0
BackgroundItem  {
    id: background
    anchors.left: ListView.left
    anchors.right: ListView.right
    contentHeight: Theme.itemSizeSmall+Theme.itemSizeSmall
    height: Theme.itemSizeSmall+Theme.itemSizeSmall

    property bool menuOpen: contextMenu != null && contextMenu.parent === background
    property Item contextMenu
    onClicked: {
    }

    function getTitleColor() {
        var color = Theme.primaryColor
        // If item selected either from list or Cover, make color highlighted
        if (background.highlighted ||
            (index === coverProxy.currentQuestion - 1)) {
            color = Theme.highlightColor
        }
        return color
    }

    Column{
        id: myListItem
        anchors.fill: parent
        anchors.leftMargin: Theme.paddingSmall
        anchors.rightMargin: Theme.paddingSmall
        Row {
            Label {
                id: labelDate
                font.pixelSize: Theme.fontSizeSmall
                //color: getTitleColor()
                //font.bold: model.title
                text: date
            }
            Item {
                id: fillRectangel
//                color: "transparent"
                width: background.width - labelDate.width - timesRectangle.width
                height: 40
            }

            // Created and updated time strings
            Rectangle {
                id: timesRectangle
                color: "transparent"
                width: 160
                height: 40
                Label {
                    font.pixelSize: Theme.fontSizeSmall
                    anchors.fill: parent
                    text: Number(sum).toLocaleCurrencyString(Qt.locale())
                }
            }
        }

        Label {
            id: labelTitle
            text: getAccountTitle()
            function getAccountTitle()
            {
                if (md5 == from)
                {
                    var o = modelAccounts.lookupByMd5(to)
                    if (!o)
                        return to

                    return o.title
                }
                else
                {
                    var o = modelAccounts.lookupByMd5(from)
                    if (!o)
                        return from

                    return o.title
                }
            }
        }

        Row {
            Label {
                id: labelType
                font.pixelSize: Theme.fontSizeSmall
                font.italic: true
                color: Theme.secondaryColor
                text: description
            }

            Item {
                id: fillRectangel2
                width: background.width - labelType.width - labelSum2.width
                height: 40
            }

            // Created and updated time strings
            Label {
                id: labelSum2
                width: 160
                height: 40
                font.pixelSize: Theme.fontSizeSmall
               // anchors.fill: parent
                text: Number(sum2).toLocaleCurrencyString(Qt.locale())
            }
        }
    }
}