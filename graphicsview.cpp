#include "graphicsview.h"
#include "boxitem.h"

#include <QFileDialog>

namespace {
    qint32 MIN_RESIZE = 50;
}

CGraphicsView::CGraphicsView(QWidget *parent) :
    QGraphicsView(parent),
    _boxItem(0),
    _itemSelected(false),
    _resizeMode(false)
{
    initMenu();

    _scene = new QGraphicsScene(this);
    setScene(_scene);
    scene();

    startTimer(1000 / 25);
}

void CGraphicsView::initMenu()
{
    _menu = new QMenu(this);

    QAction *action;

    action = new QAction(tr("Open Image"), this);
    connect(action, SIGNAL(triggered()), SLOT(onActionOpenImage()));
    _menu->addAction(action);

    action = new QAction(tr("Crop Box"), this);
    connect(action, SIGNAL(triggered()), SLOT(onActionCropImage()));
    _menu->addAction(action);

    _itemMenu = new QMenu(this);

    action = new QAction(tr("Save Image"), this);
    connect(action, SIGNAL(triggered()), SLOT(onActionSaveImage()));
    _itemMenu->addAction(action);
}

void CGraphicsView::mouseMoveEvent(QMouseEvent * event)
{
    QGraphicsView::mouseMoveEvent(event);

    if (_boxItem != 0)
    {
        if(!_itemSelected)
        {
            QPointF p = mapToScene(event->pos() - _boxItem->pos().toPoint());
            if(p.x() < MIN_RESIZE && p.y() > MIN_RESIZE)
                _boxItem->setSize(QSize(MIN_RESIZE, p.y()));

            if(p.x() > MIN_RESIZE && p.y() < MIN_RESIZE)
                _boxItem->setSize(QSize(p.x(), MIN_RESIZE));

            if(p.x() > MIN_RESIZE && p.y() > MIN_RESIZE)
                _boxItem->setSize(QSize(p.x(),p.y()));
        }
        else
        {
            QPointF p = (event->pos() - _offsetMove);
            _boxItem->setPos(p);
        }
    }
}

void CGraphicsView::mousePressEvent(QMouseEvent * event)
{
    QGraphicsView::mousePressEvent(event);

    if (QGraphicsItem * item = itemAt(event->pos()))
    {
        QRectF rect = item->sceneBoundingRect();
        rect.adjust(0,0, rect.x() - 10, rect.y() - 10);
        QPoint point = mapFromScene(rect.width(), rect.height());
        if( point.x() < event->pos().x() && point.y() < event->pos().y())
        {
            _resizeMode = true;
        }
        else
        {
            _offsetMove = event->pos() - item->pos().toPoint();
            _itemSelected = true;
        }
    }
}

void CGraphicsView::mouseReleaseEvent(QMouseEvent * event)
{
    QGraphicsView::mouseReleaseEvent(event);

    _resizeMode = false;
    _itemSelected = false;
}

void CGraphicsView::contextMenuEvent(QContextMenuEvent *event)
{
    _pointMenu = event->pos();

    QGraphicsItem * item = itemAt(_pointMenu);
    if (item != 0 && item->zValue() == 100)
        _itemMenu->exec(event->globalPos());
    else
        _menu->exec(event->globalPos());
}

void CGraphicsView::onActionOpenImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                 "/home",
                                                 tr("Images (*.png *.jpg)"));

    _pix.load(fileName);

    _scene->addPixmap(_pix);
}

void CGraphicsView::onActionCropImage()
{
    if ( _boxItem == 0)
    {
        _boxItem = new CBoxItem();
        _boxItem->setZValue(100);
        _boxItem->setPos(_pointMenu);
        _scene->addItem(_boxItem);
    }
}

void CGraphicsView::onActionSaveImage()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Fiel"),
                                 "/home/test.png",
                                 tr("Images (*.png *.jpg)"));

    QRect r(_boxItem->pos().toPoint(), _boxItem->size());
    _pix.copy(r).save(fileName);
}

void CGraphicsView::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    scene()->update();
}
