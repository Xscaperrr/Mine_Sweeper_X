#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>  
#include <QMenuBar>
#include <QAction>
#include <QGraphicsItem>
#include <iostream>

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
    QGraphicsScene *scene;
    GraphicsView *view;
    QMenuBar *menubar;
    std::vector<QMenu*> menus;
    std::vector<QAction*> actions;

    MainWindow(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    ~MainWindow();
};

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GraphicsScene(QObject *parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent  *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent  *event);
    ~GraphicsScene();
};

#endif // MAINWINDOW_H
