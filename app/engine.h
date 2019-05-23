#ifndef ENGINE_H
#define ENGINE_H

#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QtGui>
#include <QVector>
#include <QTimer>
#include <QTime>
#include "mathfuncs.h"
#include "enemy.h"
#include "hero.h"
#include "bullet.h"
#include "vocabulary.h"

namespace Ui {
class Engine;
}

class Engine : public QWidget
{
    Q_OBJECT

public:
    explicit Engine(QWidget *parent = nullptr);
    ~Engine();

    void start();

private:
    Ui::Engine *ui;
    QGraphicsScene *scene;
    Vocabulary     *file;
    QVector<Enemy *> enemies;
    Hero   *hero;
    QTimer *timer;
    QTimer *heroTimer;
    QTimer *bulletsTimer;
    QTime  *time;
    size_t writtenLetters;
    size_t successLetters;
    bool   mode;
    bool   started = false;

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void checkEnemies();
    void moveEnemies();
    void heroRotate();
    void moveBullets();

signals:
    void gameOver(qreal speed, qreal timeSec, qreal mistakes);

};

#endif // ENGINE_H
