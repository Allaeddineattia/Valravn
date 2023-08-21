//
// Created by alla on 20/08/23.
//

#include <sstream>
#include <database/SQLHelpers.h>

SQLiteErrorHandler default_error_handler =
        [](string_view error_msg) -> void {
            std::cerr << "[DataBase] SQL error: " << error_msg << endl;
            throw Repo::Exceptions::DB_ERROR(error_msg);
        };

string SQLHelpers::get_insert_sql(string_view table_name, const string_map &map) {
    std::ostringstream sql_stream;
    sql_stream << "INSERT INTO " << table_name << " (";

    bool first = true;
    for (const auto& pair : map) {
        if (!first) {
            sql_stream << ", ";
        }
        sql_stream << pair.first;
        first = false;
    }

    sql_stream << ") VALUES (";

    first = true;
    for (const auto& pair : map) {
        if (!first) {
            sql_stream << ", ";
        }
        sql_stream << "'" << pair.second << "'";
        first = false;
    }
    sql_stream << ");";

    return sql_stream.str();
}

string SQLHelpers::get_update_sql(string_view table_name, const string_pair &feature, const string_map &map) {
    std::ostringstream sqlStream;
    sqlStream << "UPDATE " << table_name << " SET ";

    // Loop through the map and construct the SET part of the SQL
    bool first = true;
    for (const auto& pair : map) {
        if (!first) {
            sqlStream << ", ";
        }
        sqlStream << pair.first << " = '" << pair.second << "'";
        first = false;
    }

    sqlStream << " WHERE " << feature.first << " = '" << feature.second << "';";

    return sqlStream.str();
}