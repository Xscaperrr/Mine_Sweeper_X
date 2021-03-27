#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
// #include <QGraphicsSceneMouseEvent>  
#include "cell.h"

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GraphicsScene(QObject *parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent  *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent  *event);
    ~GraphicsScene();

    static QPixmap *blank;
    static QPixmap *flag;
    static QPixmap *exp ;
    static QPixmap *ini ;
    static QPixmap *question;
    static QPixmap *num1;
    static QPixmap *num2;
    static QPixmap *num3;
    static QPixmap *num4;
    static QPixmap *num5;
    static QPixmap *num6;
    static QPixmap *num7;
    static QPixmap *num8;
    static QPixmap *num9;
};
#endif // GRAPHICSSCENE_H