#include "itemground.h"

ItemGround::ItemGround(QRectF rect, QObject* parent)
    : QObject(parent), QGraphicsRectItem(rect) {}
