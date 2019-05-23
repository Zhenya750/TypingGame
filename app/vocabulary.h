#ifndef VOCABULARY_H
#define VOCABULARY_H

#include <QMap>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include "mathfuncs.h"

class Vocabulary
{
public:
    Vocabulary();

private:
    QMap<QChar, QVector<QString> *> vocabulary;
    QMap<QChar, int> alphabet;

public:
    int load(QString path);
    QString setNewStr(QChar c = '0');
    void clearAlpha();

};

#endif // VOCABULARY_H
