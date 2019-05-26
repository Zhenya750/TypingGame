#ifndef ENEMY_HEAL_T_H
#define ENEMY_HEAL_T_H

#include <gtest/gtest.h>
#include "enemy.h"

TEST(heal, t1){

    Enemy *e = new Enemy("name");
    e->moveEnemy(20, 30);

    QString str = "newName";
    e->heal(str);

    bool n   = e->getStr() == str;
    bool xy1 = (std::abs(e->x) >= 450 && std::abs(e->x) <= 600) &&
               (std::abs(e->y) >= 350 && std::abs(e->y) <= 500);
    bool xy2 = (std::abs(e->x) >= 0   && std::abs(e->x) <= 400) &&
               (std::abs(e->y) >= 350 && std::abs(e->y) <= 500);
    bool xy3 = (std::abs(e->x) >= 450 && std::abs(e->x) <= 600) &&
               (std::abs(e->y) >= 0   && std::abs(e->y) <= 300);

    if(!n || !(xy1 || xy2 || xy3)){

        std::cout << "enemy name:\n\texpected: " << str.toStdString() << "\n\treceived: " << e->getStr().toStdString() << std::endl;
        std::cout << "x: " << e->x << " y: " << e->y << std::endl;

        FAIL();
    }
    SUCCEED();


}
#endif // ENEMY_HEAL_T_H
