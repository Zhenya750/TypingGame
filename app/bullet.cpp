#include "bullet.h"

Bullet::Bullet()
{
    x = 0;
    y = 0;
    m = 1;
    n = 1;
    active = FREE;
    enemy  = nullptr;
}

QRectF Bullet::boundingRect() const
{
    return QRectF(0, 0, 8, 8);
}

void Bullet::moveBullet(int x, int y)
{
    this->x = x;
    this->y = y;
}

int Bullet::getActive()
{
    return active;
}

void Bullet::setActive(int active)
{
    this->active = active;
}

void Bullet::setTarget(Enemy *enemy)
{
    if(enemy != nullptr){
        m = enemy->x >= 0 ? 1 : -1;
        n = enemy->y >= 0 ? 1 : -1;
    }

    this->enemy = enemy;
}

qreal Bullet::getTarget()
{
    return enemy->k;
}

Enemy *Bullet::getEnemy()
{
    return enemy;
}

int Bullet::getSignOX()
{
    return m;
}

int Bullet::getSignOY()
{
    return n;
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPainterPath path;
    QRectF circle = boundingRect();
    QBrush brush(QColor(38, 231, 235));
    circle.moveTo(x - 4, y - 4);

    painter->setPen(Qt::NoPen);
    painter->setOpacity(0.7);
    path.addEllipse(circle);
    painter->drawPath(path);
    painter->fillPath(path, brush);
}
