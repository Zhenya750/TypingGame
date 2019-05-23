#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsItem>
#include <QPainter>
#include "enemy.h"

enum bulletActivity { FREE = -1, READY = 0, SHOT = 1 };

class Bullet : public QGraphicsItem
{
public:
    Bullet();

    int x;
    int y;

private:
    int active;
    int m;
    int n;
    Enemy *enemy;

public:
    void moveBullet(int x, int y);
    int getActive();
    void setActive(int active);
    void setTarget(Enemy *enemy);
    qreal getTarget();
    Enemy *getEnemy();
    int getSignOX();
    int getSignOY();

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // BULLET_H
