#include "cell.h"

Cell::Cell(qreal x,qreal y)
{
    QPixmap *blank = new QPixmap("://images/blank.png");
    setPixmap(blank->scaled(50,50));
    setPos(x,y);
}
Cell::~Cell()
{
};