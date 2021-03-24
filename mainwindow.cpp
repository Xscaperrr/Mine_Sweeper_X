#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      scene(new QGraphicsScene(this)),
      view(new GraphicsView(scene,this)),
      menubar(new QMenuBar(this))

{
    resize(1600,900);
    setCentralWidget(view);
    setMenuBar(menubar);
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


