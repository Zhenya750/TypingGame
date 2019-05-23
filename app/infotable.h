#ifndef INFOTABLE_H
#define INFOTABLE_H

#include <QWidget>
#include <QFile>
#include <QTextStream>

namespace Ui {
class InfoTable;
}

class InfoTable : public QWidget
{
    Q_OBJECT

public:
    explicit InfoTable(QWidget *parent = nullptr);
    ~InfoTable();

    void setRow(QString date, QString name, QString speed, QString time, QString mistakes);
    void saveInfo();
    void loadInfo();

private:
    Ui::InfoTable *ui;
    int maxROWS;
    int maxCOLS;

private slots:
    void backToMenu();
    void clearInfo();

signals:
    void goToMenu();
};

#endif // INFOTABLE_H
