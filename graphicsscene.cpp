#include "graphicsscene.h"

QPixmap * GraphicsScene::blank=nullptr;//据考证，QPixmap类设定成全局变量有bug,所以采用指针,并且不在类外初始化以规避
QPixmap * GraphicsScene::flag=nullptr;
QPixmap * GraphicsScene::bomb=nullptr;
QPixmap * GraphicsScene::ini=nullptr;
QPixmap * GraphicsScene::question=nullptr;
QPixmap * GraphicsScene::num1=nullptr;
QPixmap * GraphicsScene::num2=nullptr;
QPixmap * GraphicsScene::num3=nullptr;
QPixmap * GraphicsScene::num4=nullptr;
QPixmap * GraphicsScene::num5=nullptr;
QPixmap * GraphicsScene::num6=nullptr;
QPixmap * GraphicsScene::num7=nullptr;
QPixmap * GraphicsScene::num8=nullptr;
QPixmap * GraphicsScene::num9=nullptr;

std::vector<std::vector<Cell*>> GraphicsScene::cells;

char GraphicsScene::row=9;
char GraphicsScene::column=9;

GraphicsScene::GraphicsScene(QObject *parent) : QGraphicsScene(parent)
{
    blank=new QPixmap("://images/blank.png");  
    flag=new QPixmap("://images/flag.png");
    ini=new QPixmap("://images/initial.png");
    question=new QPixmap("://images/question.png");
    bomb=new QPixmap("://images/explode.png");
    num1=new QPixmap("://images/1.png");
    num2=new QPixmap("://images/2.png");
    num3=new QPixmap("://images/3.png");
    num4=new QPixmap("://images/4.png");
    num5=new QPixmap("://images/5.png");
    num6=new QPixmap("://images/6.png");
    num7=new QPixmap("://images/7.png");
    num8=new QPixmap("://images/8.png");

    mines=10;
    cells.resize(9);
    MineBlockSet();
}

void GraphicsScene::MineBlockSet(int x,int y)
{
    std::vector<Cell*> cell_1d;
    int count=0;
    int ifm=-1;
    for(int i=0;i<x;i++) 
        for(int j=0;j<y;j++)
        {
            if(count>=mines) ifm=0;
            cells[i].push_back(new Cell(ifm));
            cell_1d.push_back(cells[i].back());
            addItem(cells[i].back());
            count++;
        }
    //std::default_random_engine e(std::time(0));
    std::default_random_engine e;
    for(int i=0;i<x*y;i++)
    {
        std::uniform_int_distribution<int> u(i,x*y-1);
        cell_1d[i]->SwapMine(*cell_1d[u(e)]);
    }
    if(cells[0][0]->MineNum != -1) cells[0][0]->MineNum=cells[0][1]->IfMine()+cells[1][0]->IfMine()+cells[1][1]->IfMine();
    //qDebug()<<(int)cells[0][0]->MineNum;
    if(cells[0][y-1]->MineNum != -1) cells[0][y-1]->MineNum=(cells[0][y-2]->IfMine()+cells[1][y-1]->IfMine()+cells[1][y-2]->IfMine());
    //qDebug()<<(int)cells[0][y-1]->MineNum;
    if(cells[x-1][0]->MineNum != -1) cells[x-1][0]->MineNum=(cells[x-1][1]->IfMine()+cells[x-2][0]->IfMine()+cells[x-2][1]->IfMine());
    //qDebug()<<(int)cells[x-1][0]->MineNum;
    if(cells[x-1][y-1]->MineNum != -1) cells[x-1][y-1]->MineNum=(cells[x-2][y-1]->IfMine()+cells[x-1][y-2]->IfMine()+cells[x-2][y-2]->IfMine());
    //qDebug()<<(int)cells[x-1][y-1]->MineNum;
    for(int i=1;i<y-1;i++) 
    { 
        if(cells[0][i]->MineNum != -1) cells[0][i]->MineNum=(cells[0][i-1]->IfMine()+cells[0][i+1]->IfMine()+cells[1][i]->IfMine()+cells[1][i-1]->IfMine()+cells[1][i+1]->IfMine());
        if(cells[x-1][i]->MineNum != -1) cells[x-1][i]->MineNum=(cells[x-1][i-1]->IfMine()+cells[x-1][i+1]->IfMine()+cells[x-2][i]->IfMine()+cells[x-2][i-1]->IfMine()+cells[x-2][i+1]->IfMine());
    }
    for(int i=1;i<x-1;i++)
    {
        if(cells[i][0]->MineNum != -1) cells[i][0]->MineNum=(cells[i-1][0]->IfMine()+cells[i+1][0]->IfMine()+cells[i][1]->IfMine()+cells[i-1][1]->IfMine()+cells[i+1][1]->IfMine());
        if(cells[i][y-1]->MineNum != -1) cells[i][y-1]->MineNum=(cells[i-1][y-1]->IfMine()+cells[i+1][y-1]->IfMine()+cells[i][y-2]->IfMine()+cells[i-1][y-2]->IfMine()+cells[i+1][y-2]->IfMine());
    }
    for(int i=1;i<x-1;i++)
        for(int j=1;j<y-1;j++)
        {
            if(cells[i][j]->MineNum != -1)
            {
                cells[i][j]->MineNum=cells[i-1][j-1]->IfMine()+cells[i-1][j]->IfMine()+cells[i-1][j+1]->IfMine()+cells[i][j-1]->IfMine()+cells[i][j+1]->IfMine()
                +cells[i+1][j-1]->IfMine()+cells[i+1][j]->IfMine()+cells[i+1][j+1]->IfMine();
            }
        }   
}



void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent  *event)
{
    QGraphicsScene::mousePressEvent(event);
}
void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent  *event)
{
    QGraphicsScene::mouseReleaseEvent(event);
}

void GraphicsScene::BlankProcess(int x,int y)
{
    cells[x-1][y-1]->Henso(CellStatus::blank);
    //qDebug()<<x<<' '<<y;
    for (int i=-1;i<2;i++)
        for (int j=-1;j<2;j++)
            if((x-1+i>=0)&&(x-1+i<row)&&(y-1+j>=0)&&(y-1+j<column)) 
                cells[x-1+i][y-1+j]->RightRelease();
                //qDebug()<<x-1+i<<' '<<y-1+j;
}
GraphicsScene::~GraphicsScene()
{
}