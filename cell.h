#ifndef CELL_H
#define CELL_H
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QMouseEvent>
class Cell : public QGraphicsPixmapItem 
{
public:
    Cell(qreal x,qreal y);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    ~Cell();
};

#endif // CELL_H