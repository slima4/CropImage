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

protected:
    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);

    void contextMenuEvent(QContextMenuEvent *event);
    void timerEvent(QTimerEvent *event);

private:
    QGraphicsScene *_scene;

    CBoxItem *boxItem;
    QMenu *menu;

    bool itemSelected;
    bool resizeMode;
};

#endif // GRAPHICSVIEW_H
