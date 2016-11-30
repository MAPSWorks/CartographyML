import QtQuick.Controls 1.2
import GeometryML 1.0

TableView
{
  id: root
  itemDelegate: EditableDelegate { editableRoles: ["value"] }
  property alias feature: model.feature
  signal featureAttributesChanged()
  model: FeatureAttributesModel
  {
    id: model
    feature: tool.feature
    onDataChanged: root.featureAttributesChanged()
  }
  TableViewColumn {
      role: "keyName"
      title: "Name"
      width: 100
  }
  TableViewColumn {
      role: "value"
      title: "Value"
      width: 200
  }
}
