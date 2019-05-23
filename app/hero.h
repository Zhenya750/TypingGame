#ifndef HERO_H
#define HERO_H

#include <QGraphicsItem>
#include <QPainter>
#include <QVector>
#include "bullet.h"
#include "enemy.h"

class Hero : public QGraphicsItem
{
public:
    Hero();

    QVector<Bullet *> bullets;

private:
    Enemy *enemy;
    qreal angle;
    qreal targetAngle;
    bool  rotateActive;

public:
    void setEnemy(Enemy *enemy);
    void rotateHero(qreal angle);
    void setRotateActive(bool rotateActive);
    void setTargetAngle(qreal angle);
    void recharge(Bullet *bullet);
    void shot(int activity = FREE);
    bool getRotateActive();
    bool isHeadShot(Bullet *bullet);
    qreal getTargetAngle();
    qreal getAngle();
    Enemy * getEnemy();

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // HERO_H
