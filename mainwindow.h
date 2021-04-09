#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include <QMainWindow>
#include <QGraphicsView>
// #include <QGraphicsScene>
#include <QGraphicsItem>
// #include <QGraphicsSceneMouseEvent>  
#include <QStatusBar>
#include <QLabel>
#include <QMenuBar>
#include <QAction>
#include <QGraphicsItem>
#include <iostream>
#include "graphicsscene.h"

class GraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    GraphicsView(QGraphicsScene *scene=nullptr,QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    ~GraphicsView();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    GraphicsScene *scene;
    GraphicsView *view;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    std::vector<QMenu*> menus;
    std::vector<std::vector<QAction*>> actions;
    static QLabel *Diffculty,*TotalMines,*LeftMines;
    MainWindow(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    ~MainWindow();
};

#endif // MAINWINDOW_H
