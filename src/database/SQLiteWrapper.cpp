//
// Created by alro on 28‏/11‏/2020.
//

#include <iostream>
#include <sqlite3.h>
#include <sstream>

#include "database/SQLiteWrapper.h"
#include <database/Error.h>

using namespace std;
using namespace DataBase;

SQLiteWrapper::SQLiteWrapper(string_view dbPath) {
    if (dbPath.empty()) {
        throw Exceptions::DB_NAME_NOT_SET();
    }
    data_path = dbPath;
    db = make_unique<sqlite3 *>();
    int rc = sqlite3_open(data_path.c_str(), db.get());
    if (rc) {
        cout<<"[DataBase] Can't open database: "<<sqlite3_errmsg(*db)<<endl;
        this->is_db_initialised = false;
        throw Exceptions::C_ANT_OPEN_DB();
    } else {
        this->is_db_initialised = true;
        cout<<"[DataBase] Opened database successfully"<<endl;
    }
}

void SQLiteWrapper::init_db() {
    activate_foreign_keys();
    for (auto &i: tables_initiation_commands) {
        if (!is_db_initialised) break;
        create_table(i);
    }
}

string_view SQLiteWrapper::get_db_path () {
    return data_path;
}


SQLiteWrapper::~SQLiteWrapper() {
    sqlite3_close(reinterpret_cast<sqlite3 *>(db.get()));
    cout << "[DataBase] Database destructor have been called" << endl;
}

typedef int (*SqliteCallbackType)(void*, int, char**, char**);

std::pair<SqliteCallbackType, void *> getSQLiteCallback (const SQLHelpers::SQLiteResultHandler& callback)
{
    SqliteCallbackType sqlite_callback = nullptr;
    void * user_state = nullptr;
    if(callback){
        sqlite_callback = [](void * callback, int argc, char **argv, char **azColName) {
            string_map result;
            auto *user_callback = static_cast<function<bool(const string_map&)> *> (callback);
            int i;
            for (i = 0; i < argc; i++) {
                result.insert(string_pair(azColName[i], argv[i]));
            }
            return (*user_callback)(result) ? 0 : -1;
        };
        user_state = (void *) &callback;
    }
    return {sqlite_callback, user_state};

}

void SQLiteWrapper::execute_sql(
        string_view sql,
        string_view success_msg = SQLHelpers::default_success_message,
        const SQLHelpers::SQLiteResultHandler& callback = nullptr,
        const SQLHelpers::SQLiteErrorHandler &do_if_error = SQLHelpers::default_error_handler
        ) {
    char *zErrMsg = nullptr;
    std::pair<SqliteCallbackType, void *> callbackPair = getSQLiteCallback(callback);
    SqliteCallbackType sqlite_callback = callbackPair.first;
    void * user_state = callbackPair.second;
    if (sqlite3_exec(*db, sql.data(), sqlite_callback, user_state, &zErrMsg) != SQLITE_OK) {
        do_if_error(zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        cout << success_msg << endl;
    }
}

string_map SQLiteWrapper::get_by_id(string_view table_name, string_view id) {
    std::stringstream sql_stream;
    sql_stream << "SELECT * FROM " << table_name << " WHERE ID=" << id;
    std::string sql = sql_stream.str();

    std::string success_message = "[DataBase] Retrieve By id succeeded";
    string_map result;
    SQLHelpers::SQLiteErrorHandler error_handler = [&table_name, &id](string_view error_msg) -> bool {
        throw Exceptions::DataBaseRetrievingError(table_name, id);
    };
    SQLHelpers::SQLiteResultHandler result_handler = [&result](const string_map &map) mutable -> bool {
        result = map;
        return true;
    };
    execute_sql(sql, success_message, result_handler, error_handler);
    return  result;
}


void SQLiteWrapper::create_table(string_view sql_command) {
    std::string success_message = "[DataBase] Table created successfully\n";
    SQLHelpers::SQLiteResultHandler result_handler = nullptr;
    SQLHelpers::SQLiteErrorHandler error_handler = [](string_view error_msg) -> void
    {
        if  (error_msg.find("table") != std::string::npos
             &&
             error_msg.find("already exists") != std::string::npos){
            cout << "[DataBase] QL Warning: " << error_msg << endl;
            return ;
        };
        cerr << "[DataBase] QL error: " << error_msg << endl;
        throw Exceptions::C_ANT_CREATE_TABLE();
    };
    execute_sql(sql_command, success_message, result_handler, error_handler);

}

void SQLiteWrapper::insert_into_table(string_view table_name, const string_map &values) {

    string sql_command = SQLHelpers::get_insert_sql(table_name, values);
    std::string success_message = "[DataBase] Row inserted successfully";
    SQLHelpers::SQLiteErrorHandler error_handler = [&](string_view error_msg) -> bool {
        cerr << "[DataBase] SQL error: " << error_msg << endl;
        throw Exceptions::DataBaseInsertIntoTableError(table_name, error_msg);
    };
    SQLHelpers::SQLiteResultHandler result_handler = nullptr;
    execute_sql(sql_command, success_message, result_handler, error_handler);
}


void SQLiteWrapper::update_into_table(string_view table_name, const string_pair &select_key, const string_map &updated_values) {
    string sql_command = SQLHelpers::get_update_sql(table_name, select_key, updated_values);
    std::string success_message = "[DataBase] Row inserted successfully";
    execute_sql(sql_command, success_message);
}

void SQLiteWrapper::activate_foreign_keys() {
    string sql_command = "PRAGMA foreign_keys=on;";
    std::string success_message = "[DataBase] Foreign keys activated";
    SQLHelpers::SQLiteResultHandler result_handler = nullptr;
    SQLHelpers::SQLiteErrorHandler error_handler = [](string_view error_msg) -> void{
        throw Exceptions::C_ANT_ACTIVATE_FOREIGN_KEY();
    };
    execute_sql(sql_command, success_message, result_handler, error_handler);
}

void SQLiteWrapper::begin_transaction() {
    string sql_command = "BEGIN TRANSACTION;";
    std::string success_message = "[DataBase] Transaction started";
    SQLHelpers::SQLiteResultHandler result_handler = nullptr;
    SQLHelpers::SQLiteErrorHandler error_handler = [](string_view error_msg) -> bool{
            cerr<<error_msg<<endl;
            throw Exceptions::C_ANT_START_TRANSACTION();
    };
    execute_sql(sql_command, success_message, result_handler, error_handler);
}

void SQLiteWrapper::end_transaction() {
    string sql_command = "END TRANSACTION;";
    std::string success_message = "[DataBase] Transaction ended";
    SQLHelpers::SQLiteResultHandler result_handler = nullptr;
    SQLHelpers::SQLiteErrorHandler error_handler = [](string_view error_msg) -> void{
        throw Exceptions::C_ANT_END_TRANSACTION();
    };
    execute_sql(sql_command, success_message, result_handler, error_handler);
}

void SQLiteWrapper::abort_transaction() {
    string sql_command = "ROLLBACK TRANSACTION;";
    std::string success_message = "[DataBase] Transaction aborted";
    SQLHelpers::SQLiteResultHandler result_handler = nullptr;
    SQLHelpers::SQLiteErrorHandler error_handler = [](string_view error_msg) -> void{
        throw Exceptions::C_ANT_END_TRANSACTION();
    };
    execute_sql(sql_command, success_message, result_handler, error_handler);
}


void SQLiteWrapper::add_table_creation_sql(string_view sql) {
    tables_initiation_commands.push_back(string(sql));
}


time_t SQLiteWrapper::string_to_time_t(string_view str) {
    string sql_command = "SELECT strftime('%s'," + SQLHelpers::to_sql_string(str) + ");";
    std::string success_message = "[DataBase] Retrieve time_t succeeded";
    time_t result;
    SQLHelpers::SQLiteResultHandler result_handler = [&result](const string_map& map) mutable -> bool {
        result =  stoi(map.begin()->second);
        return true;
    };
    SQLHelpers::SQLiteErrorHandler error_handler = [](string_view error_msg) -> bool {
        cerr<<"SQL error: %s\n"<< error_msg<<endl;
        throw Exceptions::DataBaseRetrievingError("Time_T", "str");
    };
    execute_sql(sql_command, success_message, result_handler, error_handler);
    return result;
}

vector<string_map> SQLiteWrapper::get_all_by_feature(string_view table_name, const string_pair &feature) {
    std::stringstream sql_stream;
    sql_stream << "SELECT * FROM " << table_name << " WHERE " << feature.first << "=" << feature.second;
    std::string sql_command = sql_stream.str();
    vector<string_map> result;
    std::string success_message = "[DataBase] Retrieve many succeeded";
    SQLHelpers::SQLiteResultHandler result_handler = [&result](const string_map& map) mutable -> bool {
        result.push_back(map);
        return true;
    };
    SQLHelpers::SQLiteErrorHandler error_handler = [&](string_view error_msg) -> bool {
        cerr<<"[DataBase] SQL error: %s\n"<< error_msg<<endl;
        throw Exceptions::DataBaseRetrievingError(table_name, feature.first, feature.second);
    };
    execute_sql(sql_command, success_message, result_handler, error_handler);

    return result;
}


vector<string_map> SQLiteWrapper::get_all(string_view table_name) {
    std::stringstream sql_stream;
    sql_stream << "SELECT * FROM " << table_name;
    std::string sql_command = sql_stream.str();
    std::string success_message = "[DataBase] Retrieve many succeeded";
    vector<string_map> result;
    SQLHelpers::SQLiteResultHandler result_handler =[&result](const string_map& map) mutable -> bool {
        result.push_back(map);
        return true;
    };
    SQLHelpers::SQLiteErrorHandler error_handler =[&](string_view error_msg) -> bool {
        cerr<<"SQL error: %s\n"<< error_msg<<endl;
        throw Exceptions::DataBaseRetrievingError(table_name);
    };
    execute_sql(sql_command, success_message, result_handler, error_handler);
    return result;
}

void SQLiteWrapper::delete_by_feature(string_view table_name, const string_pair &filter) {
    std::stringstream sql_stream;
    sql_stream << "DELETE FROM " << table_name << " WHERE " << filter.first << "=" << filter.second;
    std::string sql_command = sql_stream.str();
    std::string success_message = "[DataBase] Delete From Table Succeeded";
    SQLHelpers::SQLiteResultHandler result_handler = nullptr;
    SQLHelpers::SQLiteErrorHandler error_handler =  [&](string_view error_msg) -> bool {
        cerr<<"SQL error: %s\n"<< error_msg<<endl;
        throw Exceptions::DataBaseRetrievingError(table_name);
    };
    execute_sql(sql_command, success_message, result_handler, error_handler);
}




