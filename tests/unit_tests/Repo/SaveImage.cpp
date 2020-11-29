//
// Created by alro on 29‏/11‏/2020.
//

#include <Shared/DependencyInjector.h>
#include "gtest/gtest.h"
#include "tools/Database.h"
#include "stubs/Images.h"
using namespace std;
using namespace Unit_testing;
TEST(image_creation, create_valid_image){
    string fileName = "testdata.db";
    ASSERT_EQ(Database::drop_database(fileName), true);
    shared_ptr<DependencyInjector> di = make_shared<DependencyInjector> ();
    di->install_data_base(fileName);
    di->install_multimedia_repo(di);
    di->install_image_repo(di);
    ASSERT_EQ( Database::init_database(di), true);
    auto image_repo = di->get_image_repo(di);
    auto image = Images::get_image_1();
    bool res = image_repo->save(*image);
    ASSERT_EQ(res, true);

};