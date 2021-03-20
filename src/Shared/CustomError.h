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

    struct C_ANT_ACTIVATE_FOREIGN_KEY : public std::exception {
        [[nodiscard]] const char *what() const noexcept override {
            return "Can't open database";
        }
    };

    struct C_ANT_OPEN_DB : public std::exception {
        [[nodiscard]] const char *what() const noexcept override {
            return "Can't open database";
        }
    };

    struct C_ANT_START_TRANSACTION : public std::exception {
        [[nodiscard]] const char *what() const noexcept override {
            return "Can't start database transaction";
        }
    };

    struct C_ANT_END_TRANSACTION : public std::exception {
        [[nodiscard]] const char *what() const noexcept override {
            return "Can't end database transaction";
        }
    };


    class DB_ERROR : public std::exception {
    private:
        std::string message;
    public:
        explicit DB_ERROR(std::string_view message) : message(std::string("[DATABASE] Error message <") + message.data()) {}

        [[nodiscard]] const char *what() const noexcept override {
            return message.c_str();
        }
    };


    struct C_ANT_CREATE_TABLE : public std::exception {
        [[nodiscard]] const char *what() const noexcept override {
            return "Can't create table";
        }
    };

    class DataBaseInsertIntoTableError : public std::exception {
    private:
        std::string message;

    public:
        [[nodiscard]] const char* what() const noexcept override {
            return message.data();
        }
        DataBaseInsertIntoTableError(std::string_view tableName, std::string_view message)
         {
            this->message = std::string(
                    "[DataBase]  INSERT ERROR INTO {table: ") + tableName.data() + "} " +
                            "error_message <" +  message.data() + ">";
         }

    };

    class DataBaseDeleteFromTableError : public std::exception {
    private:
        std::string message;
        const char * msg;


    public:
        [[nodiscard]] const char* what() const noexcept override {
            return msg;
        }
        DataBaseDeleteFromTableError(std::string_view tableName, std::string_view id ,std::string_view message)
        {
            this->message = std::string(
                    "[DataBase]  DELETE ERROR FROM {table: ") + tableName.data() + ", id:"+ id.data() + "} " +
                            "error_message <" +  message.data() + ">";
            this->msg = this->message.c_str();
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
