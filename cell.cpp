// #include "cell.h"
#include "graphicsscene.h"

Cell::Cell(qreal x,qreal y)
{
    MineNum = -2;
    Henso(CellStatus::ini);
    setPos(x,y);
}
Cell::~Cell()
{
};

void Cell::Henso(CellStatus NewStatus)
{
    switch (NewStatus)
    {
    case CellStatus::ini:
        status=CellStatus::ini;
        setPixmap(*GraphicsScene::ini);
        break;
    case CellStatus::flag:
        status=CellStatus::flag;
        setPixmap(*GraphicsScene::flag);
        break;
    case CellStatus::question:
        status=CellStatus::question;
        setPixmap(*GraphicsScene::question);
        break;
    default:
        break;
    }
}
void Cell::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void Cell::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        switch (status)
        {
        case CellStatus::ini:
            Henso(CellStatus::flag);
            break;
        case CellStatus::flag:
            Henso(CellStatus::question);
            break;
        case CellStatus::question:
            Henso(CellStatus::ini);
            break;
        default:
            break;
        }
    }
    else
    {
        switch (MineNum)
        {
        case -1:
            
            break;
        case 0:
            Henso(CellStatus::blank);            
            break;
        case 1:;
        case 2:;
        case 3:;
        case 4:;
        case 5:;
        case 6:;
        case 7:;
        case 8:Henso(CellStatus::num);
        default:
            break;
        }
    }
}
