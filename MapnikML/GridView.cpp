#include "GridView.h"

using namespace MapnikML;

struct GridView::Private
{
  qreal verticalSpacing = 10.0;
  qreal horizontalSpacing = 10.0;
  SpacingMode spacingMode = SpacingMode::Pixels;
};

GridView::GridView(QQuickItem* parent) : QQuickPaintedItem(parent), d(new Private)
{
}

GridView::~GridView()
{
}

void GridView::paint(QPainter* painter)
{
}

    qreal verticalSpacing() const;
    void setVerticalSpacing(qreal _spacing);
    qreal horizontalSpacing() const;
    void setHorizontalSpacing(qreal _spacing);
    SpacingMode spacingMode() const;
    void setSpacingMode(SpacingMode _mode);



#include "moc_GridView.cpp"
