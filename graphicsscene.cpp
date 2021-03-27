#include "graphicsscene.h"

QPixmap * GraphicsScene::blank=nullptr;//据考证，QPixmap类设定成全局变量有bug,所以采用指针绕路
QPixmap * GraphicsScene::flag=nullptr;
QPixmap * GraphicsScene::exp=nullptr;
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

GraphicsScene::GraphicsScene(QObject *parent) : QGraphicsScene(parent)
{
    blank=new QPixmap("://images/blank.png");  
    flag=new QPixmap("://images/flag.png");
    ini=new QPixmap("://images/initial.png");
    question=new QPixmap("://images/question.png");

    Cell *a;
    setSceneRect(0,0,1600,900);
    for(int i=0;i<32;i++)
        for(int j=0;j<25;j++)
        {
            a=new Cell(50*i,50*j);
            addItem(a);
        }
}
void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent  *event)
{
    //std::cout<<"ok2!"<<std::endl;
    QGraphicsScene::mousePressEvent(event);
}
void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent  *event)
{
    QGraphicsScene::mouseReleaseEvent(event);
}
GraphicsScene::~GraphicsScene()
{
}