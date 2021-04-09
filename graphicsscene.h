#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QMessageBox>
// #include <QGraphicsSceneMouseEvent>  
#include <vector>
#include <random>
#include <ctime>
#include <QDebug>

#include "cell.h"

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GraphicsScene(QObject *parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent  *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent  *event);
    void MineBlockSet(int x=row,int y=column);
    void AutoFlag();
    bool FlagCheck();
    void FlagCheckEvent();
    void GameRestart();
    static QVector<Cell*> RoundCell(Cell* c);
    static void BlankProcess(int x,int y);
    ~GraphicsScene();

    int TotalMineNum;
    static char row,column;
    static int LeftMineNum;
    static std::vector<std::vector<Cell*>> cells;
    //std::vector<Cell*> cell_1d;
    //static QVector<QPair<int,int>> RoundStep;
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