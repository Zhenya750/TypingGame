#include "engine.h"
#include "ui_engine.h"

#define ENEMYAMOUNT 6
#define HERO_UPDATE 4
#define BLLT_UPDATE 4
#define ENMY_UPDATE 35

Engine::Engine(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Engine)
{
    srand(static_cast<unsigned int>(std::time(nullptr)));

    mode            = false;
    started         = false;
    writtenLetters  = 0;    //amounf of all written letters
    successLetters  = 0;    //amount of succeessfully written letters

    scene = new QGraphicsScene(this);
    scene->setSceneRect(-640, -360, 1280, 720);

    file  = new Vocabulary();
    file->load("sources/enwords");

    hero  = new Hero();

    for(Bullet *bullet : hero->bullets){
        scene->addItem(bullet);
    }
    scene->addItem(hero);

    for(int i = 0; i < ENEMYAMOUNT % 11; i++){

        QString str = file->setNewStr();
        enemies.append(new Enemy(str));
        scene->addItem(enemies.at(i));
    }

    ui->setupUi(this);
    ui->lineEdit->setVisible(false);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(checkEnemies()));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(moveEnemies()));
    timer->start(ENMY_UPDATE);

    heroTimer = new QTimer(this);
    connect(heroTimer, SIGNAL(timeout()), this, SLOT(heroRotate()));
    heroTimer->start(HERO_UPDATE);

    bulletsTimer = new QTimer(this);
    connect(bulletsTimer, SIGNAL(timeout()), this, SLOT(moveBullets()));
    bulletsTimer->start(BLLT_UPDATE);
}

Engine::~Engine()
{
    delete ui;
}

void Engine::start()
{
    writtenLetters = 0;
    successLetters = 0;

    if(mode){

        hero->setEnemy(nullptr);
        hero->rotateHero(0);
        hero->setTargetAngle(0);
        hero->setRotateActive(false);

        for(Bullet *bullet : hero->bullets){
            hero->recharge(bullet);
        }

        file->clearAlpha();

        for(Enemy *enemy : enemies){
            QString str = file->setNewStr();
            enemy->heal(str);
        }
    }

    started = true;
    time = new QTime;
    time->start();
}

void Engine::keyPressEvent(QKeyEvent *event)
{
    if(started){
        ui->lineEdit->setText(event->text());
        writtenLetters++;
        scene->update();
    }
}

void Engine::keyReleaseEvent(QKeyEvent *event)
{
    if(started){
        Q_UNUSED(event);
        ui->lineEdit->clear();
    }
}

void Engine::checkEnemies()
{
    if(started){
        QString letter = ui->lineEdit->text();

        if(hero->getEnemy() != nullptr &&
           hero->getEnemy()->getActive() == TARGET){

            if(hero->getEnemy()->doCmp(letter)){
                hero->shot();
                successLetters++;
            }
            return;
        }

        for(Enemy *enemy : enemies){

            if(hero->getRotateActive() == false &&
               enemy->getStr()[0] == letter[0]  &&
               enemy->getActive() == ALIVE      &&
               qAbs(enemy->x) < qAbs(this->width()  >> 1) &&
               qAbs(enemy->y) < qAbs(this->height() >> 1)){

                enemy->setActive(TARGET);
                enemy->doCmp(letter);

                qreal angle = qRadiansToDegrees(qAtan(enemy->k)) + enemy->signOX * 90;

                hero->setRotateActive(true);
                hero->setTargetAngle(angle);
                hero->setEnemy(enemy);

                successLetters++;
                return;
            }
        }
    }
}

void Engine::moveEnemies()
{
    if(started){

        for(Enemy *enemy : enemies){
            if(enemy->getActive() == KILLED){
                QString str = file->setNewStr(enemy->getStr()[0]);
                enemy->heal(str);
            }
        }

        for(Enemy *enemy : enemies){

            bool attacked = enemy->x * enemy->x + enemy->y * enemy->y <= 144;
            bool resisted = enemy->getLocked();

            if(attacked || resisted){
                enemy->moveEnemy(enemy->x, enemy->y);
                enemy->setLocked(enemy->getLocked() - 1);

                if(attacked){

                    qreal speed = (successLetters + 0.0) / ((time->elapsed() + 0.0) / 60000);

                    if(writtenLetters){
                        if(!successLetters) successLetters = 1;
                    }
                    else{
                        writtenLetters = successLetters = 1;
                    }

                    qreal mistakes = 100.0 - (successLetters * 100 + 0.0) / writtenLetters;
                    emit gameOver(speed, (time->elapsed() / 1000), mistakes);
                    started = false;
                    mode    = true;
                }
            }

            else{
                if(!enemy->x){
                    enemy->moveEnemy(0, enemy->y + (enemy->y > 0 ? -1 : 1));
                    continue;
                }

                if(!enemy->y){
                    enemy->moveEnemy(enemy->x + (enemy->x > 0 ? -1 : 1), 0);
                    continue;
                }

                if(qAbs(enemy->k) > 1){

                    enemy->moveEnemy(int((1 + 0.0) / enemy->k * enemy->y), enemy->y + (enemy->y > 0 ? -1 : 1));
                }
                else{

                    enemy->moveEnemy(enemy->x + (enemy->x > 0 ? -1 : 1), int(enemy->k * enemy->x));
                }
            }
        }

        scene->update();
    }
}

void Engine::heroRotate()
{
    if(started){
        if(hero->getRotateActive()){

            qreal target = hero->getTargetAngle();
            if(int(target) % 2 != 0) target += 1;
            qreal angle  = hero->getAngle();
            qreal delA   = target - angle;

            int n = 1;
            int m = 1;
            if(delA < 0) n = -1;
            if(delA * delA > 180 * 180) m = -1;

            if(int(hero->getAngle()) != int(target      ) &&
               int(hero->getAngle()) != int(target + 360) &&
               int(hero->getAngle()) != int(target - 360)){

                hero->rotateHero(hero->getAngle() + m * n * 2);
            }
            else{

                hero->setRotateActive(false);
                hero->shot();
                hero->shot(READY);
            }
            scene->update();
        }
    }
}

void Engine::moveBullets()
{
    if(started){
        for(Bullet *bullet : hero->bullets){

            if(bullet->getActive() == SHOT){

                if(bullet->getEnemy()->x == 0){

                    bullet->moveBullet(0, bullet->y + 2 * bullet->getSignOY());
                }
                else{

                    if(qAbs(bullet->getEnemy()->k) > 1){

                        bullet->moveBullet(int(bullet->y * (1 + 0.0) / bullet->getTarget()), bullet->y + 2 * bullet->getSignOY());
                    }
                    else{

                        bullet->moveBullet(bullet->x + 2 * bullet->getSignOX(), int(bullet->x * bullet->getTarget()));
                    }
                }

                if(hero->isHeadShot(bullet)){
                    hero->recharge(bullet);
                }

                scene->update();
            }
        }
    }
}
