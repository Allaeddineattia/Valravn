//
// Created by alro on 29‏/11‏/2020.
//

#include <core/DependencyInjector.h>
#include <core/Tools.h>
#include <image/Image.h>
#include "gtest/gtest.h"
#include "../tools/Database.h"
#include "../stubs/Images.h"
using namespace std;

TEST(image_deleting, delete_saved_image){
    string fileName = "testdata.db";
    ASSERT_EQ(Unit_testing::Database::drop_database(fileName), true);
    shared_ptr<DependencyInjector> di = make_shared<DependencyInjector> ();
    di->install_data_base(fileName);
    di->install_multimedia_repo(di);
    di->install_image_repo(di);

    ASSERT_EQ( Unit_testing::Database::init_database(di), true);
    Unit_testing::Images::seed_db_with_images(di);
    auto image_repo = di->get_image_repo(di);
    Image::install_repo(image_repo);
    auto image = Unit_testing::Images::get_image_1();
    image->remove();
    auto res = Image::fetch_by_id(image->get_id());
    ASSERT_EQ(res.has_value(), false);
    vector<unique_ptr<Image>> images;
    images.push_back(Unit_testing::Images::get_image_2());
    images.push_back(Unit_testing::Images::get_image_3());

    auto images_res = Image::get_all();
    //bool equality = std::equal(images_res.begin(), images_res.end(), images.begin(), Tools::unique_ptr_vec_comparator<Image>);
    //ASSERT_EQ( equality, true);
};