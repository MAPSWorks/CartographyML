#ifndef _GEOMETRYML_FEATUREATTRIBUTESMODEL_H_
#define _GEOMETRYML_FEATUREATTRIBUTESMODEL_H_

#include <QAbstractItemModel>

namespace GeometryML
{
  class Feature;
  class FeatureAttributesModel : public QAbstractItemModel
  {
    Q_OBJECT
    Q_PROPERTY(GeometryML::Feature* feature READ feature WRITE setFeature NOTIFY featureChanged)
    enum Role
    {
       KeyNameRole = Qt::UserRole,
       ValueRole = Qt::UserRole + 1
    };
  public:
    explicit FeatureAttributesModel(QObject* parent = 0);
    virtual ~FeatureAttributesModel();
    Feature* feature() const;
    void setFeature(Feature* _feature);
    virtual int columnCount(const QModelIndex& parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    virtual bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
    virtual QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex& child) const;
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    virtual QHash< int, QByteArray > roleNames() const;
    Q_INVOKABLE bool isEditable(const QModelIndex& index, int role) const;
  signals:
    void featureChanged();
  private:
    struct Private;
    Private* const d;
  };
}

#endif
