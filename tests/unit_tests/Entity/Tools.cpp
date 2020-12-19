//
// Created by ismail on 22‏/11‏/2020.
//
#include "gtest/gtest.h"
#include <string>
#include "Shared/Tools.h"
using namespace std ;
TEST(Tools, Valid_remove_blanks) {
    string str = "120 : 120";
    Tools::remove_blanks(str);
    ASSERT_EQ(str,"120:120");
}
TEST(Tools,Throw_error_on_check_resolution){
    string str = "12:58";
    ASSERT_THROW(Tools::check_resolution_string_pattern(str),invalid_argument);
}

TEST(Tools,Valid_check_resolution){
    string str = "1080:720";
    Tools::check_resolution_string_pattern(str);
}