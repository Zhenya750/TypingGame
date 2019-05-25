#ifndef HERO_RECHARGE_T_H
#define HERO_RECHARGE_T_H

#include <gtest/gtest.h>
#include "hero.h"

TEST(recharge, t1){

    Hero *hero = new Hero();
    int mode = FREE;
    Enemy *e = nullptr;

    for(int i = 1; i <= 30; i++){

        if(i > 10) mode = READY;
        if(i > 20) mode = SHOT;
        if(i > 15) e    = new Enemy("name");

        Bullet *b = new Bullet();
        b->setActive(mode);
        b->setTarget(e);
        b->moveBullet(i, i + i);

        hero->recharge(b);

        bool n = b->getEnemy()  == nullptr;
        bool m = b->getActive() == FREE;
        bool l = (b->x + b->y)  == 0;

        if(!n || !m || !l){

            std::cout << "enemy == nullptr:\t" << n << std::endl;
            std::cout << "active == FREE:\t"   << m << std::endl;
            std::cout << "x = 0 & y = 0:\t"    << l << std::endl;

            FAIL();
        }
    }

    SUCCEED();
}

#endif // HERO_RECHARGE_T_H
