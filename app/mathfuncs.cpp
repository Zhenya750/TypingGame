#include "mathfuncs.h"

int getRand(int minLeft, int left, int right, int maxRight)
{
    if(minLeft > left || right > maxRight || left > right){
        return 0;
    }

    if(left == 0 && right == 0){
        return (minLeft + rand() % (maxRight - minLeft + 1));
    }

    if(getRand(0, 0, 0, 1) == 0){
        return (minLeft + rand() % (left     - minLeft + 1));
    }
    else {
        return (right   + rand() % (maxRight - right   + 1));
    }
}
