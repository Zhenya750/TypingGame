#include "enemy.h"

Enemy::Enemy(QString str)
{
    heal(str);
}

QRectF Enemy::boundingRect() const
{
    return QRectF(0, 0, 20, 20);
}

QString Enemy::getStr()
{
    return str;
}

int Enemy::getRadius()
{
    return radius;
}

void Enemy::moveEnemy(int x, int y)
{
    this->x = x;
    this->y = y;
}

int Enemy::getActive()
{
    return active;
}

void Enemy::setActive(int active)
{
    this->active = active;
}

int Enemy::getLocked()
{
    return locked;
}

void Enemy::setLocked(int locked)
{
    this->locked = locked;
}

void Enemy::addShot()
{
    locked = 3;
    shots++;
}

void Enemy::heal(QString str)
{
    switch (getRand(0, 0, 0, 2))
    {
    case 0:{
        x = getRand(-600, -450, 450, 600);
        y = getRand(-500, -350, 350, 500);
        break;
    }
    case 1:{
        x = getRand(-400,    0,   0, 400);
        y = getRand(-500, -350, 350, 500);
        break;
    }
    case 2:{
        x = getRand(-600, -450, 450, 600);
        y = getRand(-300,    0,   0, 300);
        break;
    }
    }
    count     = 0;
    shots     = 0;
    locked    = 0;
    active    = ALIVE;
    radius    = 15;
    this->str = str;
    k         = (y + 0.0) / x;
    signOX    = x >= 0 ? 1 : -1;
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    if(shots == str.size()) active = KILLED;

    //text size
    int size = 13;

    painter->setRenderHint(QPainter::Antialiasing);
    QPainterPath path;
    QRectF rec(0, 0, str.size() * size, size << 1);
    //QRectF circle(0, 0, radius, radius);
    QRectF circle(0, 0, radius / 2 * qLn(str.size() * size), radius / 2 * qLn(str.size() * size));

    qreal mcx = x;                                                      //middle circle x
    qreal mcy = y;                                                      //middle circle y
    qreal mrx = signOX * (rec.width()  + size) * qCos(qAtan(k)) + mcx;  //middle rectangle x
    qreal mry = signOX * (rec.height() + size) * qSin(qAtan(k)) + mcy;  //middle rectangle y

    mrx -= rec.width()  / 2;
    mry -= rec.height() / 2;

    circle.moveTo(mcx - circle.width() / 2, mcy - circle.height() / 2);
    rec.moveTo(mrx, mry);

    /*//This part demonstrates how ellipse align works
    for(int i = 0; i < 361; i++){
        painter->setPen(Qt::white);
        painter->drawPoint(qCeil(signOX * (rec.width()  + size) * qCos(qDegreesToRadians(i + 0.0)) + mcx),
                           qCeil(signOX * (rec.height() + size) * qSin(qDegreesToRadians(i + 0.0)) + mcy));
    }
    */


    // part of an enemy
    painter->setOpacity(active == ALIVE ? 0.3 : 0.7);
    if(active > INJURY) path.addRoundedRect(rec, 10, 10);
    if(active > KILLED) path.addEllipse(circle);
    QBrush brush(QColor(10 + shots * 220 / str.size(), 10, 230 - shots * 220 / str.size()));
    painter->fillPath(path, brush);
    painter->drawPath(path);

    // text painter
    if(active > INJURY){
        QString str1(str.size(), ' ');
        QString str2 = str;
        for(int i = 0; i < count; i++){
            str1[i] = str[i];
            str2[i] = ' ';
        }

        painter->setOpacity(active == ALIVE ? 0.7 : 1);
        painter->setPen(QColor(10, 40, 40));
        painter->setFont(QFont("Consolas", size));
        painter->drawText(rec, Qt::AlignCenter, str1);
        painter->setPen(Qt::white);
        painter->drawText(rec, Qt::AlignCenter, str2);
    }

}

int Enemy::doCmp(QString &letter)
{
    if(count < str.size()){

        if(letter[0] == str.at(count)){
            count++;
            return 1;
        }
    }
    else{

        active = INJURY;
    }

    return 0;
}
