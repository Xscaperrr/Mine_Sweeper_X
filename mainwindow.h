#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMenuBar>
#include <QAction>
#include <QGraphicsItem>

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
    std::vector<QMenu*> menus;
    std::vector<QAction*> actions;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};



#endif // MAINWINDOW_H
