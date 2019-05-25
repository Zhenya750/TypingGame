#ifndef HERO_RECHARGE_T_H
#define HERO_RECHARGE_T_H

#include <gtest/gtest.h>
#include "hero.h"

TEST(recharge, t1){

    Hero *hero = new Hero();

    for(int i = 0; i < 20; i++){

        Bullet *b = new Bullet();
        b->setActive(SHOT);
        b->setTarget(nullptr);
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

TEST(recharge, t2){

    Hero *hero = new Hero();

    for(int i = 0; i < 20; i++){

        Bullet *b = new Bullet();
        b->setActive(SHOT);
        b->setTarget(new Enemy("name"));
        b->moveBullet(i * 2, i + i);

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
