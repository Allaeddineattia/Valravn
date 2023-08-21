//
// Created by alla on 18/08/23.
//

#ifndef MYPROJECT_SQLHELPERS_H
#define MYPROJECT_SQLHELPERS_H

#include <string_view>
#include <string>
#include <functional>
#include <map>
#include <database/Error.h>
#include <iostream>
using namespace std;


typedef map<string, string> string_map;
typedef pair<string, string> string_pair;



namespace SQLHelpers
{

    typedef function<void(const string_map &)> SQLiteResultHandler;
    typedef function<void(string_view)> SQLiteErrorHandler;
    extern SQLiteErrorHandler default_error_handler;
    const string default_success_message = "[DataBase] OPERATION_SUCCEEDED";

    string get_insert_sql(string_view table_name, const string_map &map);

    string get_update_sql(string_view table_name, const string_pair &feature, const string_map &map);

    string to_sql_string(string_view s);

    string to_sql_date_time(time_t t);

}


#endif //MYPROJECT_SQLHELPERS_H
