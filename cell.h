#ifndef CELL_H
#define CELL_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>  
// #include <iostream>

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
    // static QPixmap *blank;
    // static QPixmap flag;
    // static QPixmap exp ;
    // static QPixmap num1;
    // static QPixmap num2;
    // static QPixmap num3;
    // static QPixmap num4;
    // static QPixmap num5;
    // static QPixmap num6;
    // static QPixmap num7;
    // static QPixmap num8;
    // static QPixmap num9;


    CellStatus status;
    char MineNum;//-2未处理,-1雷，0空，1-8周边雷数
    
    Cell(qreal x,qreal y);

    //改变status及外表
    void Henso(CellStatus NewStatus=CellStatus::kara);
   
    //鼠标点击
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    //鼠标释放
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    ~Cell();
};

#endif // CELL_H