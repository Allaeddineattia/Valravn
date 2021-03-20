//
// Created by alro on 23‏/1‏/2021.
//

#ifndef MYPROJECT_TOOLS_H
#define MYPROJECT_TOOLS_H
#include <iostream>
#include <random>
#include <limits>
class Tools{
public:
    static unsigned int generate_random_value(){
        std::random_device rd;     //Get a random seed from the OS entropy device, or whatever
        std::mt19937 eng(rd()); //Use the 32-bit Mersenne Twister 19937 generator
        //and seed it with entropy.

        //Define the distribution, by default it goes from 0 to MAX(unsigned long long)
        //or what have you.
        std::uniform_int_distribution<unsigned int> distr;

        return distr(eng);
    }

};

#endif //MYPROJECT_TOOLS_H
