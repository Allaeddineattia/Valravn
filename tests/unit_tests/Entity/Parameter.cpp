//
// Created by alro on 21‏/11‏/2020.
//

#include <media_player/Parameter.h>
#include <gtest/gtest.h>
using namespace std;
TEST(Parameter, Valid_Creation){
    auto parameter = make_unique<Parameter>(true, 100, 30000, 50);
    ASSERT_TRUE(parameter->is_fullscreen());
    ASSERT_EQ(parameter->get_volume(), 100);
    ASSERT_EQ(parameter->get_timeout(), 30000);
    ASSERT_EQ(parameter->get_speed(), 50);
}