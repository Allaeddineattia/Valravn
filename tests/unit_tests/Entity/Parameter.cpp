//
// Created by alro on 21‏/11‏/2020.
//

#include <media_player/Parameter.h>
#include <gtest/gtest.h>
using namespace std;
TEST(Parameter, Valid_Creation){
    auto parameter = make_unique<Parameter>(true, 100, 30000, 50);
    ASSERT_TRUE(parameter->isFullscreen());
    ASSERT_EQ(parameter->getVolume(), 100);
    ASSERT_EQ(parameter->getTimeout(), 30000);
    ASSERT_EQ(parameter->getSpeed(), 50);
}