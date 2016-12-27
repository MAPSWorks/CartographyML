#ifndef _CARTOGRAPHERML_ABSTRACTOOL_H_
#define _CARTOGRAPHERML_ABSTRACTOOL_H_

#include <QObject>
#include <QQmlListProperty>

class QQmlComponent;

namespace MapnikML
{
  class MapView;
}

namespace CartographerML
{
  class AbstractFeaturesSource;
  class MouseToolEvent;
  class ProxyTool;
  class ToolController;
  class WheelToolEvent;
  class AbstractTool : public QObject
  {
    friend class ToolController;
    friend class ProxyTool;
    Q_OBJECT
    Q_PROPERTY(bool hoverEnabled READ isHoverEnabled WRITE setHoveredEnabled NOTIFY hoverEnabledChanged)
    Q_PROPERTY(CartographerML::AbstractFeaturesSource* featuresSource READ featuresSource WRITE setFeaturesSource NOTIFY featuresSourceChanged)
    Q_PROPERTY(MapnikML::MapView* mapView READ mapView WRITE setMapView NOTIFY mapViewChanged)
    Q_PROPERTY(QQmlComponent* optionsComponent READ optionsComponent WRITE setOptionsComponent NOTIFY optionsComponentChanged)
    Q_PROPERTY(QQmlComponent* overlayComponent READ overlayComponent WRITE setOverlayComponent NOTIFY overlayComponentChanged)
    Q_PROPERTY(QQmlListProperty<QObject> children READ childrenList)
    Q_CLASSINFO("DefaultProperty", "children")
  public:
    AbstractTool(QObject* _parent = 0);
    ~AbstractTool();
    bool isHoverEnabled() const;
    void setHoveredEnabled(bool _v);
    CartographerML::AbstractFeaturesSource* featuresSource() const;
    void setFeaturesSource(CartographerML::AbstractFeaturesSource* _source);
    MapnikML::MapView* mapView() const;
    void setMapView(MapnikML::MapView* _mapView);
    QQmlComponent* optionsComponent() const;
    void setOptionsComponent(QQmlComponent* _component);
    QQmlComponent* overlayComponent() const;
    void setOverlayComponent(QQmlComponent* _component);
  signals:
    void hoverEnabledChanged();
    void featuresSourceChanged();
    void optionsComponentChanged();
    void overlayComponentChanged();
    void mapViewChanged();
  protected:
    virtual void toolActivated();
    virtual void toolDeactivated();
    virtual void mouseDoubleClickEvent(MouseToolEvent* event);
    virtual void mouseMoveEvent(MouseToolEvent* event);
    virtual void mousePressEvent(MouseToolEvent* event);
    virtual void mouseReleaseEvent(MouseToolEvent* event);
    virtual void wheelEvent(WheelToolEvent* event);
  private:
    QQmlListProperty<QObject> childrenList() const;
    static void children_append(QQmlListProperty<QObject>* _list, QObject* _layer);
    static int children_count(QQmlListProperty<QObject>* _list);
    static QObject* children_at(QQmlListProperty<QObject>* _list, int _index);
    static void children_clear(QQmlListProperty<QObject>* _list);
  private:
    struct Private;
    Private* const d;
  };
}

#endif
