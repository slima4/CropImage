#include "boxitem.h"

CBoxItem::CBoxItem() :
    _size(40,40)
{
}

QRectF CBoxItem::boundingRect() const
{
    return QRectF(0, 0, _size.width(), _size.height());
}

void CBoxItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
           QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing, true);

    int width = _size.width();
    int height = _size.height();
    painter->drawRect(0, 0, width, height);
    painter->drawLine(width - 13, height, width, height - 13);
    painter->drawLine(width - 9, height, width, height - 9);
    painter->drawLine(width - 5, height, width, height - 5);
}

QSize CBoxItem::size() const
{
    return _size;
}

void CBoxItem::setSize(const QSize &size)
{
    _size = size;
}
