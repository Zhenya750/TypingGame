#include "startmenu.h"
#include "ui_startmenu.h"

StartMenu::StartMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartMenu)
{
    ui->setupUi(this);

    game  = new Engine(this);
    saver = new Saver(this);
    table = new InfoTable(this);
    ui->stackedWidget->insertWidget(1, game);
    ui->stackedWidget->insertWidget(2, saver);
    ui->stackedWidget->insertWidget(3, table);

    table->loadInfo();

    connect(ui->exitButton,  SIGNAL(clicked()),                     this, SLOT(close()));
    connect(ui->startButton, SIGNAL(clicked()),                     this, SLOT(startGame()));
    connect(ui->statButton,  SIGNAL(clicked()),                     this, SLOT(goToStat()));
    connect(saver,           SIGNAL(goToMenu()),                    this, SLOT(getHome()));
    connect(table,           SIGNAL(goToMenu()),                    this, SLOT(getHome()));
    connect(game,            SIGNAL(gameOver(qreal, qreal, qreal)), this, SLOT(showGameOver(qreal, qreal, qreal)));
    connect(saver,           SIGNAL(saveResult(QString, QString, QString, QString, QString)),
                               this, SLOT(save(QString, QString, QString, QString, QString)));
}

StartMenu::~StartMenu()
{
    delete ui;
}

void StartMenu::closeEvent(QCloseEvent *event)
{
    table->saveInfo();
    event->accept();
}

void StartMenu::startGame()
{
    ui->stackedWidget->setCurrentIndex(1);
    game->start();
}

void StartMenu::showGameOver(qreal speed, qreal timeSec, qreal mistakes)
{
    saver->setInfo(speed, timeSec, mistakes);
    ui->stackedWidget->setCurrentIndex(2);
}

void StartMenu::getHome()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void StartMenu::goToStat()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void StartMenu::save(QString date, QString name, QString speed, QString time, QString mistakes)
{
    table->setRow(date, name, speed, time, mistakes);
}
