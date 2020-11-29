//
// Created by alro on 21‏/11‏/2020.
//

#ifndef MYPROJECT_CUSTOMERROR_H
#define MYPROJECT_CUSTOMERROR_H

#include <stdexcept>
#include <exception>

class NotImplementedException : public std::logic_error
{
public:
    NotImplementedException () : std::logic_error{"Function not yet implemented."} {}
};



namespace Repo::Exceptions{
    struct DB_NAME_NOT_SET : public std::exception {
        [[nodiscard]] const char *what() const noexcept override {
            return "db_path is not settled yet";
        }
    };
    struct C_ANT_OPEN_DB : public std::exception {
        [[nodiscard]] const char *what() const noexcept override {
            return "Can't open database";
        }
    };
    class DataBaseRetrievingError : public std::exception {

    private:
        std::string tableName;
        const char * msg;
        [[nodiscard]] const char* what() const noexcept override {
            return msg;
        }

    public:
        DataBaseRetrievingError(std::string_view tableName, std::string_view id){
            this-> tableName = tableName;
            msg = ("[DataBase]  retrieving by id error {table: " + this->tableName + ", id: " + id.data() + "}").c_str();
        }
        DataBaseRetrievingError(std::string_view tableName,std::string_view feature, std::string_view feature_value){
            this-> tableName = tableName;
            msg = ("[DataBase]  retrieving many error {table: " + this->tableName + ", feature: " + feature.data() +
                    ", feature_value: " + feature_value.data() + "}").c_str();
        }
        DataBaseRetrievingError() {
            msg = "[DataBase]  retrieving error ";
        }
        explicit DataBaseRetrievingError(std::string_view tableName) {
            this->tableName = tableName;
            msg = ("[DataBase]  retrieving all error {table: " + this->tableName + "}").c_str();
        }


    };
    
    
}

#endif //MYPROJECT_CUSTOMERROR_H
