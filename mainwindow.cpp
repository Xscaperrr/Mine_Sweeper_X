#include "mainwindow.h"
#include "cell.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      scene(new GraphicsScene(this)),
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

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QMainWindow::mousePressEvent(event);
    // std::cout<<"ojbk!"<<std::endl;

}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    QMainWindow::mouseReleaseEvent(event);
}

MainWindow::~MainWindow()
{
}

GraphicsView::GraphicsView(QGraphicsScene *scene,QWidget *parent)
{
    setScene(scene);setParent(parent);
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
