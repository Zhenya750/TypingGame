#ifndef GETRAND_T_H
#define GETRAND_T_H

#include <gtest/gtest.h>
#include "mathfuncs.h"

TEST(getRand, t1) {

    int v[7];

    v[0] = getRand(0, -1,  0, 10);
    v[1] = getRand(0,  0, -1, 10);
    v[2] = getRand(0, -1, -2, 10);
    v[3] = getRand(0, -2, -1, 10);
    v[4] = getRand(0,  5,  3, 10);
    v[5] = getRand(0,  5,  6,  2);
    v[6] = getRand(10, 5,  6,  2);

    int res = 0;

    for(int i = 0; i < 7; i++){
        res+= v[i];
    }

    if(res == 0){
        SUCCEED();
    }
    else{
        FAIL();
    }
}

TEST(getRand, t2) {

    int v = 0;

    for(int j = 0; j < 600; j++){
        for (int i = 0; i < 5; i++){

            v = getRand(0, 0, 0, j);

            if(v < 0 || v > j){
                std::cout << v << " " << j <<  std::endl;
                FAIL();
            }
        }
    }
}

TEST(getRand, t3) {

    int v = 0;

    int ml = 1;
    int l  = 2;
    int r  = 3;
    int mr = 4;

    for(int j = 0; j < 4; j++){
        for (int i = 0; i < 10; i++){

            v = getRand(ml, l, r, mr);

            bool n = v > l && v < r;
            bool m = v < ml || v > mr;

            if(m || n){
                std::cout << v << std::endl;
                FAIL();
            }
            std::cout << v << ": " << ml << "-" << l << " " << r << "-" << mr <<  std::endl;
        }

        ml*= ml;
        l*=  l;
        r*=  r;
        mr*= mr;
    }
}

#endif // GETRAND_T_H
