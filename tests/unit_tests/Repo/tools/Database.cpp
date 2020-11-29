//
// Created by alro on 3/17/20.
//

#include <unistd.h>
#include "Database.h"
#include <iostream>
#include "../stubs/Images.h"


bool Unit_testing::Database::drop_database(string_view db_file_name) {
    if (access( db_file_name.data(), F_OK ) != -1)
        return remove(db_file_name.data()) == 0;
    return true;
}

bool Unit_testing::Database::init_database(const shared_ptr<DependencyInjector> &di) {
    auto db = di->get_data_base(di);
    return db->init_db();
}

bool Unit_testing::Database::seed_database(const shared_ptr<DependencyInjector>& di) {

    return Unit_testing::Images::seed_db_with_images(di);

}
