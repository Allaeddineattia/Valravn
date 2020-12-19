//
// Created by alro on 29‏/11‏/2020.
//

#include <Entity/DependencyInjector.h>
#include <Shared/Tools.h>
#include <Entity/Image.h>
#include "gtest/gtest.h"
#include "tools/Database.h"
#include "stubs/Images.h"
using namespace std;

TEST(image_deleting, delete_saved_image){
    string fileName = "testdata.db";
    ASSERT_EQ(Unit_testing::Database::drop_database(fileName), true);
    shared_ptr<DependencyInjector> di = make_shared<DependencyInjector> ();
    di->install_data_base(fileName);
    di->install_multimedia_repo(di);
    di->install_image_repo(di);

    ASSERT_EQ( Unit_testing::Database::init_database(di), true);
    ASSERT_EQ( Unit_testing::Images::seed_db_with_images(di), true);
    auto image_repo = di->get_image_repo(di);
    Image::installRepo(image_repo);
    auto image = Unit_testing::Images::get_image_1();
    ASSERT_EQ( image->remove(), true);
    auto res = Image::fetchById(image->getId());
    ASSERT_EQ(res.has_value(), false);
    vector<unique_ptr<Image>> images;
    images.push_back(Unit_testing::Images::get_image_2());
    images.push_back(Unit_testing::Images::get_image_3());

    auto images_res = Image::getAll();
    bool equality = std::equal(images_res.begin(), images_res.end(), images.begin(), Tools::unique_ptr_vec_comparator<Image>);
    ASSERT_EQ( equality, true);
};