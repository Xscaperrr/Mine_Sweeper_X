#include "graphicsscene.h"
#include "mainwindow.h"

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

QStack<Cell*> GraphicsScene::RedoTipList;
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

int Fac(int n)
{
    int Ans=1;
    while(n >=2)
    {
        Ans*=n;
        n--;
    }
    return Ans;
}
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
                cells[i].push_back(new Cell(i,j,ifm));
                cell_1d.push_back(cells[i].back());
                addItem(cells[i].back());
                count++;
            }
            else cells[i].push_back(new Cell(CellStatus::kara));
        }
    time_t seed=
    time(0)
    //1618564101
    
    ;
    qDebug()<<"seed:"<<seed;
    std::default_random_engine e(seed);
    

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
void GraphicsScene::update(const QRectF &rect)
{
    MainWindow::LeftMines->setText("剩余雷数:"+QString::number(LeftMineNum));
    QGraphicsScene::update(rect);
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
    qDebug()<<"Restart!";
    cells.clear();
    cells.resize(row+2);//哨兵加入
    Cell::nc=Cell::nr=1;
    LeftMineNum=TotalMineNum;
    MineBlockSet();
}
bool GraphicsScene::ProbeCheck(const QList<Cell*>& AllNum)
{
    for(auto& i:AllNum)
    {
        auto r=RoundCell(i);
        int flags=0;
        int inis=0;
        for(auto& c:r)
            {
                if(c->status == CellStatus::ini) inis++;
                if(c->status == CellStatus::flag) flags++;
            }
        if(( flags > i->MineNum )||( inis+flags < i->MineNum )) 
            return false;
    }
    return true;
}

void GraphicsScene::Recover(QStack<Cell*>& rec)
{
    while(!rec.empty())
        {
            rec.top()->Henso(CellStatus::ini);
            rec.pop();
        }
}
void GraphicsScene::Probe(QList<Cell*>& ActiveIni,QList<Cell*>& ActiveNum,ProbeResult& Result)
{
    QList<Cell *>::iterator it=ActiveIni.begin();
    while(!Probe(it,ActiveIni,ActiveNum,Result))
    {
        it++;
    }
}
bool GraphicsScene::Probe
(
const QList<Cell *>::iterator& it,//只是当前试探位置，除非删除不做任何更改
const QList<Cell*>& ActiveIni,//从第一次Probe开始不做更改只做标记
const QList<Cell*>& ActiveNum,//仅用于复位
ProbeResult& Result//用于存储
)

{
    qDebug()<<"Probe flag "<<(int)(*it)->nx<<' '<<(int)(*it)->ny;
    QStack<Cell*> rec;
    auto nowit=it;
    auto NowActiveNum=ActiveNum;
    bool r=false;//返回值记录
    (*nowit)->Henso(CellStatus::flag);

    RevocableAutoFlag(NowActiveNum,rec);//此时NowActiveNum不可信
    if(!ProbeCheck(ActiveNum))//使用可信的ActiveNum进行检测
    {
        qDebug()<<"Paradox flag "<<(int)(*nowit)->nx<<' '<<(int)(*it)->ny;
        qDebug()<<"clickable "<<(int)(*nowit)->nx<<' '<<(int)(*it)->ny;
        (*nowit)->Henso(CellStatus::clickable);
        Recover(rec);
        return r;
    }
    while(nowit != ActiveIni.end())
    {
        if((*nowit)->status == CellStatus::ini ) 
        {
            if(Probe(nowit,ActiveIni,NowActiveNum,Result)) goto F_Break;
            rec.push(*nowit);//一次试探失败时，Probe做的只有一件事可以在外部看到，就是标出他现在可以确定的状态
            RevocableAutoFlag(NowActiveNum,rec);//根据此状态继续标
        }
        nowit++;
    }
    Result.Add();
    r=true;
    F_Break:
    qDebug()<<"Recover Flag Assume!";
    

    qDebug()<<"Probe clickable "<<(int)(*it)->nx<<' '<<(int)(*it)->ny;
    Recover(rec);
    nowit=it;
    NowActiveNum=ActiveNum;
    (*nowit)->Henso(CellStatus::clickable);

    RevocableAutoFlag(NowActiveNum,rec);

    if(!ProbeCheck(ActiveNum))
    {
        qDebug()<<"Paradox clickable ";
        if(r) goto C_Break ;
        qDebug()<<"flag "<<(int)(*it)->nx<<' '<<(int)(*it)->ny;
        (*nowit)->Henso(CellStatus::flag);
        Recover(rec);
        return r;
    }
    while(nowit != ActiveIni.end())
    {
        if((*nowit)->status == CellStatus::ini ) 
        {
            if(Probe(nowit,ActiveIni,NowActiveNum,Result)) goto C_Break;
            rec.push(*nowit);//一次试探失败时，Probe做的只有一件事可以在外部看到，就是标出他现在可以确定的状态
            RevocableAutoFlag(NowActiveNum,rec);//根据此状态继续标
        }
        nowit++;
    }
    Result.Add();
    
    C_Break:
    Recover(rec);
    qDebug()<<"Recover clickable Assume!";

    (*it)->Henso(CellStatus::ini);
    return true;
}
void GraphicsScene::AutoFlag()
{
    RedoTip();
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
                    //qDebug()<<"clickable around "<<(int)x<<(int)y;
                    for(auto& c:r)
                        if(c->status==CellStatus::ini) c->Henso(CellStatus::clickable);
                }
                else if (activity ==cells[x][y]->MineNum - flags)//未翻开格子数 == 周围雷数，则全部标雷雷
                {
                    //qDebug()<<"flag around "<<(int)x<<(int)y;
                    for(auto& c:r)
                        if(c->status==CellStatus::ini) c->Henso(CellStatus::flag);
                }
                else ActiveNum.push_back(cells[x][y]);//活跃但无法确定周遭状态
            }
    AutoFlag(ActiveNum);
    // if(ActiveNum.size()==0)//此时
    // {
    //     if(!WinCheck())
    //     {
            
    //     }
    //     return;
    // }
    //简单标旗结束
    QList<Cell*> ActiveIni,InActiveIni;//活跃的未翻开格，指周围有数字的未翻开格
    int InActiveIniNum=0;//非活跃未翻开格数
    for(auto x=1;x<=row;x++)
        for(auto y=1;y<=column;y++)
            if(cells[x][y]->status == CellStatus::ini)
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
                else InActiveIni.push_back(cells[x][y]);
            }
    //std::cout<<InActiveIniNum<<std::endl;
    if( ActiveIni.size()==0 )
    {
        if(!WinCheck())
        {
            float InActiveProb=(float)LeftMineNum/InActiveIni.size();
            for(auto& i:InActiveIni)
            {
                i->setAcceptHoverEvents(true);
                RedoTipList.push(i);
                i->setToolTip("地雷概率:" +  QString::number(InActiveProb*100,10,2) + '%');
            }
        }
        return;
    }
    ProbeResult Result(ActiveIni);
    Probe(ActiveIni,ActiveNum,Result);
    Result.RmNecessity(InActiveIni);
    using namespace std;
    if( ActiveIni.size()==0 )
    {
        if(!WinCheck())
        {
            float InActiveProb=(float)LeftMineNum/InActiveIni.size();
            for(auto& i:InActiveIni)
            {
                i->setAcceptHoverEvents(true);
                RedoTipList.push(i);
                i->setToolTip("地雷概率:" +  QString::number(InActiveProb*100,10,2) + '%');
            }
        }
        return;
    }
    vector<int> flags(Result.Res.back().size(),0);
    cout<<endl;
    for(auto& i:ActiveIni) cout<<(int)i->nx<<','<<(int)i->ny<<' ';
    for(int j=0;j<Result.Res.back().size();j++)
    {
        cout<<endl;
        for(auto& i:Result.Res) 
        {
            if(i[j]) flags[j]++;
            cout<<((i[j])?"f ":"c ");
        }
        //cout<<endl;
    }
    cout<<endl;
    float InActiveProb;
    QVector<float> Pbs=Result.Cal(InActiveProb,InActiveIni.size());
    cout<<"InActiveProb:"<<InActiveProb<<endl;
    for(auto& i:Pbs) cout<<i<<' ';
    auto j=Pbs.begin();
    for(auto& i:ActiveIni)
    {
        i->setAcceptHoverEvents(true);
        RedoTipList.push(i);
        i->setToolTip("地雷概率:" +  QString::number((*j)*100,10,2) + '%');
        j++;
    }
    for(auto& i:InActiveIni)
    {
        i->setAcceptHoverEvents(true);
        RedoTipList.push(i);
        i->setToolTip("地雷概率:" +  QString::number(InActiveProb*100,10,2) + '%');
    }
}

//只在非试探状态下使用
void GraphicsScene::AutoFlag(QList<Cell*>& ActiveNum)
{
    bool IfAct=true;//在队列的一轮遍历时是否有处理
    while(IfAct)
    {
        IfAct=false;
        for(auto i=ActiveNum.begin();i !=ActiveNum.end();)
        {
            // qDebug()<<"acess "<<(int)(*i)->nx<<(int)(*i)->ny;
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
                IfAct=true;
                // qDebug()<<"release "<<(int)(*i)->nx<<(int)(*i)->ny;
                i=ActiveNum.erase(i);
            }
            else if ((*i)->MineNum == flags)//周围可标无雷
            {
                IfAct=true;
                // qDebug()<<"clickable around "<<(int)(*i)->nx<<(int)(*i)->ny;
                
                for(auto& c:r)
                    if(c->status==CellStatus::ini) c->Henso(CellStatus::clickable);

                i=ActiveNum.erase(i);
            }
            else if (activity ==(*i)->MineNum - flags )//周围可标雷
            {
                IfAct=true;
                // qDebug()<<"flag around "<<(int)(*i)->nx<<(int)(*i)->ny;
                for(auto& c:r)
                    if(c->status==CellStatus::ini) c->Henso(CellStatus::flag);
                i=ActiveNum.erase(i);
            }
            else i++;
        }
    }
}
void GraphicsScene::RevocableAutoFlag(QList<Cell*>& ActiveNum,QStack<Cell*>& ss)
{
    bool IfAct=true;//在队列的一轮遍历时是否有处理
    while(IfAct)
    {
        IfAct=false;
        for(auto i=ActiveNum.begin();i !=ActiveNum.end();)
        {
            //qDebug()<<"acess "<<(int)(*i)->nx<<(int)(*i)->ny;
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
                IfAct=true;
                //qDebug()<<"release "<<(int)(*i)->nx<<(int)(*i)->ny;
                i=ActiveNum.erase(i);
            }
            else if ((*i)->MineNum == flags)//周围可标无雷
            {
                IfAct=true;
                //qDebug()<<"clickable around "<<(int)(*i)->nx<<(int)(*i)->ny;
                
                for(auto& c:r)
                    if(c->status==CellStatus::ini) 
                    {
                        c->Henso(CellStatus::clickable);
                        ss.push_back(c);
                    }
                i=ActiveNum.erase(i);
            }
            else if (activity ==(*i)->MineNum - flags )//周围可标雷
            {
                IfAct=true;
                //qDebug()<<"flag around "<<(int)(*i)->nx<<(int)(*i)->ny;
                for(auto& c:r)
                    if(c->status==CellStatus::ini) 
                    {
                        c->Henso(CellStatus::flag);
                        ss.push_back(c);
                    }
                i=ActiveNum.erase(i);
            }
            else i++;
        }
    }
}
void GraphicsScene::RedoTip()
{
    while(!RedoTipList.empty())
    {
        RedoTipList.top()->setAcceptHoverEvents(false);
        RedoTipList.pop();
    }
}
bool GraphicsScene::WinCheck()
{
    if(LeftMineNum==0 && FlagCheck())
    {
        QMessageBox::information(NULL, tr("提示"), tr("游戏胜利"));
        return true;
    }
    return false;
}
GraphicsScene::~GraphicsScene()
{
}


ProbeResult::ProbeResult(QList<Cell*>& TheAcitveIni)
:
AcitveIni(TheAcitveIni),
Res(TheAcitveIni.size())
{
}
void ProbeResult::Add()
{
    auto i=AcitveIni.begin();
    auto j=Res.begin();
    while(i!=AcitveIni.end())
    {
        j->push_back((*i)->status == CellStatus::flag);
        i++;j++;
    }
}
void ProbeResult::RmNecessity(QList<Cell*> InActiveIni)
{
    auto i=AcitveIni.begin();
    auto j=Res.begin();
    while(i!=AcitveIni.end())
    {
        bool flag=true;
        bool clickable=true;
        for(auto& x:*j)
            if(x) clickable=false;
            else flag=false;
        if(flag)
        {
            (*i)->Henso(CellStatus::flag);
            InActiveIni.push_back(*i);
            i=AcitveIni.erase(i);
            j=Res.erase(j);
        }
        else if(clickable)
        {
            (*i)->Henso(CellStatus::clickable);
            InActiveIni.push_back(*i);
            i=AcitveIni.erase(i);
            j=Res.erase(j);
        }
        else 
        {
            i++;
            j++;
        }
    }
}
QVector<float> ProbeResult::Cal(float& InAcitveProb,int IncativeSize)
{
    InAcitveProb =0;
    QVector<float> r(Res.size(),0);
    QMap<int,int> HMflags;
    QMap<int,float> Prob;//key为解的雷数，value为该雷数出现的范围
    QVector<int> flags(Res.back().size(),0);
    for(int j=0;j<Res.back().size();j++)
    {
        for(auto& i:Res) 
            if(i[j]) flags[j]++;
        if(HMflags.find(flags[j]) == HMflags.end()) HMflags[flags[j]]=1;
        else HMflags[flags[j]]+=1;
    }
    //HMflags[2]=2,HMflags[1]=1
    //LeftMineNum=4
    float all=0;
    for(auto i=HMflags.begin();i !=HMflags.end();i++)
    {
        Prob[i.key()]=(1.0/Fac(GraphicsScene::LeftMineNum-i.key()))*i.value();
        all +=Prob[i.key()];
    }
    for(auto i=Prob.begin();i !=Prob.end();i++)
    {
        Prob[i.key()] /= all;//计算活跃格出现i.key()个雷的概率
        InAcitveProb += ((GraphicsScene::LeftMineNum-i.key())/(float)IncativeSize)*i.value();
    }
    for(int j=0;j<Res.back().size();j++)
    {
        auto rr=r.begin();
        for(auto& i:Res) 
        {
            if(i[j] == 1) *rr += (1.0/ HMflags[flags[j]])*Prob[flags[j]];
            rr++;
        }
    }
    return r;
}
/*
1表示有旗，0表示无
下列为所有可能解
10010
01001
00100

C(n,k)表示n个里选k个
2*6+3*9=12+27=39
39-5=34
34 (1,2) 4
All=C(34,2)*2+C(34,3)*1 //全部可能情况
2雷概率:=C(34,2)*2/All
1雷概率:=C(34,3)/All
大数直接约分
2雷概率=(1/2*2)/(1/2)*2+1/6=6/7
1雷概率=1/7
1,2,4,5号:=0.5*2雷概率=3/7
3号:=1雷概率=1/7

*/