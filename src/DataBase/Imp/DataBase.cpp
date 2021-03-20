//
// Created by alro on 28‏/11‏/2020.
//

#include <DataBase/Contracts/DataBase.h>
#include <iostream>

#include <Shared/CustomError.h>
#include <ctime>
#include <sqlite3.h>
using namespace std;
using namespace Repo;

DataBase::DataBase(string_view dbPath) {
    if (dbPath.empty()) {
        throw Exceptions::DB_NAME_NOT_SET();
    }
    db_path = dbPath;
    db = make_unique<sqlite3 *>();
    int rc = sqlite3_open(db_path.c_str(), db.get());
    if (rc) {
        cout<<"[DataBase] Can't open database: "<<sqlite3_errmsg(*db)<<endl;
        this->is_db_initialised = false;
        throw Exceptions::C_ANT_OPEN_DB();
    } else {
        this->is_db_initialised = true;
        cout<<"[DataBase] Opened database successfully"<<endl;
    }
}

void DataBase::init_db() {
    activate_foreign_keys();
    for (auto &i: tables_creation_sql) {
        if (!is_db_initialised) break;
        create_table_from_sql(i);
    }
}

string_view DataBase::get_db_path () {
    return db_path;
}


DataBase::~DataBase() {
    sqlite3_close(reinterpret_cast<sqlite3 *>(db.get()));
    cout << "[DataBase] Database destructor have been called" << endl;
}


void DataBase::execute_sql(
        string_view sql,
        string_view success_msg = "[DataBase] OPERATION_SUCCEEDED",
        const function<void(string_view)> &do_if_error =
        [](string_view error_msg) -> void {
            cerr << "[DataBase] SQL error: " << error_msg << endl;
            throw Exceptions::DB_ERROR(error_msg);
        },
        const function<void(const string_map &)> &callback = nullptr) {
    char *zErrMsg = nullptr;
    int (*sqlite_callback)(void *, int, char **, char **) = nullptr;
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
    int rc = sqlite3_exec(*db, sql.data(), sqlite_callback, user_state, &zErrMsg);

    if (rc != SQLITE_OK) {
        do_if_error(zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        cout << success_msg << endl;
    }
}

string_map DataBase::get_by_id(string_view table_name, string_view id) {
    string sql = "select * from ";
    sql += table_name;
    sql += " where ID=";
    sql += id;
    string_map result;
    execute_sql(sql, "[DataBase] Retrieve By id succeeded",
                [&](string_view error_msg) -> bool {
                    throw Exceptions::DataBaseRetrievingError(table_name, id);
                },
                [&result](const string_map& map) mutable -> bool {
                    result = map;
                    return true;
                });

    return  result;

}


void DataBase::create_table_from_sql(string_view sql) {

    execute_sql(sql,
                "[DataBase] Table created successfully\n",
                [](string_view error_msg) -> void
                    {
                       if  (error_msg.find("table") != std::string::npos
                           &&
                           error_msg.find("already exists") != std::string::npos){
                           cout << "[DataBase] QL Warning: " << error_msg << endl;
                           return ;
                       };
                       cerr << "[DataBase] QL error: " << error_msg << endl;
                       throw Exceptions::C_ANT_CREATE_TABLE();
                    }
               );

}

string DataBase::get_insert_sql(string_view table_name, const string_map &map) const {
    string sql1 = "insert into ";
    sql1 += table_name;
    sql1 += "(";
    string sql2 = ") values (";
    for (auto &itr : map) {
        sql1 += " " + itr.first + ",";
        sql2 += " " + itr.second + ",";
    }
    sql1.resize(sql1.size() - 1);
    sql2.resize(sql2.size() - 1);
    string sql = sql1 + sql2 + ");";
    return sql;
}

void DataBase::insert_into_table(string_view table_name, const string_map &map) {

    string sql = get_insert_sql(table_name, map);
    execute_sql(sql, "[DataBase] Row inserted successfully",
                       [&](string_view error_msg) -> bool {
                                cerr << "[DataBase] SQL error: " << error_msg << endl;
                                throw Exceptions::DataBaseInsertIntoTableError(table_name, error_msg);
                        });



}


string DataBase::get_update_sql(string_view table_name, const string_pair &feature, const string_map &map) {
    string sql = "UPDATE ";
    sql += table_name;
    sql += " SET";
    for (auto &itr : map) {
        sql += " " + itr.first + " = " + itr.second + ",";
    }
    sql.resize(sql.size() - 1);
    sql += " WHERE " + feature.first + " = " + feature.second;
    return sql;
}

void DataBase::update_into_table(string_view table_name, const string_pair &select_feature, const string_map &map) {
    string sql = get_update_sql(table_name, select_feature, map);
    return execute_sql(
            sql,
            "[DataBase] Row updated successfully");
}

void DataBase::activate_foreign_keys() {

    string sql = "PRAGMA foreign_keys=on;";
    execute_sql(
            sql,
            "[DataBase] Foreign keys activated",
            [](string_view error_msg) -> void{
                throw Exceptions::C_ANT_ACTIVATE_FOREIGN_KEY();
            });

}

void DataBase::begin_transaction() {
    string sql = "BEGIN TRANSACTION;";
    execute_sql(
            sql,
            "[DataBase] Transaction started",
            [](string_view error_msg) -> bool{
                cerr<<error_msg<<endl;
                throw Exceptions::C_ANT_START_TRANSACTION();
            });

}

void DataBase::end_transaction() {
    string sql = "END TRANSACTION;";
    execute_sql(
            sql,
            "[DataBase] Transaction ended",
            [](string_view error_msg) -> void{
                throw Exceptions::C_ANT_END_TRANSACTION();
            });

}

void DataBase::abort_transaction() {
    string sql = "ROLLBACK TRANSACTION;";
    execute_sql(
            sql,
            "[DataBase] Transaction aborted",
            [](string_view error_msg) -> void{
                throw Exceptions::C_ANT_END_TRANSACTION();
            });
}


void DataBase::add_table_creation_sql(string_view sql) {
    string str;
    str = sql;
    tables_creation_sql.push_back(str);
}


time_t DataBase::string_to_time_t(string_view str) {
    string sql = "SELECT strftime('%s'," + to_sql_string(str) + ");";
    time_t result;
    execute_sql(sql, "[DataBase] Retrieve time_t succeeded",
                [](string_view error_msg) -> bool {
                    cerr<<"SQL error: %s\n"<< error_msg<<endl;
                    throw Exceptions::DataBaseRetrievingError("Time_T", "str");
                },
                [&result](const string_map& map) mutable -> bool {
                    result =  stoi(map.begin()->second);
                    return true;
                });
    return result;
}

vector<string_map> DataBase::get_all_by_feature(string_view table_name, const string_pair &feature) {
    string sql = "select * from ";
    sql += table_name;
    sql += " where " + feature.first + "=" + feature.second;
    vector<string_map> result;
    execute_sql(sql, "[DataBase] Retrieve many succeeded",
                [&](string_view error_msg) -> bool {
                    cerr<<"[DataBase] SQL error: %s\n"<< error_msg<<endl;
                    throw Exceptions::DataBaseRetrievingError(table_name, feature.first, feature.second);
                },
                [&result](const string_map& map) mutable -> bool {
                    result.push_back(map);
                    return true;
                });

    return result;
}


vector<string_map> DataBase::get_all(string_view table_name) {
    string sql = "select * from ";
    sql += table_name;
    vector<string_map> result;
    execute_sql(sql, "[DataBase] Retrieve many succeeded",
                [&](string_view error_msg) -> bool {
                    cerr<<"SQL error: %s\n"<< error_msg<<endl;
                    throw Exceptions::DataBaseRetrievingError(table_name);
                },
                [&result](const string_map& map) mutable -> bool {
                    result.push_back(map);
                    return true;
                });

    return result;
}

void DataBase::delete_by_feature(string_view table_name, const string_pair &feature) {
    string sql = "delete from ";
    sql += table_name;
    sql += " where " + feature.first + "=" + feature.second;
    execute_sql(
            sql,
            "[DataBase] Delete succeeded",
            [&](string_view error_msg) -> bool {
                cerr<<"SQL error: %s\n"<< error_msg<<endl;
                throw Exceptions::DataBaseRetrievingError(table_name);
            });

}


string DataBase::to_sql_string(string_view s) {
    string result = "\"";
    result += s;
    result += "\"";
    return result;
}

string DataBase::to_sql_date_time(time_t t) {
    string result = "datetime(";
    result += to_string(t);
    result += ", 'unixepoch')";
    //strftime('%s',time)
    return result;
}

