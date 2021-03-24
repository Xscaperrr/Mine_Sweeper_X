#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMenuBar>
#include <QAction>

class GraphicsView : public QGraphicsView
{
Q_OBJECT

public:
GraphicsView(QGraphicsScene *scene=nullptr,QWidget *parent = nullptr);
~GraphicsView();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QGraphicsScene *scene;
    GraphicsView *view;
    QMenuBar *menubar;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};



#endif // MAINWINDOW_H
