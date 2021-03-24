#ifndef CELL_H
#define CELL_H
#include <QGraphicsPixmapItem>
#include <QPixmap>

class Cell : public QGraphicsPixmapItem 
{
public:
    Cell(qreal x,qreal y);
    ~Cell();
};

#endif // CELL_H