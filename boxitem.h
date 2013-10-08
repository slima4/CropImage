#ifndef BOXITEM_H
#define BOXITEM_H

#include <QGraphicsItem>
#include <QPainter>

class CBoxItem : public QGraphicsItem
{
public:
    CBoxItem();

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    QSize size() const;
    void setSize(const QSize &size);

private:
    QSize _size;
};

#endif // BOXITEM_H
