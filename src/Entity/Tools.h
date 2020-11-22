//
// Created by alro on 14‏/11‏/2020.
//

#ifndef MYPROJECT_TOOLS_H
#define MYPROJECT_TOOLS_H
#include <string_view>
#include <regex>

using namespace std;

class Tools{
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


#endif //MYPROJECT_TOOLS_H
