#ifndef VOCABULARY_CLEARALPHA_T_H
#define VOCABULARY_CLEARALPHA_T_H

#include <gtest/gtest.h>
#include "vocabulary.h"

TEST(clearAlpha, t1){

    Vocabulary *v = new Vocabulary();
    v->load(":file/sources/enwords_t");

    /* set few letters in alphabet */
    for(int i = 0; i < 5; i++){
        v->setNewStr();
    }

    /* clear alphabet, free all letters */
    v->clearAlpha();

    QMap<QChar, int> arr = v->getAlphabet();

    for(char i = 'a'; i <= 'z'; i++){
        if(arr.value(i)){
            std::cout << "alphabet[" << i << "] = " << arr.value(i) << std::endl;
            FAIL();
        }
    }
    SUCCEED();
}





#endif // VOCABULARY_CLEARALPHA_T_H
