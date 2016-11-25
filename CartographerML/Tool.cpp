#include "Tool.h"

#include <QMouseEvent>

#include "ToolEvents.h"

using namespace CartographerML;

Tool::Tool(QObject* _parent): AbstractTool(_parent)
{

}

Tool::~Tool()
{

}

void Tool::mouseDoubleClickEvent(MouseToolEvent* event)
{
  emit(doubleClicked(event));
}

void Tool::mouseMoveEvent(MouseToolEvent* event)
{
  emit(moved(event));
}

void Tool::mousePressEvent(MouseToolEvent* event)
{
  emit(pressed(event));
}

void Tool::mouseReleaseEvent(MouseToolEvent* event)
{
  emit(released(event));
}

#include "moc_Tool.cpp"
