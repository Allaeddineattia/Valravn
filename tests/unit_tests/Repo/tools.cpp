//
// Created by alro on 23‏/1‏/2021.
//

#include "gtest/gtest.h"
#include <string>
#include <core/Tools.h>
using namespace std ;
TEST(Tools, Generate_Random) {
    string str = "120 : 120";
    for (int i = 0; i<10; i++){
        cout<<Tools::generate_random_value()<<endl;
    }

}