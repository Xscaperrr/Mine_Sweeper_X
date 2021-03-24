#include "mainwindow.h"
#include "cell.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      scene(new QGraphicsScene(this)),
      view(new GraphicsView(scene,this)),
      menubar(new QMenuBar(this))

{
    resize(1200,900);
    setCentralWidget(view);
    setMenuBar(menubar);
    menus.push_back(new QMenu("设置"));
    actions.push_back(new QAction("难度",this));
    for(int i=0;i<menus.size();i++)
    {
        menubar->addMenu(menus[i]);
        menus[i]->addAction(actions[i]);
    }
    Cell *a=new Cell(500,500);
    QGraphicsLineItem *l=new QGraphicsLineItem(0,0,500,500);
    QGraphicsPixmapItem *p=new QGraphicsPixmapItem();
    QPixmap pi("C:/Users/Lee/Desktop/Cpp Work/Mines_Sweeper/Mine_Sweeper_X/images/blank.png");
    p->setPixmap(pi.scaled(150,150));
    //scene->addItem(l);
    scene->addItem(a);
    //scene->addItem(p);
}

MainWindow::~MainWindow()
{
}

GraphicsView::GraphicsView(QGraphicsScene *scene,QWidget *parent)
{
    setScene(scene);setParent(parent);
}
GraphicsView::~GraphicsView()
{    
}


