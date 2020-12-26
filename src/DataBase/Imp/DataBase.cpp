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

bool DataBase::InitDb() {
    IsDbInitialised = activate_foreign_keys();
    for (auto &i: tables_creation_sql) {
        if (!IsDbInitialised) break;
        IsDbInitialised = IsDbInitialised && CreateTableFromSql(i);
    }
    return IsDbInitialised;
}

string_view DataBase::GetDbPath () {
    return DbPath;
}


DataBase::~DataBase() {
    sqlite3_close(reinterpret_cast<sqlite3 *>(db.get()));
    cout << "[DataBase] Database destructor have been called" << endl;
}


bool DataBase::ExecuteSql(
        string_view sql,
        string_view SuccessMsg = "[DataBase] OPERATION_SUCCEEDED",
        const function<bool(string_view error_msg)> &do_if_error =
        [](string_view error_msg) -> bool {
            cout << "[DataBase] SQL error: " << error_msg << endl;
            return false;
        },
        const function<bool (const string_map&)>& callback = nullptr ) {
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
        bool result = do_if_error(zErrMsg);
        sqlite3_free(zErrMsg);
        return result;
    } else {
        cout << SuccessMsg << endl;
        return true;
    }
}

string_map DataBase::GetById(string_view TableName, string_view id) {
    string sql = "select * from ";
    sql += TableName;
    sql += " where ID=";
    sql += id;
    string_map result;
    ExecuteSql(sql, "[DataBase] Retrieve By id succeeded",
                [&](string_view ErrorMsg) -> bool {
                    throw Exceptions::DataBaseRetrievingError(TableName, id);
                },
                [&result](const string_map& map) mutable -> bool {
                    result = map;
                    return true;
                });

    return  result;

}


bool DataBase::CreateTableFromSql(string_view sql) {

    return ExecuteSql(sql, "[DataBase] Table created successfully\n",
                       [](string_view ErrorMsg) -> bool {
                        cerr << "[DataBase] QL error: " << ErrorMsg << endl;
                        return ErrorMsg.find("table") != std::string::npos
                               &&
                               ErrorMsg.find("already exists") != std::string::npos;
                        });

}

string DataBase::GetInsertSql(string_view TableName, const string_map &map) const {
    string sql1 = "insert into ";
    sql1 += TableName;
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

bool DataBase::InsertIntoTable(string_view TableName, const string_map &map) {

    string sql = GetInsertSql(TableName, map);
    return ExecuteSql(sql, "[DataBase] Row inserted successfully");

}


string DataBase::GetUpdateSql(string_view TableName, const string_pair &feature, const string_map &map) {
    string sql = "UPDATE ";
    sql += TableName;
    sql += " SET";
    for (auto &itr : map) {
        sql += " " + itr.first + " = " + itr.second + ",";
    }
    sql.resize(sql.size() - 1);
    sql += " WHERE " + feature.first + " = " + feature.second;
    return sql;
}

bool DataBase::UpdateIntoTable(string_view TableName, const string_pair &SelectFeature, const string_map &map) {
    string sql = GetUpdateSql(TableName, SelectFeature, map);
    return ExecuteSql(sql, "[DataBase] Row updated successfully");
}

bool DataBase::ActivateForeignKeys() {

    string sql = "PRAGMA foreign_keys=on;";
    return ExecuteSql(sql, "[DataBase] Foreign keys activated");

}

bool DataBase::BeginTransaction() {
    string sql = "BEGIN TRANSACTION;";
    return ExecuteSql(sql, "[DataBase] Transaction started");

}

bool DataBase::EndTransaction() {
    string sql = "END TRANSACTION;";
    return ExecuteSql(sql, "[DataBase] Transaction ended");

}

void DataBase::AddTableCreationSql(string_view sql) {
    string str;
    str = sql;
    tables_creation_sql.push_back(str);
}


time_t DataBase::StringToTimeT(string_view str) {
    string sql = "SELECT strftime('%s'," + ToSqlString(str) + ");";
    time_t result;
    ExecuteSql(sql, "[DataBase] Retrieve time_t succeeded",
                [](string_view ErrorMsg) -> bool {
                    cerr<<"SQL error: %s\n"<< ErrorMsg<<endl;
                    throw Exceptions::DataBaseRetrievingError("Time_T", "str");
                },
                [&result](const string_map& map) mutable -> bool {
                    result =  stoi(map.begin()->second);
                    return true;
                });
    return result;
}

vector<string_map> DataBase::GetAllByFeature(string_view TableName, const string_pair &feature) {
    string sql = "select * from ";
    sql += TableName;
    sql += " where " + feature.first + "=" + feature.second;
    vector<string_map> result;
    ExecuteSql(sql, "[DataBase] Retrieve many succeeded",
                [&](string_view ErrorMsg) -> bool {
                    cerr<<"[DataBase] SQL error: %s\n"<< ErrorMsg<<endl;
                    throw Exceptions::DataBaseRetrievingError(TableName, feature.first, feature.second);
                },
                [&result](const string_map& map) mutable -> bool {
                    result.push_back(map);
                    return true;
                });

    return result;
}


vector<string_map> DataBase::GetAll(string_view TableName) {
    string sql = "select * from ";
    sql += TableName;
    vector<string_map> result;
    ExecuteSql(sql, "[DataBase] Retrieve many succeeded",
                [&](string_view ErrorMsg) -> bool {
                    cerr<<"SQL error: %s\n"<< ErrorMsg<<endl;
                    throw Exceptions::DataBaseRetrievingError(TableName);
                },
                [&result](const string_map& map) mutable -> bool {
                    result.push_back(map);
                    return true;
                });

    return result;
}

bool DataBase::DeleteByFeature(string_view TableName, const string_pair &feature) {
    string sql = "delete from ";
    sql += TableName;
    sql += " where " + feature.first + "=" + feature.second;
    return ExecuteSql(sql, "[DataBase] Delete succeeded");

}


string DataBase::ToSqlString(string_view s) {
    string result = "\"";
    result += s;
    result += "\"";
    return result;
}

string DataBase::ToSqlDateTime(time_t t) {
    string result = "datetime(";
    result += to_string(t);
    result += ", 'unixepoch')";
    //strftime('%s',time)
    return result;
}
