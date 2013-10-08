#include "graphicsview.h"
#include "boxitem.h"

#include <QFileDialog>

CGraphicsView::CGraphicsView(QWidget *parent) :
    QGraphicsView(parent),
    boxItem(0),
    itemSelected(false),
    resizeMode(false)
{
    menu = new QMenu(this);

    QAction *action;

    action = new QAction(tr("Open Image"), this);
    connect(action, SIGNAL(triggered()), SLOT(onActionOpenImage()));
    menu->addAction(action);

    action = new QAction(tr("Crop"), this);
    connect(action, SIGNAL(triggered()), SLOT(onActionCropImage()));
    menu->addAction(action);

    _scene = new QGraphicsScene(this);
    setScene(_scene);
    startTimer(1000 / 25);
}

void CGraphicsView::mouseMoveEvent(QMouseEvent * event)
{
    if (boxItem != 0)
    {
        QPointF p = mapToScene(event->pos());
        if(itemSelected)
            boxItem->setPos(p);
        else
            boxItem->setSize(QSize(p.x(),p.y()));
    }
    QGraphicsView::mouseMoveEvent(event);
}

void CGraphicsView::mousePressEvent(QMouseEvent * event)
{
    if (QGraphicsItem * item = itemAt(event->pos()))
    {
        QRectF rect = item->sceneBoundingRect();
        rect.adjust(0,0, rect.x() - 20, rect.y() - 20);
        QPoint point = mapFromScene(rect.width(), rect.height());
        if( point.x() < event->pos().x() && point.y() < event->pos().y())
        {
            resizeMode = true;
        }
        else
        {
            itemSelected = true;
        }
    }
    QGraphicsView::mousePressEvent(event);
}

void CGraphicsView::mouseReleaseEvent(QMouseEvent * event)
{
    resizeMode = false;
    itemSelected = false;
    QGraphicsView::mouseReleaseEvent(event);
}

void CGraphicsView::contextMenuEvent(QContextMenuEvent *event)
{
    menu->exec(event->globalPos());
}

void CGraphicsView::onActionOpenImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                 "/home",
                                                 tr("Images (*.png *.jpg)"));

    QPixmap pix;
    pix.load(fileName);

    _scene->addPixmap(fileName);
}

void CGraphicsView::onActionCropImage()
{
    if ( boxItem == 0)
    {
        boxItem = new CBoxItem();
        _scene->addItem(boxItem);
    }
}

void CGraphicsView::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    QListIterator<QGraphicsItem*> it(scene()->items());
    while(it.hasNext())
    {
        it.next()->update();
    }
}
