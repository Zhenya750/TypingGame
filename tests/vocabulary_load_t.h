#ifndef VOCABULARY_LOAD_T_H
#define VOCABULARY_LOAD_T_H

#include <gtest/gtest.h>
#include "vocabulary.h"

TEST(load, t1){

    Vocabulary *v = new Vocabulary();
    int opened = v->load(":file/sources/enwords_t");

    if(opened == -1){
        std::cout << "Can not open file" << std::endl;
        FAIL();
    }

    /* load information from file to voc */
    QMap<QChar, QVector<QString> *> voc = v->getVocabulary();

    /* create similar vocabulary to compare */
    QMap<QChar, QVector<QString> *> voc_t;

    for(int i = 'a'; i <= 'z'; i++){
        voc_t.insert(i, new QVector<QString>);
    }

    for(char i = 'a'; i <= 'z'; i++){

        QString str;
        str.append(i);
        str.append(i);
        str.append(i);

        voc_t.value(i)->append(str);
    }

    voc_t.value('c')->append("cccc");
    voc_t.value('c')->append("ccccc");
    voc_t.value('z')->append("zzzz");


    for(char i = 'a'; i <= 'z'; i++){

        for(int j = 0; j < voc.value(i)->size(); j++){

            if(voc.value(i)->at(j) != voc_t.value(i)->at(j)){
                std::cout << "key: " << i << " on line: " << j << "\n" << std::endl;
                std::cout << "\texpected: " << voc_t.value(i)->at(j).toStdString() << std::endl;
                FAIL();
            }
        }
    }

    SUCCEED();
}

TEST(load, t2){

    Vocabulary *v = new Vocabulary();
    int opened = v->load(":file/sources/empty_t");

    if(opened == -1){
        std::cout << "Can not open file" << std::endl;
        FAIL();
    }

    QMap<QChar, QVector<QString> *> arr = v->getVocabulary();

    for(char i = 'a'; i <= 'z'; i++){

        for(char j = 0; j < arr.value(i)->size(); j++){

            if(arr.value(i)->at(j) != i){
                FAIL();
            }
        }
    }
    SUCCEED();
}

#endif // VOCABULARY_LOAD_T_H
