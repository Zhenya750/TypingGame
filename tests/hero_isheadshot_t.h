#ifndef HERO_ISHEADSHOT_T_H
#define HERO_ISHEADSHOT_T_H

#include <gtest/gtest.h>
#include "hero.h"

TEST(isHeadShot, t1){

    Hero *hero = new Hero();
    Bullet *b  = new Bullet();
    Enemy *e   = nullptr;

    b->setTarget(e);

    if(hero->isHeadShot(b)){
        std::cout << "Enemy == nullptr\nexptected false" << std::endl;
        FAIL();
    }
    SUCCEED();

}

TEST(isHeadShot, t2){

    Hero *hero = new Hero();
    Bullet *b  = new Bullet();
    Enemy *e   = new Enemy("name");

    b->setActive(SHOT);

    int sgnX = 1;
    int sgnY = -1;

    for(int j = 0; j < 4; j++){

        if(j == 3){
            sgnY = 1;
        }

        e->moveEnemy(sgnX * 20, sgnY * 40);
        e->k = (e->y + 0.0) / e->x;
        e->signOX = e->x >= 0 ? 1 : -1;

        b->setTarget(e);

        bool success = false;

        for(int i = 0; i < std::abs(e->x); i++){

            if(qAbs(b->getEnemy()->k) > 1){

                b->moveBullet(int(b->y * (1 + 0.0) / b->getTarget()), b->y + 2 * b->getSignOY());
            }
            else{
                b->moveBullet(b->x + 2 * b->getSignOX(), int(b->x * b->getTarget()));
            }

            if(hero->isHeadShot(b)){
                success = true;
            }
        }

        if(!success){
            double dx = (std::sqrt(e->x * e->x + e->y * e->y) - 15) * std::cos(std::atan(e->k));
            double dy = (std::sqrt(e->x * e->x + e->y * e->y) - 15) * std::sin(std::atan(e->k));

            std::cout << "Bullet x: |" << b->x << "| < |" << std::ceil(dx) << "|" << std::endl;
            std::cout << "Bullet y: |" << b->y << "| < |" << std::ceil(dy) << "|" << std::endl;
            std::cout << "Enemy  x: |" << e->x << "|" << std::endl;
            std::cout << "Enemy  y: |" << e->y << "|" << std::endl;
            std::cout << "Enemy radius: " << e->getRadius() << std::endl;
            FAIL();
        }

        sgnX*= sgnY;
        sgnY*= sgnX;

        b->moveBullet(0, 0);
    }

    SUCCEED();
}

#endif // HERO_ISHEADSHOT_T_H
