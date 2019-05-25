#ifndef ENEMY_DOCMP_T_H
#define ENEMY_DOCMP_T_H

#include <gtest/gtest.h>
#include "enemy.h"

TEST(doCmp, t1){

    Enemy *e = new Enemy("abcde");

    int count = 0;

    for(int i = 'a'; i <= 'e'; i++){

        QString letter(i);
        count+= e->doCmp(letter);
    }

    if(count != e->getStr().size()){
        std::cout << "expected:\t" << e->getStr().size() << std::endl;
        std::cout << "enemy count\t" << count << std::endl;
        FAIL();
    }
    SUCCEED();
}

TEST(doCmp, t2){

    Enemy *e = new Enemy("abzdz");

    int count = 0;

    for(int i = 'a'; i <= 'e'; i++){

        QString letter(i);
        count+= e->doCmp(letter);
    }

    if(count != 2){
        std::cout << "expected:\t2"   << std::endl;
        std::cout << "enemy count:\t" << count << std::endl;
        FAIL();
    }
    SUCCEED();
}

#endif // ENEMY_DOCMP_T_H
