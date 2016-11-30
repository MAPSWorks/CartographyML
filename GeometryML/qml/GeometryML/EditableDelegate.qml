import QtQuick 2.2
import QtQuick.Controls 1.2

Item
{
  property variant editableRoles: []
  function __is_editable(role)
  {
    return editableRoles.indexOf(role) >= 0
  }
  Text
  {
    width: parent.width
    anchors.margins: 4
    anchors.left: parent.left
    anchors.verticalCenter: parent.verticalCenter
    elide: styleData.elideMode
    text: styleData.value !== undefined ? styleData.value : ""
    color: styleData.textColor
    visible: !styleData.selected || !__is_editable(styleData.role)
  }

  Loader
  {
    id: loaderEditor
    anchors.fill: parent
    anchors.margins: 4
    Connections
    {
      target: loaderEditor.item
      onAccepted:
      {
        model[styleData.role] = loaderEditor.item.text
      }
    }
    sourceComponent: (styleData.selected && __is_editable(styleData.role)) ? editor : null
    Component
    {
      id: editor
      TextInput
      {
        id: textinput
        color: styleData.textColor
        text: styleData.value
        MouseArea
        {
          id: mouseArea
          anchors.fill: parent
          hoverEnabled: true
          onClicked: textinput.forceActiveFocus()
        }
      }
    }
  }
}
