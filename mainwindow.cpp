#include "mainwindow.h"
#include "cell.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      scene(new GraphicsScene(this)),
      view(new GraphicsView(scene,this)),
      menubar(new QMenuBar(this))

{
    resize(455,480);
    setCentralWidget(view);
    setMenuBar(menubar);
    menus.push_back(new QMenu("设置",this));//0
    menus.push_back(new QMenu("作弊",this));//1

    //for(auto& i:menus) actions.push_back(*(new std::vector<QAction*>));
    //for(auto& i:menus) actions.push_back(std::vector<QAction*>(0));
    actions.resize(menus.size());
    
    actions[0].push_back(new QAction("难度",this));
    actions[1].push_back(new QAction("标旗正确校验",this));
    actions[1].push_back(new QAction("自动标旗",this));

    

    for(int i=0;i<menus.size();i++)
    {
        menubar->addMenu(menus[i]);
        for(auto& j:actions[i]) menus[i]->addAction(j);
    }

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QMainWindow::mousePressEvent(event);
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    QMainWindow::mouseReleaseEvent(event);
}

MainWindow::~MainWindow()
{
}

GraphicsView::GraphicsView(QGraphicsScene *scene,QWidget *parent): QGraphicsView(scene,parent)
{
    //QGraphicsView::setAlignment(Qt::AlignLeft | Qt::AlignTop);
}
void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
    //std::cout<<"ok1!"<<std::endl;
}
void GraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
}
GraphicsView::~GraphicsView()
{    
}
