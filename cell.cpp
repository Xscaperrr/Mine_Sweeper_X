// #include "cell.h"
#include "graphicsscene.h"
#include "mainwindow.h"

// char Cell::row=9;
// char Cell::column=9;
char Cell::nc=1;
char Cell::nr=1;
char Cell::pix=50;

Cell::Cell(char x):Cell(nc,nr,x)
{
    nx=nc;ny=nr;
    if(nr==GraphicsScene::row)
    {
        nr=1;
        nc++;
    }
    else
    {
        nr++;
    }
}
Cell::Cell(int x,int y,char k)
:QGraphicsPixmapItem(*GraphicsScene::ini),
nx(x),ny(y),MineNum(k),status(CellStatus::ini)
//构造函数
{
    // MineNum = k;
    // status=CellStatus::ini;
    setPos((x-1)*pix,(y-1)*pix);
}
Cell::Cell(CellStatus s)
{
    status=CellStatus::kara;
}
Cell::~Cell()
{
};
void Cell::SwapMine(Cell& x)
{
    if(MineNum!=-1 and x.MineNum!=-1) return;
    else std::swap(MineNum,x.MineNum);
}

void Cell::Henso(CellStatus NewStatus)
{
    if(status ==CellStatus::flag)
    {
        GraphicsScene::LeftMineNum ++;
        MainWindow::LeftMines->setText("剩余雷数:"+QString::number(GraphicsScene::LeftMineNum));
    }
    switch (NewStatus)
    {
    case CellStatus::ini:
        status=CellStatus::ini;
        setPixmap(*GraphicsScene::ini);
        break;
    case CellStatus::flag:
        status=CellStatus::flag;
        setPixmap(*GraphicsScene::flag);
        GraphicsScene::LeftMineNum --;
        MainWindow::LeftMines->setText("剩余雷数:"+QString::number(GraphicsScene::LeftMineNum));
        break;
    case CellStatus::question:
        status=CellStatus::question;
        setPixmap(*GraphicsScene::question);
        break;
    case CellStatus::bomb:
        status=CellStatus::bomb;
        setPixmap(*GraphicsScene::bomb);
        break;
    case CellStatus::blank:
        status=CellStatus::blank;
        setPixmap(*GraphicsScene::blank);
        break;
    case CellStatus::clickable:
        status=CellStatus::clickable;
        setPixmap(*GraphicsScene::clickable);
        break;
    case CellStatus::num:
        status=CellStatus::num;
        switch (MineNum)
        {
        case 1:
            setPixmap(*GraphicsScene::num1);
            break;
        case 2:
            setPixmap(*GraphicsScene::num2);
            break;
        case 3:
            setPixmap(*GraphicsScene::num3);
            break;
        case 4:
            setPixmap(*GraphicsScene::num4);
            break;
        case 5:
            setPixmap(*GraphicsScene::num5);
            break;
        case 6:
            setPixmap(*GraphicsScene::num6);
            break;
        case 7:
            setPixmap(*GraphicsScene::num7);
            break;
        case 8:
            setPixmap(*GraphicsScene::num8);
            break;
        default:
            break;
        }
        break;
    case CellStatus::kara:
        Henso(status);
        break;
    }
    status=NewStatus;
}
void Cell::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(status != CellStatus::num && status != CellStatus::blank) GraphicsScene::RedoTip(); 
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
        LeftRelease();//为了自动扩展拆分
        GraphicsScene::WinCheck();
    }
}
void Cell::LeftRelease()
{
    if(status == CellStatus::ini || status == CellStatus::clickable)
    {
        switch (MineNum)
            {
            case -1:
                Henso(CellStatus::bomb);
                break;
            case 0:
                //Henso(CellStatus::blank);            
                GraphicsScene::BlankProcess(nx,ny);
                break;
            case 1:;
            case 2:;
            case 3:;
            case 4:;
            case 5:;
            case 6:;
            case 7:;
            case 8:
                Henso(CellStatus::num);
                break;
            default:
                qDebug()<<"error!!!!!";
                break;
            }
    }
}
char Cell::IfMine()
{
    if(MineNum==-1) return 1;
    else return 0;
}

void Cell::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    //setToolTip("try");
    QToolTip::showText(event->screenPos(), toolTip());
    //std::cout<<"triggered!\n";
}
void Cell::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QToolTip::showText(event->screenPos(), toolTip());}
void Cell::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QToolTip::hideText();
}