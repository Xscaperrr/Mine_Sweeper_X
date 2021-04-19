#include "mainwindow.h"
#include "cell.h"

QLabel* MainWindow::Diffculty=nullptr;
QLabel* MainWindow::TotalMines=nullptr;
QLabel* MainWindow::LeftMines=nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      scene(new GraphicsScene(this)),
      view(new GraphicsView(scene,this)),
      statusbar(new QStatusBar(this)),
      menubar(new QMenuBar(this))

{
    resize(455,515);
    setCentralWidget(view);
    setMenuBar(menubar);
    setStatusBar(statusbar);
    // QLabel * l=new QLabel("try",this);
    // statusBar()->addPermanentWidget(new QLabel("try",this));
    // statusBar()->addPermanentWidget(new QLabel("try2",this));
    // statusBar()->setStyleSheet(QString("QStatusBar::item{border: 0px}"));
    Diffculty=new QLabel("难度:简单",this);
    TotalMines=new QLabel("总雷数:10",this);
    LeftMines=new QLabel("剩余雷数:10",this);
    statusBar()->addWidget(Diffculty,1);
    statusBar()->addWidget(TotalMines,1);
    statusBar()->addWidget(LeftMines,1);
     
    menus.push_back(new QMenu("游戏",this));//0
    menus.push_back(new QMenu("作弊",this));//1
    menus.push_back(new QMenu("帮助",this));//2

    //for(auto& i:menus) actions.push_back(*(new std::vector<QAction*>));
    //for(auto& i:menus) actions.push_back(std::vector<QAction*>(0));
    actions.resize(menus.size());
    
    actions[0].push_back(new QAction("重启",this));//0 0
    actions[0].push_back(new QAction("难度",this));//0 1
    actions[1].push_back(new QAction("标旗正确校验",this));//1 0
    actions[1].push_back(new QAction("自动标旗并计算概率",this));//1 1

    connect(actions[0][0],&QAction::triggered,scene,&GraphicsScene::GameRestart);
    connect(actions[1][0],&QAction::triggered,scene,&GraphicsScene::FlagCheckEvent);
    connect(actions[1][1],&QAction::triggered,scene,QOverload<>::of(&GraphicsScene::AutoFlag));

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
    qDebug()<<"Program End";
    qDebug()<<"/****************************************************************/";
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
