#include "vocabulary.h"

Vocabulary::Vocabulary()
{
    for(int i = 'a'; i <= 'z'; i++){
        alphabet.insert(i, 0);
        vocabulary.insert(i, new QVector<QString>);
    }
}

int Vocabulary::load(QString path)
{
    QFile fin(path);
    if(!fin.open(QIODevice::ReadOnly | QIODevice::Text)){
        return -1;
    }

    QTextStream in(&fin);
    while(!in.atEnd()){

        QString current = in.readLine();

        if(current.size() < 1 || current[0] < 'a' || current[0] > 'z'){
            continue;
        }
        vocabulary.value(current[0])->append(current);
    }

    for(int i = 'a'; i <= 'z'; i++){

        if(vocabulary.value(i)->size() == 0){
            vocabulary.value(i)->append(QString(i));
        }
    }

    return 0;
}

QString Vocabulary::setNewStr(QChar c)
{
    if(c >= 'a' && c <= 'z'){
        alphabet.insert(c, 0);
    }

    QString freeLetter;

    for(char i = 'a'; i <= 'z'; i++){
        if(alphabet.value(i) == 0){
            freeLetter.append(i);
        }
    }

    int indexLetter = getRand(0, 0, 0, freeLetter.size() - 1);
    QChar letter    = freeLetter[indexLetter];
    int index       = getRand(0, 0, 0, vocabulary.value(letter)->count() - 1);

    alphabet.insert(letter, 1);

    return vocabulary.value(letter)->at(index);
}

void Vocabulary::clearAlpha()
{
    for(int i = 'a'; i <= 'z'; i++){
        alphabet.insert(i, 0);
    }
}

QMap<QChar, int> Vocabulary::getAlphabet()
{
    return alphabet;
}

QMap<QChar, QVector<QString> *> Vocabulary::getVocabulary()
{
    return vocabulary;
}
