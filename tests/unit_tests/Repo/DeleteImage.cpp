//
// Created by alro on 29‏/11‏/2020.
//

#include <Shared/DependencyInjector.h>
#include <Shared/Tools.h>
#include "gtest/gtest.h"
#include "tools/Database.h"
#include "stubs/Images.h"
using namespace std;
using namespace Unit_testing;

TEST(image_deleting, delete_saved_image){
    string fileName = "testdata.db";
    ASSERT_EQ(Database::drop_database(fileName), true);
    shared_ptr<DependencyInjector> di = make_shared<DependencyInjector> ();
    di->install_data_base(fileName);
    di->install_multimedia_repo(di);
    di->install_image_repo(di);
    ASSERT_EQ( Database::init_database(di), true);
    ASSERT_EQ( Images::seed_db_with_images(di), true);
    auto image_repo = di->get_image_repo(di);

    auto image = Images::get_image_1();
    ASSERT_EQ( image_repo->delete_by_id(image->getId()), true);
    auto res = image_repo->get_by_id(image->getId());
    ASSERT_EQ(res.has_value(), false);
    vector<unique_ptr<Image>> images;
    images.push_back(Images::get_image_2());
    images.push_back(Images::get_image_3());

    auto images_res = image_repo->get_all();
    bool equality = std::equal(images_res.begin(), images_res.end(), images.begin(), Tools::unique_ptr_vec_comparator<Image>);
    ASSERT_EQ( equality, true);
};