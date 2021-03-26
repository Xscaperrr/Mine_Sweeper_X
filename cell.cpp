#include "cell.h"

Cell::Cell(qreal x,qreal y)
{
    QPixmap *blank = new QPixmap("://images/blank.png");
    setPixmap(*blank);
    setPos(x,y);
}
Cell::~Cell()
{
};

void Cell::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    std::cout<<"ook!"<<std::endl;
   
    if (event->button() == Qt::RightButton)
    {
        QPixmap *flag = new QPixmap("://images/flag.png");
        setPixmap(*flag);
    }
}
void Cell::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
}
