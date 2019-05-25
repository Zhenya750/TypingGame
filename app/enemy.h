#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsItem>
#include <QPainter>
#include "mathfuncs.h"

enum enemyActivity { TARGET = 1, ALIVE = 0, INJURY = -1, KILLED = -2 };

class Enemy : public QGraphicsItem
{
public:

    Enemy(QString str);

    int x;
    int y;
    qreal k;
    int singOX;

private:

    int locked;
    int count;
    int shots;
    int radius;
    int active;
    QString str;

public:
    QString getStr();
    void moveEnemy(int x, int y);
    void setActive(int active);
    void setLocked(int locked);
    void addShot();
    void heal(QString str);
    int getRadius();
    int getActive();
    int getLocked();
    int doCmp(QString &str);


private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // ENEMY_H
