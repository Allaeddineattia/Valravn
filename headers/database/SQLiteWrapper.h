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



namespace DataBase
{
    class SQLiteWrapper {
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
        void execute_sql(string_view sql, string_view success_msg, const SQLHelpers::SQLiteResultHandler & handle_result,
                         const SQLHelpers::SQLiteErrorHandler & handle_error);

    public:

        explicit SQLiteWrapper(string_view dbPath);

        virtual ~SQLiteWrapper();

        /**
         *
         * @return the path to file containing the database infromation
         */
        string_view get_db_path();

        /**
         *
         * @param table_name : the name of the table where the new row will be inserted
         * @param values : map of of keys of values of the row of the table. For example if user have id, name, age
         * the map will contain {("id":"5", "name":"Joe", age:"25" )}
         */
        void insert_into_table(string_view table_name, const string_map &values);


        /**
         * Update the row that gets fetched from table_name using the filter to update the new values
         * @param table_name : the name of the table where the new row will be updated.
         * @param filter : the filter that needs to be matched to fetch the row. example ("id", 5)
         * @param updated_values : map of of keys of values of the row of the table. For example if user have id, name, age
         * the map will contain {("name":"Jane", age:"28" )}
         */
        void update_into_table(string_view table_name, const string_pair &filter, const string_map &updated_values);


        /**
         *
         * @param table_name : the name of the table where the row will be deleted.
         * @param filter : the filter that needs to be matched to fetch the row. example ("id", 5).
         */
        void delete_by_feature(string_view table_name, const string_pair &filter);

        void init_db();


        /**
         * A transaction is a mechanism to execute a set of sql transactions together if one of them fails
         * the others will be rolled back. It is a good mechanism to keep the integrity of the database.
         * end_transaction should be called when the sql commands are set.
         */
        void begin_transaction();

        /**
         * should only be called after begin transaction have been previously called.
         */
        void end_transaction();

        /**
         * should only be called after begin transaction have been previously called.
         */
        void abort_transaction();

        /**
         * Add a creation table sql command to be executed when the database is initiated.
         * @param sql : create table sql
         */
        void add_table_creation_sql(string_view sql);

        /**
         *
         * @param table_name
         * @param id
         * @return : a string map that contains the values of the row mapped by the name of the value
         * example for User table: {("id":5, "name":"Joe", age:"25" )}
         */
        string_map get_by_id(string_view table_name, string_view id);

        time_t string_to_time_t(string_view string);


        vector<string_map> get_all_by_feature(string_view table_name, const string_pair &feature);

        /**
         *
         * @param table_name
         * @return: every row in the table presented in a vector of string maps.
         * example for User table: {("id":5, "name":"Joe", age:"25" ), ("id":6, "name":"Jane", age:"28" )}
         */
        vector<string_map> get_all(string_view table_name);

    };

}








#endif //VALRAVEN_DATABASE_H
