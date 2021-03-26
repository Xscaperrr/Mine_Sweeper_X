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