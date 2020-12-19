//
// Created by alro on 3/17/20.
//

#ifndef SMART_AD_SGA_TESTS_DATABASE_H
#define SMART_AD_SGA_TESTS_DATABASE_H

#include <string_view>
#include <memory>
#include <Entity/DependencyInjector.h>

using namespace std;
namespace Unit_testing{
    class Database {



    public:

        static bool drop_database(string_view db_file_name);
        static bool init_database(const shared_ptr<DependencyInjector> &di);
        static bool seed_database(const shared_ptr<DependencyInjector>& di);
    };
}



#endif //SMART_AD_SGA_TESTS_DATABASE_H
