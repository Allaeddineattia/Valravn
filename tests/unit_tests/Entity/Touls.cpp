//
// Created by ismail on 22‏/11‏/2020.
//
#include "gtest/gtest.h"
#include <string>
#include "Entity/Tools.h"
using namespace std ;
TEST(Tools, ThrowErrorOnremove_blanks) {
    string str = "120 : 120";
    Tools::remove_blanks(str);
    ASSERT_EQ(str,"120:120");
}
