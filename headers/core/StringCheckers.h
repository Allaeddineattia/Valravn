//
// Created by alla on 20/08/23.
//

#ifndef MYPROJECT_STRINGCHECKERS_H
#define MYPROJECT_STRINGCHECKERS_H

#include <string>
#include <regex>

using namespace std;

class StringCheckers
{
public:

    static void remove_blanks(string & str){
        int found = str.find(" ");
        while(found != string::npos){
            str.erase(str.begin() + found);
            found = str.find(" ");
        }
    }

    static void check_resolution_string_pattern(string_view resolution){
        regex resolution_pattern("^([1-9]\\d{2,3}:[1-9]\\d{2,3})$");
        if(! regex_match(resolution.data(), resolution_pattern)){
            throw invalid_argument("Error:Resolution shape int:int");
        }
    }
};

#endif //MYPROJECT_STRINGCHECKERS_H
