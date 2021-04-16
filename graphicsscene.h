#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QMessageBox>
// #include <QGraphicsSceneMouseEvent>  
#include <vector>
#include <list>//Qlist缺少int初始化的构造函数
#include <random>
#include <ctime>
#include <QDebug>
#include <QStack>
#include "cell.h"

class ProbeResult
{
public:
    //QVector<QList<ResNode>> Res;
    ProbeResult(QList<Cell*>& TheAcitveIni);
    void Add();
    //void Del(Cell*& c);
    QList<Cell*>& AcitveIni;//仅访问获取结果,在rm操作时删除确定值
    std::list<QVector<bool>> Res;//True为旗，False为可点击
    void RmNecessity(QList<Cell*> InActiveIni);
    QVector<float> Cal(float& InAcitveProb,int IncativeSize);//概率计算
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

    void RevocableAutoFlag(QList<Cell*>& ActiveNum,QStack<Cell*>& ss);
    bool ProbeCheck(const QList<Cell*>& AllNum);//试探后的矛盾性检测

    void Recover(QStack<Cell*>& ss);//状态恢复

    void Probe(QList<Cell*>& ActiveIni,QList<Cell*>& ActiveNum,ProbeResult& Result);//试探全过程
    bool Probe(const QList<Cell *>::iterator& it,const QList<Cell*>& ActiveIni,const QList<Cell*>& ActiveNum,ProbeResult& Result);//递归回溯试探

    void FlagCheckEvent();
    void GameRestart();
    //void CalProbability();
    
    static bool FlagCheck();
    static QVector<Cell*> RoundCell(Cell* c);
    static void RedoTip();
    static bool WinCheck();
    static QStack<Cell*> RedoTipList;
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