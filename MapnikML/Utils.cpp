#include "Utils.h"

#include "UtilsAttachedProperty.h"

using namespace MapnikML;

UtilsAttachedProperty* Utils::qmlAttachedProperties(QObject* object)
{
  return new UtilsAttachedProperty(object);
}

