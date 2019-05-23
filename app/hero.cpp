#include "hero.h"
#include <QDebug>

Hero::Hero()
{
    angle        = 0;
    enemy        = nullptr;
    rotateActive = false;

    for(int i = 0; i < 100; i++){
        bullets.append(new Bullet());
    }
}


void Hero::setEnemy(Enemy *enemy)
{
    this->enemy = enemy;
}

Enemy * Hero::getEnemy()
{
    return enemy;
}

void Hero::rotateHero(qreal angle)
{
    this->angle = angle;
}

bool Hero::getRotateActive()
{
    return rotateActive;
}

void Hero::setRotateActive(bool rotateActive)
{
    this->rotateActive = rotateActive;
}

qreal Hero::getTargetAngle()
{
    return targetAngle;
}

void Hero::setTargetAngle(qreal angle)
{
    targetAngle = angle;
}

qreal Hero::getAngle()
{
    return angle;
}

QRectF Hero::boundingRect() const
{
    return QRectF(-13, -13, 26, 26);
}

void Hero::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QRectF circle = boundingRect();
    QRectF gun(-5, 0, 10, -30);
    QPainterPath path;

    circle.moveTo(-13, -13);
    gun.moveTo(-5, 0);

    path.addEllipse(circle);

    while(angle >= 180 ) angle -= 360;
    while(angle <= -180) angle += 360;

    painter->rotate(angle);
    painter->setPen(Qt::NoPen);
    painter->fillPath(path, Qt::green);
    painter->fillRect(gun, Qt::black);
    painter->drawPath(path);
    painter->drawRect(gun);
}

void Hero::recharge(Bullet *bullet)
{
    bullet->setActive(FREE);
    bullet->moveBullet(0, 0);
    bullet->setTarget(nullptr);
}

bool Hero::isHeadShot(Bullet *bullet)
{
    if((bullet->x - bullet->getEnemy()->x) * (bullet->x - bullet->getEnemy()->x) +
       (bullet->y - bullet->getEnemy()->y) * (bullet->y - bullet->getEnemy()->y) <
                    bullet->getEnemy()->getRadius() * bullet->getEnemy()->getRadius()){

        bullet->getEnemy()->addShot();
        return true;
    }

    return false;
}

void Hero::shot(int activity)
{
    if(activity == READY){

        for(Bullet *bullet : bullets){
            if(bullet->getActive() == READY)
                bullet->setActive(SHOT);
        }
        return;
    }

    for(Bullet *bullet : bullets){

        if(bullet->getActive() == FREE){
            bullet->setTarget(enemy);
            bullet->setActive(rotateActive ? READY : SHOT);
            return;;
        }

    }
}
