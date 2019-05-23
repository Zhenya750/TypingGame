#ifndef STARTMENU_H
#define STARTMENU_H

#include <QWidget>
#include "engine.h"
#include "saver.h"
#include "infotable.h"

namespace Ui {
class StartMenu;
}

class StartMenu : public QWidget
{
    Q_OBJECT

public:
    explicit StartMenu(QWidget *parent = nullptr);
    ~StartMenu();

private:
    Ui::StartMenu *ui;
    Engine *game;
    Saver *saver;
    InfoTable *table;

    void closeEvent(QCloseEvent *event);

private slots:
    void startGame();
    void showGameOver(qreal speed, qreal timeSec, qreal mistakes);
    void getHome();
    void goToStat();
    void save(QString date, QString name, QString speed, QString time, QString mistakes);
};

#endif // STARTMENU_H
