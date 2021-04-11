#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QMessageBox>
// #include <QGraphicsSceneMouseEvent>  
#include <vector>
#include <random>
#include <ctime>
#include <QDebug>
#include <QStack>
#include "cell.h"

class ResNode//结果节点
{
public:
    int x,y;//下标
    bool flag;//是否有旗

    ResNode(int xx,int yy,int flagg);

    //重载==用于队列的查找及删除
    bool operator==(const ResNode& another)const;
};

class ProbeResult
{
public:
    QVector<QList<ResNode>> Res;
    void Add(QList<Cell*>& l);
    void Del(Cell*& c);
    QVector<int> RmNecess();
};
class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GraphicsScene(QObject *parent = nullptr);
    void update(const QRectF &rect = QRectF());
    void mousePressEvent(QGraphicsSceneMouseEvent  *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent  *event);
    void MineBlockSet(int x=row,int y=column);
    void AutoFlag();
    void AutoFlag(QList<Cell*>& ActiveNum);
    void RevocableAutoFlag(QList<Cell*> ActiveNum,QStack<Cell*>& ss);
    static bool FlagCheck();
    bool ProbeCheck(QList<Cell*>& AllNum);//试探后的矛盾性检测
    void Recover(QStack<Cell*>& ss);
    bool Probe(QList<Cell *>::iterator& it,QList<Cell*>& ActiveIni,QList<Cell*>& ActiveNum,QList<Cell*>& AllNum,ProbeResult& Result);//递归回溯试探
    void FlagCheckEvent();
    void GameRestart();
    void CalProbability();
    static QVector<Cell*> RoundCell(Cell* c);
    static void BlankProcess(int x,int y);
    ~GraphicsScene();

    int TotalMineNum;
    static char row,column;
    static int LeftMineNum;
    static std::vector<std::vector<Cell*>> cells;
    //std::vector<Cell*> cell_1d;
    static QPixmap *blank;
    static QPixmap *flag;
    static QPixmap *bomb ;
    static QPixmap *ini ;
    static QPixmap *question;
    static QPixmap *clickable;
    static QPixmap *num1;
    static QPixmap *num2;
    static QPixmap *num3;
    static QPixmap *num4;
    static QPixmap *num5;
    static QPixmap *num6;
    static QPixmap *num7;
    static QPixmap *num8;
    static QPixmap *num9;
};



#endif // GRAPHICSSCENE_H