#ifndef _CARTOGRAPHERML_ABSTRACTOOL_H_
#define _CARTOGRAPHERML_ABSTRACTOOL_H_

#include <QObject>

class QQmlComponent;

namespace CartographerML
{
  class AbstractFeaturesSource;
  class MouseToolEvent;
  class ToolController;
  class WheelToolEvent;
  class AbstractTool : public QObject
  {
    friend class ToolController;
    Q_OBJECT
    Q_PROPERTY(bool hoverEnabled READ isHoverEnabled WRITE setHoveredEnabled NOTIFY hoverEnabledChanged)
    Q_PROPERTY(CartographerML::AbstractFeaturesSource* featuresSource READ featuresSource WRITE setFeaturesSource NOTIFY featuresSourceChanged)
    Q_PROPERTY(QQmlComponent* optionsComponent READ optionsComponent WRITE setOptionsComponent NOTIFY optionsComponentChanged)
    Q_PROPERTY(QQmlComponent* overlayComponent READ overlayComponent WRITE setOverlayComponent NOTIFY overlayComponentChanged)
  public:
    AbstractTool(QObject* _parent = 0);
    ~AbstractTool();
    bool isHoverEnabled() const;
    void setHoveredEnabled(bool _v);
    CartographerML::AbstractFeaturesSource* featuresSource() const;
    void setFeaturesSource(CartographerML::AbstractFeaturesSource* _source);
    QQmlComponent* optionsComponent() const;
    void setOptionsComponent(QQmlComponent* _component);
    QQmlComponent* overlayComponent() const;
    void setOverlayComponent(QQmlComponent* _component);
  signals:
    void hoverEnabledChanged();
    void featuresSourceChanged();
    void optionsComponentChanged();
    void overlayComponentChanged();
  protected:
    virtual void toolActivated();
    virtual void toolDeactivated();
    virtual void mouseDoubleClickEvent(MouseToolEvent* event);
    virtual void mouseMoveEvent(MouseToolEvent* event);
    virtual void mousePressEvent(MouseToolEvent* event);
    virtual void mouseReleaseEvent(MouseToolEvent* event);
    virtual void wheelEvent(WheelToolEvent* event);
  private:
    struct Private;
    Private* const d;
  };
}

#endif
