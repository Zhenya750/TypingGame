#include <gtest/gtest.h>
#include "getrand_t.h"
#include "hero_recharge_t.h"
#include "hero_isheadshot_t.h"
#include "enemy_docmp_t.h"
#include "enemy_heal_t.h"
#include "vocabulary_clearalpha_t.h"
#include "vocabulary_load_t.h"


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
