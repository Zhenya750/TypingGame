#ifndef SAVER_H
#define SAVER_H

#include <QWidget>
#include <QDateTime>
#include <QRegExp>

namespace Ui {
class Saver;
}

class Saver : public QWidget
{
    Q_OBJECT

public:
    explicit Saver(QWidget *parent = nullptr);
    ~Saver();

private:
    Ui::Saver *ui;
    QString speed;
    QString mistakes;
    QString time;
    QString nickname;
    QString date;

public:
    void setInfo(qreal speed, qreal timeSec, qreal mistakes);

private slots:
    void saveInfo();
    void backtoMenu();

signals:
    void goToMenu();
    void saveResult(QString date, QString name, QString speed, QString time, QString mistakes);

};

#endif // SAVER_H
