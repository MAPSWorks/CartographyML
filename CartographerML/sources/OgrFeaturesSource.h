#ifndef _CARTOGRAPHERML_OGRFEATURESSOURCE_H_
#define _CARTOGRAPHERML_OGRFEATURESSOURCE_H_

#include "AbstractFeaturesSource.h"

namespace CartographerML
{
  class OgrFeaturesSource : public AbstractFeaturesSource
  {
    Q_OBJECT
    Q_PROPERTY(QString filename READ filename WRITE setFilename NOTIFY filenameChanged)
    Q_PROPERTY(QString errMsg READ errMsg NOTIFY errMsgChanged)
  public:
    OgrFeaturesSource();
    ~OgrFeaturesSource();
  public:
    Q_INVOKABLE virtual bool save();
    Q_INVOKABLE virtual bool load();
    QString errMsg() const;
    QString filename() const;
    void setFilename(const QString& _name);
  signals:
    void filenameChanged();
    void errMsgChanged();
  private:
    struct Private;
    Private* const d;
  };
}

#endif
