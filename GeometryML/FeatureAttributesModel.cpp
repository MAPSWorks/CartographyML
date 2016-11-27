#include "FeatureAttributesModel.h"

#include "Feature.h"

using namespace GeometryML;

struct FeatureAttributesModel::Private
{
  Feature* feature = nullptr;
  QVariantHash attributes;
  QStringList keys;
};

FeatureAttributesModel::FeatureAttributesModel(QObject* parent): QAbstractItemModel(parent), d(new Private)
{

}

FeatureAttributesModel::~FeatureAttributesModel()
{
  delete d;
}

Feature* FeatureAttributesModel::feature() const
{
  return d->feature;
}

void FeatureAttributesModel::setFeature(Feature* _feature)
{
  beginResetModel();
  d->feature = _feature;
  if(d->feature)
  {
    d->attributes = d->feature->attributes();
    d->keys = d->attributes.keys();
  } else {
    d->attributes.clear();
    d->keys.clear();
  }
  endResetModel();
}


QModelIndex FeatureAttributesModel::parent(const QModelIndex& child) const
{
  return QModelIndex();
}

int FeatureAttributesModel::columnCount(const QModelIndex& parent) const
{
  return 1;
}

QVariant FeatureAttributesModel::data(const QModelIndex& index, int role) const
{
  if(d->feature and index.isValid() and index.row() < d->keys.size() and index.column() < 1)
  {
    switch(role)
    {
      case KeyNameRole:
        return d->keys[index.row()];
      case ValueRole:
        return d->attributes.value(d->keys[index.row()]);
      default:
        return QVariant("invalid");
    }
  }
  return QVariant();
}

bool FeatureAttributesModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
  if(role != ValueRole or index.row() >= d->keys.size() or d->feature == nullptr) return QAbstractItemModel::setData(index, value, role);

  QString keyName = d->keys.at(index.row());
  QVariant normalized_value;
  QVariant current_value = d->attributes[keyName];
  
  switch(current_value.type())
  {
    case QVariant::Bool:
      normalized_value = value.toBool();
      break;
    case QVariant::Int:
      normalized_value = value.toInt();
      break;
    case QVariant::Double:
      normalized_value = value.toDouble();
      break;
    default:
      normalized_value = value.toString();
      break;
  }
  d->attributes[keyName] = normalized_value;
  d->feature->setAttribute(keyName, normalized_value);
  emit(dataChanged(index, index));
  return true;
}

QModelIndex FeatureAttributesModel::index(int row, int column, const QModelIndex& parent) const
{
  return hasIndex(row, column, parent) ? createIndex(row, column, nullptr) : QModelIndex();
}

int FeatureAttributesModel::rowCount(const QModelIndex& parent) const
{
  if(d->feature)
  {
    return d->keys.size();
  } else {
    return 0;
  }
}

QHash< int, QByteArray > FeatureAttributesModel::roleNames() const
{
  QHash< int, QByteArray > roles;
  roles[KeyNameRole]  = "keyName";
  roles[ValueRole]    = "value";
  return roles;
}

bool FeatureAttributesModel::isEditable(const QModelIndex& index, int role) const
{
  return role == ValueRole;
}

#include "moc_FeatureAttributesModel.cpp"
