#include "graphicsscene.h"

QPixmap * GraphicsScene::blank=nullptr;//据考证，QPixmap类设定成全局变量有bug,所以采用指针,并且不在类外初始化以规避
QPixmap * GraphicsScene::flag=nullptr;
QPixmap * GraphicsScene::bomb=nullptr;
QPixmap * GraphicsScene::ini=nullptr;
QPixmap * GraphicsScene::question=nullptr;
QPixmap * GraphicsScene::clickable=nullptr;
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
int GraphicsScene::LeftMineNum=10;

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
    clickable=new QPixmap("://images/clickable.png");
    bomb=new QPixmap("://images/explode.png");
    num1=new QPixmap("://images/1.png");
    num2=new QPixmap("://images/2.png");
    num3=new QPixmap("://images/3.png");
    num4=new QPixmap("://images/4.png");
    num5=new QPixmap("://images/5.png");
    num6=new QPixmap("://images/6.png");
    num7=new QPixmap("://images/7.png");
    num8=new QPixmap("://images/8.png");

    TotalMineNum=10;
    cells.resize(row+2);//哨兵加入
    MineBlockSet();
}

void GraphicsScene::MineBlockSet(int x,int y)
{
    QVector<Cell*> cell_1d;
    int count=0;
    int ifm=-1;
    for(int i=0;i<=x+1;i++) 
        for(int j=0;j<=y+1;j++)
        {
            if(i>=1 && i<=row && j>=1 && j<=column)
            {
                if(count>=TotalMineNum) ifm=0;
                cells[i].push_back(new Cell(ifm));
                cell_1d.push_back(cells[i].back());
                addItem(cells[i].back());
                count++;
            }
            else cells[i].push_back(new Cell(CellStatus::kara));
        }

    std::default_random_engine e //便于调试取消真随机
    (std::time(0))
    ;
    

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
   for(auto& c:r) c->LeftRelease();
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

void GraphicsScene::GameRestart()
{
    for(auto& i:cells)
        for(auto& j:i)
            delete j;
    qDebug()<<"delete over";
    cells.clear();
    cells.resize(row+2);//哨兵加入
    Cell::nc=Cell::nr=1;
    MineBlockSet();
}

void GraphicsScene::AutoFlag()
{
    QList<Cell*> ActiveNum;//活跃数字队列，指周围有未翻开格子的数字格
    for(auto x=1;x<=row;x++)
        for(auto y=1;y<=column;y++)
            if(cells[x][y]->status == CellStatus::num)
            {
                int activity=0;//周围的未翻开格子数
                int flags=0;//周围的旗子数
                auto r=RoundCell(cells[x][y]);
                for(auto& c:r)//遍历周围格子计数
                {
                    if(c->status==CellStatus::ini) activity++;
                    if(c->status==CellStatus::flag) flags++;
                }
                if (activity == 0) continue;//非活跃
                if (cells[x][y]->MineNum == flags)//所有雷已经标记完,则将其他未翻开格子标记为无雷
                {
                    qDebug()<<"clickable around "<<(int)x<<(int)y;
                    for(auto& c:r)
                        if(c->status==CellStatus::ini) c->Henso(CellStatus::clickable);
                }
                else if (activity ==cells[x][y]->MineNum - flags)//未翻开格子数 == 周围雷数，则全部标雷雷
                {
                    qDebug()<<"flag around "<<(int)x<<(int)y;
                    for(auto& c:r)
                        if(c->status==CellStatus::ini) c->Henso(CellStatus::flag);
                }
                else ActiveNum.push_back(cells[x][y]);//活跃但无法确定周遭状态
            }
    bool IfAct=true;//在队列的一轮遍历时是否有处理
    while(IfAct)
    {
        IfAct=false;
        for(auto i=ActiveNum.begin();i !=ActiveNum.end();)
        {
            qDebug()<<"acess "<<(int)(*i)->nx<<(int)(*i)->ny;
            int activity=0;
            int flags=0;
            auto r=RoundCell(*i);
            for(auto& c:r)
            {
                if(c->status==CellStatus::ini) activity++;
                if(c->status==CellStatus::flag) flags++;
            }
            if (activity == 0)//已经不活跃
            {
                qDebug()<<"release "<<(int)(*i)->nx<<(int)(*i)->ny;
                i=ActiveNum.erase(i);
            }
            else if ((*i)->MineNum == flags)//周围可标无雷
            {
                IfAct=true;
                qDebug()<<"clickable around "<<(int)(*i)->nx<<(int)(*i)->ny;
                
                for(auto& c:r)
                    if(c->status==CellStatus::ini) c->Henso(CellStatus::clickable);

                i=ActiveNum.erase(i);
            }
            else if (activity ==(*i)->MineNum - flags )//周围可标雷
            {
                IfAct=true;
                qDebug()<<"flag around "<<(int)(*i)->nx<<(int)(*i)->ny;
                for(auto& c:r)
                    if(c->status==CellStatus::ini) c->Henso(CellStatus::flag);
                i=ActiveNum.erase(i);
            }
            else i++;
        }
    }
}
void GraphicsScene::CalProbability()//概率计算
{
    QList<Cell*> ActiveNum;//活跃数字队列，指周围有未翻开格子的数字格
    for(auto x=1;x<=row;x++)
        for(auto y=1;y<=column;y++)
            if(cells[x][y]->status == CellStatus::num)
            {
                int activity=0;//周围的未翻开格子数
                int flags=0;//周围的旗子数
                auto r=RoundCell(cells[x][y]);
                for(auto& c:r)//遍历周围格子计数
                {
                    if(c->status==CellStatus::ini) activity++;
                    if(c->status==CellStatus::flag) flags++;
                }
                if (activity == 0) continue;//非活跃
                if (cells[x][y]->MineNum == flags)//所有雷已经标记完,则将其他未翻开格子标记为无雷
                {
                    qDebug()<<"clickable around "<<(int)x<<(int)y;
                    for(auto& c:r)
                        if(c->status==CellStatus::ini) c->Henso(CellStatus::clickable);
                }
                else if (activity ==cells[x][y]->MineNum - flags)//未翻开格子数 == 周围雷数，则全部标雷雷
                {
                    qDebug()<<"flag around "<<(int)x<<(int)y;
                    for(auto& c:r)
                        if(c->status==CellStatus::ini) c->Henso(CellStatus::flag);
                }
                else ActiveNum.push_back(cells[x][y]);//活跃但无法确定周遭状态
            }
    bool IfAct=true;//在队列的一轮遍历时是否有处理
    while(IfAct)
    {
        IfAct=false;
        for(auto i=ActiveNum.begin();i !=ActiveNum.end();)
        {
            qDebug()<<"acess "<<(int)(*i)->nx<<(int)(*i)->ny;
            int activity=0;
            int flags=0;
            auto r=RoundCell(*i);
            for(auto& c:r)
            {
                if(c->status==CellStatus::ini) activity++;
                if(c->status==CellStatus::flag) flags++;
            }
            if (activity == 0)//已经不活跃
            {
                qDebug()<<"release "<<(int)(*i)->nx<<(int)(*i)->ny;
                i=ActiveNum.erase(i);
            }
            else if ((*i)->MineNum == flags)//周围可标无雷
            {
                IfAct=true;
                qDebug()<<"clickable around "<<(int)(*i)->nx<<(int)(*i)->ny;
                
                for(auto& c:r)
                    if(c->status==CellStatus::ini) c->Henso(CellStatus::clickable);

                i=ActiveNum.erase(i);
            }
            else if (activity ==(*i)->MineNum - flags )//周围可标雷
            {
                IfAct=true;
                qDebug()<<"flag around "<<(int)(*i)->nx<<(int)(*i)->ny;
                for(auto& c:r)
                    if(c->status==CellStatus::ini) c->Henso(CellStatus::flag);
                i=ActiveNum.erase(i);
            }
            else i++;
        }
    }
    //简单标旗结束
    QList<Cell*> AllNum,//全部数字格，用于回溯的错误判断
                ActiveIni;//活跃的未翻开格，指周围有数字的未翻开格
    int InactiveIniNum=0;//非活跃未翻开格数
    for(auto x=1;x<=row;x++)
        for(auto y=1;y<=column;y++)
            if(cells[x][y]->status == CellStatus::num) AllNum.push_back(cells[x][y]);
            else if(cells[x][y]->status == CellStatus::ini)
            {
                bool IfNum=false;
                auto r=RoundCell(cells[x][y]);
                for(auto& c:r)
                    if(c->status==CellStatus::num)
                    {
                        IfNum=true;
                        break;
                    }
                if(IfNum) ActiveIni.push_back(cells[x][y]);
                else InactiveIniNum++;
            }
}
GraphicsScene::~GraphicsScene()
{
}