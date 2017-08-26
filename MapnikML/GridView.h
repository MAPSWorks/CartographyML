#ifndef _MAPNIKML_GRIDVIEW_H_
#define _MAPNIKML_GRIDVIEW_H_

#include <QQuickPaintedItem>

namespace MapnikML
{
  class GridView : public QQuickPaintedItem
  {
    Q_OBJECT
  public:
    enum class SpacingMode
    {
      MapUnit,  ///< Spacing is expressed in units from the map
      Pixels,   ///< Spacing is expressed in pixels
      PixelsRounded ///< Spacing is expressed in pixels, but rounded to the closest map unit
    };
    Q_ENUMS(SpacingMode)
    
    Q_PROPERTY(qreal verticalSpacing READ verticalSpacing WRITE setVerticalSpacing NOTIFY verticalSpacingChanged)
    Q_PROPERTY(qreal horizontalSpacing READ horizontalSpacing WRITE setHorizontalSpacing NOTIFY horizontalSpacingChanged)
    Q_PROPERTY(SpacingMode spacingMode READ spacingMode WRITE setSpacingMode NOTIFY spacingModeChanged)
    Q_PROPERTY(QColor mainColor READ mainColor WRITE setMainColor NOTIFY mainColorChanged)
    Q_PROPERTY(QColor secondaryColor READ secondaryColor WRITE setSecondaryColor NOTIFY secondaryColorChanged)
    Q_PROPERTY(int verticalSubdivisions READ verticalSubdivisions WRITE setVerticalSubdivisions NOTIFY verticalSubdivisionsChanged)
    Q_PROPERTY(int horizontalSubdivisions READ horizontalSubdivisions WRITE setHorizontalSubdivisions NOTIFY horizontalSubdivisionsChanged)
  public:
    explicit GridView(QQuickItem *parent = Q_NULLPTR);
    virtual ~GridView();
    virtual void paint(QPainter *painter);
    qreal verticalSpacing() const;
    void setVerticalSpacing(qreal _spacing);
    qreal horizontalSpacing() const;
    void setHorizontalSpacing(qreal _spacing);
    SpacingMode spacingMode() const;
    void setSpacingMode(SpacingMode _mode);
  signals:
    void verticalSpacingChanged();
    void horizontalSpacingChanged();
    void spacingModeChanged();
    void mainColorChanged();
    void secondaryColorChanged();
    void verticalSubdivisionsChanged();
    void horizontalSubdivisionsChanged();
  private:
    struct Private;
    Private* const d;
  };
}

#endif
