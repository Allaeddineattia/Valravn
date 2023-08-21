//
// Created by alro on 28‏/11‏/2020.
//

#ifndef VALRAVEN_DATABASE_H
#define VALRAVEN_DATABASE_H


#include <memory>
#include <string_view>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <sqlite3.h>

#include "SQLHelpers.h"
using namespace std;



class DataBase {
private:

    /**
     * ! Path to the file containing the sqlite data
     **/
    string data_path;

    /**
     * ! Path to the file containing the sqlite data
     **/
    bool is_db_initialised;

    /**
     * ! sqlite3 database object
     */
    unique_ptr<sqlite3 *> db;

    /**
     * A list of sql commands that enables initiating the database tables if they do not exist.
     */
    vector<string> tables_initiation_commands;

    /**
     * Execute the sql command in order to create a table if it doesn't exist.
     * @param sql_command : sql command that contains instructions to create a table.
     */
    void create_table(string_view sql_command);

    /**
     * Activate Foreign keys usage in SQLite3
     */
    void activate_foreign_keys();



    /**
     * execute an sql command and call the appropriate handlers according to the result.
     * @param sql: command to be executed by the sqlite library.
     * @param success_msg : message to display to the user when the operation is successful.
     * @param handle_result : callback that handles the retrieved information resulted from the sql command.
     * @param handle_error  : callback to be called when to the operations fails.
     */
    void execute_sql(string_view sql, string_view success_msg, const SQLiteResultHandler & handle_result,
                     const SQLiteErrorHandler & handle_error);

public:

    explicit DataBase(string_view dbPath);

    string_view get_db_path();

    virtual ~DataBase();

    void insert_into_table(string_view table_name, const string_map &map);

    void update_into_table(string_view table_name, const string_pair &select_feature, const string_map &map);

    void delete_by_feature(string_view table_name, const string_pair &feature);

    void init_db();

    void begin_transaction();

    void end_transaction();

    void abort_transaction();

    void add_table_creation_sql(string_view sql);

    string_map get_by_id(string_view table_name, string_view id);

    time_t string_to_time_t(string_view string);

    vector<string_map> get_all_by_feature(string_view table_name, const string_pair &feature);

    vector<string_map> get_all(string_view table_name);

    static string to_sql_string(string_view s);

    static string to_sql_date_time(time_t t);



};








#endif //VALRAVEN_DATABASE_H
