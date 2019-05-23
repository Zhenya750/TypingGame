#include "saver.h"
#include "ui_saver.h"

Saver::Saver(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Saver)
{
    speed    = "";
    mistakes = "";
    time     = "";
    nickname = "Unknown";
    date     = "";
    ui->setupUi(this);

    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveInfo()));
    connect(ui->menuButton, SIGNAL(clicked()), this, SLOT(backtoMenu()));
}

Saver::~Saver()
{
    delete ui;
}

void Saver::setInfo(qreal speed, qreal timeSec, qreal mistakes)
{
    QString time;
    if(timeSec > 60){
        time = QString::number(timeSec / 60, 'f', 1) + " min";
    }
    else{
        time = QString::number(timeSec) + " sec";
    }

    this->date     = QDateTime::currentDateTime().toString("dd.MM.yy hh:mm");
    this->speed    = QString::number(int(speed));
    this->time     = time;
    this->mistakes = QString::number(mistakes, 'f', 1) + "%";

    ui->lineTime->setText(this->time);
    ui->lineSpeed->setText(this->speed + " signs/min");
    ui->lineMistakes->setText(this->mistakes);
    ui->saveButton->setEnabled(true);
}

void Saver::saveInfo()
{
    nickname = ui->lineNickname->text();
    if(!QRegExp(".*\\S+.*").exactMatch(nickname)){
        nickname = "Unknown";
    }

    ui->saveButton->setEnabled(false);
    emit saveResult(date, nickname, speed, time, mistakes);
}

void Saver::backtoMenu()
{
    emit goToMenu();
}
