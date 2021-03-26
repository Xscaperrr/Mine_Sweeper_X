#include "mainwindow.h"
#include "cell.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      scene(new QGraphicsScene(this)),
      view(new GraphicsView(scene,this)),
      menubar(new QMenuBar(this))

{
    resize(1600,900);
    setCentralWidget(view);
    setMenuBar(menubar);
    menus.push_back(new QMenu("设置"));
    actions.push_back(new QAction("难度",this));
    for(int i=0;i<menus.size();i++)
    {
        menubar->addMenu(menus[i]);
        menus[i]->addAction(actions[i]);
    }
    Cell *a;
   
    //scene->addItem(a);
    scene->setSceneRect(0,0,1600,900);
    for(int i=0;i<32;i++)
        for(int j=0;j<18;j++)
        {
            a=new Cell(50*i,50*j);
            scene->addItem(a);
        }
    
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


