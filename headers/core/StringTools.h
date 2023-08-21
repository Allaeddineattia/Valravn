//
// Created by alla on 20/08/23.
//

#ifndef MYPROJECT_STRINGTOOLS_H
#define MYPROJECT_STRINGTOOLS_H

#include <string>
#include <regex>

using namespace std;

class StringTools
{
public:

    static void remove_blanks(string & str){
        size_t found = str.find(' ');
        while(found != string::npos){
            str.erase(str.begin() + found);
            found = str.find(' ');
        }
    }

    /**
     * Throws error if the provided string view does not follow the resolution format
     * valid examples: 1920:1080, 1280:720
     * @param resolution
     */
    static void check_resolution_string_pattern(string_view resolution){
        regex resolution_pattern("^([1-9]\\d{2,3}:[1-9]\\d{2,3})$");
        if(! regex_match(resolution.data(), resolution_pattern)){
            throw invalid_argument("Error:Resolution shape int:int");
        }
    }
};

#endif //MYPROJECT_STRINGTOOLS_H
