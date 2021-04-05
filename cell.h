#ifndef CELL_H
#define CELL_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>  
#include <iostream>

enum class CellStatus:char
{
    ini,//未翻开
    num,//数字状态
    bomb,//炸弹
    flag,//旗
    blank,//空格
    question,//问号
    kara  //空，非状态，表示不传参数
};

class Cell : public QGraphicsPixmapItem 
{   
public:
    static char row,column,nr,nc,pix;//目标行列数，现在的行列数,像素

    CellStatus status;
    char MineNum;//-2未处理,-1雷，0空，1-8周边雷数
    
    Cell(char x=-1);
    Cell(qreal x,qreal y,char k);

    void SwapMine(Cell& x);
    //改变status及外表
    void Henso(CellStatus NewStatus=CellStatus::kara);
   
    //鼠标点击
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    //鼠标释放
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    char IfMine();
    ~Cell();
};

#endif // CELL_H