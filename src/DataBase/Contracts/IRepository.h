//
// Created by alro on 25‏/11‏/2020.
//

#ifndef MYPROJECT_IREPOSITORY_H
#define MYPROJECT_IREPOSITORY_H
#include <vector>
#include <Shared/CustomError.h>
#include <memory>
using namespace std;

template<class T>
class IRepository {
public:
    virtual bool save() = 0;
    virtual bool remove() = 0;
    static unique_ptr<T> fetch_by_id(int id){
        throw NotImplementedException();
    };
    static vector<unique_ptr<T>> get_all(){
        throw NotImplementedException();
    };


};



#endif //MYPROJECT_IREPOSITORY_H
