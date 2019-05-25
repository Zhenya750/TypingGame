#include "infotable.h"
#include "ui_infotable.h"

#define FILEPATH "progress.info"

InfoTable::InfoTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoTable)
{
    ui->setupUi(this);

    maxROWS = 16;
    maxCOLS = 5;

    connect(ui->menuButton,  SIGNAL(clicked()), this, SLOT(backToMenu()));
    connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clearInfo()));
}

InfoTable::~InfoTable()
{
    delete ui;
}

void InfoTable::setRow(QString date, QString name, QString speed, QString time, QString mistakes)
{
    int rowIndex = ui->tableWidget_info->rowCount();

    if(rowIndex >= maxROWS){
        ui->tableWidget_info->removeRow(0);
        rowIndex--;
    }

    ui->tableWidget_info->insertRow(rowIndex);
    ui->tableWidget_info->setItem(rowIndex, 0, new QTableWidgetItem(date));
    ui->tableWidget_info->setItem(rowIndex, 1, new QTableWidgetItem(name));
    ui->tableWidget_info->setItem(rowIndex, 2, new QTableWidgetItem(speed));
    ui->tableWidget_info->setItem(rowIndex, 3, new QTableWidgetItem(time));
    ui->tableWidget_info->setItem(rowIndex, 4, new QTableWidgetItem(mistakes));

    for(int j = 0; j < maxCOLS; j++){
        ui->tableWidget_info->item(rowIndex, j)->setTextAlignment(Qt::AlignCenter);
    }
}

void InfoTable::backToMenu()
{
    emit goToMenu();
}

void InfoTable::clearInfo()
{
    while(ui->tableWidget_info->rowCount() > 0){
        ui->tableWidget_info->removeRow(0);
    }

    QFile::remove(FILEPATH);
}

void InfoTable::saveInfo()
{
    QFile progress(FILEPATH);
    if(!progress.open(QIODevice::ReadWrite | QIODevice::Text)){
        return;
    }

    QTextStream out(&progress);
    for(int i = 0; i < ui->tableWidget_info->rowCount(); i++){
        for(int j = 0; j < maxCOLS; j++){
            out << ui->tableWidget_info->item(i, j)->text() << "\n";
        }
    }

    progress.close();
}

void InfoTable::loadInfo()
{
    QFile progress(FILEPATH);
    if(!progress.open(QIODevice::ReadWrite | QIODevice::Text)){
        return;
    }

    QTextStream in(&progress);
    while(!in.atEnd()){
        QString date     = in.readLine();
        QString name     = in.readLine();
        QString speed    = in.readLine();
        QString time     = in.readLine();
        QString mistakes = in.readLine();
        setRow(date, name, speed, time, mistakes);
    }

    progress.close();
}
