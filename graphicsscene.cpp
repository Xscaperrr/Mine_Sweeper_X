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

const QVector<QPair<int,int>> RoundStep
                        {
                            QPair<int,int>(-1,-1),
                            QPair<int,int>(-1,-0),
                            QPair<int,int>(-1,1),
                            QPair<int,int>(0,-1),
                            QPair<int,int>(0,1),
                            QPair<int,int>(1,-1),
                            QPair<int,int>(1,0),
                            QPair<int,int>(1,1)
                        };
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
    cells.resize(row+2);//哨兵加入
    MineBlockSet();
}

void GraphicsScene::MineBlockSet(int x,int y)
{
    //std::vector<Cell*> cell_1d;
    QVector<Cell*> cell_1d;
    int count=0;
    int ifm=-1;
    for(int i=0;i<=x+1;i++) 
        for(int j=0;j<=y+1;j++)
        {
            if(i>=1 && i<=row && j>=1 && j<=column)
            {
                if(count>=mines) ifm=0;
                cells[i].push_back(new Cell(ifm));
                cell_1d.push_back(cells[i].back());
                addItem(cells[i].back());
                count++;
            }
            else cells[i].push_back(new Cell(CellStatus::kara));
        }

    std::default_random_engine e(std::time(0));
    //std::default_random_engine e;

    for(int i=0;i<x*y;i++)
    {
        std::uniform_int_distribution<int> u(i,x*y-1);
        cell_1d[i]->SwapMine(*cell_1d[u(e)]);
    }

    for(int i=1;i<=x;i++)
        for(int j=1;j<=y;j++)
            if(cells[i][j]->IfMine() != 1)
            {
                auto r=RoundCell(cells[i][j]);
                for(auto& c:r) cells[i][j]->MineNum+=c->IfMine();
            }
            
    //未加哨兵的朴素算法
    // if(cells[0][0]->MineNum != -1) cells[0][0]->MineNum=cells[0][1]->IfMine()+cells[1][0]->IfMine()+cells[1][1]->IfMine();
    // //qDebug()<<(int)cells[0][0]->MineNum;
    // if(cells[0][y-1]->MineNum != -1) cells[0][y-1]->MineNum=(cells[0][y-2]->IfMine()+cells[1][y-1]->IfMine()+cells[1][y-2]->IfMine());
    // //qDebug()<<(int)cells[0][y-1]->MineNum;
    // if(cells[x-1][0]->MineNum != -1) cells[x-1][0]->MineNum=(cells[x-1][1]->IfMine()+cells[x-2][0]->IfMine()+cells[x-2][1]->IfMine());
    // //qDebug()<<(int)cells[x-1][0]->MineNum;
    // if(cells[x-1][y-1]->MineNum != -1) cells[x-1][y-1]->MineNum=(cells[x-2][y-1]->IfMine()+cells[x-1][y-2]->IfMine()+cells[x-2][y-2]->IfMine());
    // //qDebug()<<(int)cells[x-1][y-1]->MineNum;
    // for(int i=1;i<y-1;i++) 
    // { 
    //     if(cells[0][i]->MineNum != -1) cells[0][i]->MineNum=(cells[0][i-1]->IfMine()+cells[0][i+1]->IfMine()+cells[1][i]->IfMine()+cells[1][i-1]->IfMine()+cells[1][i+1]->IfMine());
    //     if(cells[x-1][i]->MineNum != -1) cells[x-1][i]->MineNum=(cells[x-1][i-1]->IfMine()+cells[x-1][i+1]->IfMine()+cells[x-2][i]->IfMine()+cells[x-2][i-1]->IfMine()+cells[x-2][i+1]->IfMine());
    // }
    // for(int i=1;i<x-1;i++)
    // {
    //     if(cells[i][0]->MineNum != -1) cells[i][0]->MineNum=(cells[i-1][0]->IfMine()+cells[i+1][0]->IfMine()+cells[i][1]->IfMine()+cells[i-1][1]->IfMine()+cells[i+1][1]->IfMine());
    //     if(cells[i][y-1]->MineNum != -1) cells[i][y-1]->MineNum=(cells[i-1][y-1]->IfMine()+cells[i+1][y-1]->IfMine()+cells[i][y-2]->IfMine()+cells[i-1][y-2]->IfMine()+cells[i+1][y-2]->IfMine());
    // }
    // for(int i=1;i<x-1;i++)
    //     for(int j=1;j<y-1;j++)
    //     {
    //         if(cells[i][j]->MineNum != -1)
    //         {
    //             cells[i][j]->MineNum=cells[i-1][j-1]->IfMine()+cells[i-1][j]->IfMine()+cells[i-1][j+1]->IfMine()+cells[i][j-1]->IfMine()+cells[i][j+1]->IfMine()
    //             +cells[i+1][j-1]->IfMine()+cells[i+1][j]->IfMine()+cells[i+1][j+1]->IfMine();
    //         }
    //     }   
}

//获取周围的有效Cell的指针数组
QVector<Cell*> GraphicsScene::RoundCell(Cell* c)
{
    QVector<Cell*> res;
    for(auto& p:RoundStep)
    {
        if(cells[c->nx+p.first][c->ny+p.second]->status != CellStatus::kara)
        res.push_back(cells[c->nx+p.first][c->ny+p.second]);
    }
    return res;
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
    cells[x][y]->Henso(CellStatus::blank);
   auto r=RoundCell(cells[x][y]);
   for(auto& c:r) c->RightRelease();
}

bool GraphicsScene::FlagCheck()
{
    for(auto x=1;x<=row;x++)
        for(auto y=1;y<=column;y++)
            if(cells[x][y]->status == CellStatus::flag && cells[x][y]->MineNum != -1) return false;
    return true;
}

void GraphicsScene::FlagCheckEvent()
{
    if (FlagCheck()) QMessageBox::information(NULL, tr("标旗正确性检查"), tr("正确"));
    else QMessageBox::information(NULL, tr("标旗正确性检查"), tr("不正确"));
}
void GraphicsScene::AutoFlag()
{
    QList<Cell*> ActiveNum;
    for(auto x=1;x<=row;x++)
        for(auto y=1;y<=column;y++)
            if(cells[x][y]->status == CellStatus::num)
            {
                int activity=0;
                int flags=0;
                auto r=RoundCell(cells[x][y]);
                for(auto& c:r)
                {
                    if(c->status==CellStatus::ini) activity++;
                    if(c->status==CellStatus::flag) flags++;
                }
                if (cells[x][y]->MineNum == flags)
                {
                    for(auto& c:r)
                        if(c->status==CellStatus::ini) c->Henso(CellStatus::question);
                }
                else if (activity ==cells[x][y]->MineNum - flags)
                {
                    for(auto& c:r)
                        if(c->status==CellStatus::ini) c->Henso(CellStatus::flag);
                }
                else if (activity != 0) ActiveNum.push_back(cells[x][y]);
            }
    bool IfFlag=true;
    while(IfFlag)
    {
        IfFlag=false;
        for(auto i=ActiveNum.begin();i !=ActiveNum.end();i++)
        {
            int activity=0;
            int flags=0;
            auto r=RoundCell(*i);
            for(auto& c:r)
            {
                if(c->status==CellStatus::ini) activity++;
                if(c->status==CellStatus::flag) flags++;
            }
            if ((*i)->MineNum == flags)
            {
                IfFlag=true;
                for(auto& c:r)
                    if(c->status==CellStatus::ini) c->Henso(CellStatus::question);
            }
            else if (activity ==(*i)->MineNum - flags )
            {
                IfFlag=true;
                ActiveNum.erase(i);
                for(auto& c:r)
                    if(c->status==CellStatus::ini) c->Henso(CellStatus::flag);
            }
        }
    }
}

GraphicsScene::~GraphicsScene()
{
}