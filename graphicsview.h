#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QMenu>

class CBoxItem;

class CGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    CGraphicsView(QWidget *parent = 0);

public slots:
    void onActionOpenImage();
    void onActionCropImage();
    void onActionSaveImage();

protected:
    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);

    void contextMenuEvent(QContextMenuEvent *event);
    void timerEvent(QTimerEvent *event);

private:
    void initMenu();

private:
    QGraphicsScene *_scene;
    QPixmap _pix;

    CBoxItem *_boxItem;
    QMenu *_menu;
    QMenu *_itemMenu;

    QPoint _pointMenu;
    QPoint _offsetMove;

    bool _itemSelected;
    bool _resizeMode;
};

#endif // GRAPHICSVIEW_H
