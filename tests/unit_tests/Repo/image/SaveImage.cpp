//
// Created by alro on 29‏/11‏/2020.
//

#include <Entity/DependencyInjector.h>
#include "gtest/gtest.h"
#include "../tools/Database.h"
#include "../stubs/Images.h"
using namespace std;

TEST(image_creation, create_valid_image){
    string fileName = "testdata.db";
    ASSERT_EQ(Unit_testing::Database::drop_database(fileName), true);
    shared_ptr<DependencyInjector> di = make_shared<DependencyInjector> ();
    di->install_data_base(fileName);
    di->install_multimedia_repo(di);
    di->install_image_repo(di);
    ASSERT_EQ( Unit_testing::Database::init_database(di), true);
    auto image_repo = di->get_image_repo(di);
    Image::installRepo(image_repo);
    auto image = Unit_testing::Images::get_image_1();
    bool res = image->save();
    ASSERT_EQ(res, true);

}



