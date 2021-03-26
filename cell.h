#ifndef CELL_H
#define CELL_H
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsSceneMouseEvent>  
#include <iostream>

class Cell : public QGraphicsPixmapItem 
{
public:
    Cell(qreal x,qreal y);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    ~Cell();
};

#endif // CELL_H