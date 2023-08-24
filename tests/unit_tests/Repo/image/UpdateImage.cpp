//
// Created by alro on 29‏/11‏/2020.
//

#include <core/DependencyInjector.h>
#include "gtest/gtest.h"
#include "../tools/Database.h"
#include "../stubs/Images.h"
using namespace std;
using namespace Unit_testing;

TEST(image_updating, update_path){
    string fileName = "testdata.db";
    ASSERT_EQ(Database::drop_database(fileName), true);
    shared_ptr<DependencyInjector> di = make_shared<DependencyInjector> ();
    di->install_data_base(fileName);
    di->install_multimedia_repo(di);
    di->install_image_repo(di);
    ASSERT_EQ( Database::init_database(di), true);
    Images::seed_db_with_images(di);
    auto image_repo = di->get_image_repo(di);
    auto image = Images::get_image_1();

    string new_path = "never meant to belong ";
    auto updated_multimedia = make_unique<Multimedia>(image->get_multimedia().get_id(),
                                              new_path,
                                                      image->get_multimedia().getSize(),
                                                      image->get_multimedia().getMimeType());
    auto updated_image = make_unique<Image>(image->get_id(), image->get_resolution(), move(updated_multimedia));

    updated_image->save();

    auto res = Image::fetch_by_id(image->get_id());

    ASSERT_EQ(*(res.value()), *updated_image);

};

TEST(image_updating, update_size_image){
    string fileName = "testdata.db";
    ASSERT_EQ(Database::drop_database(fileName), true);
    shared_ptr<DependencyInjector> di = make_shared<DependencyInjector> ();
    di->install_data_base(fileName);
    di->install_multimedia_repo(di);
    di->install_image_repo(di);
    ASSERT_EQ( Database::init_database(di), true);
    Images::seed_db_with_images(di);
    auto image_repo = di->get_image_repo(di);
    Image::install_repo(image_repo);
    auto image = Images::get_image_1();

    unsigned int new_size = 4040;

    auto updated_multimedia = make_unique<Multimedia>(image->get_multimedia().get_id(),
                                                      image->get_multimedia().getPath(),
                                                      new_size,
                                                      image->get_multimedia().getMimeType());
    auto updated_image = make_unique<Image>(image->get_id(), image->get_resolution(), move(updated_multimedia));

    updated_image->save();

    auto res = Image::fetch_by_id(image->get_id());

    ASSERT_EQ(*(res.value()), *updated_image);

};

TEST(image_updating, update_mime_type){
    string fileName = "testdata.db";
    ASSERT_EQ(Database::drop_database(fileName), true);
    shared_ptr<DependencyInjector> di = make_shared<DependencyInjector> ();
    di->install_data_base(fileName);
    di->install_multimedia_repo(di);
    di->install_image_repo(di);
    ASSERT_EQ( Database::init_database(di), true);
    Images::seed_db_with_images(di);
    auto image_repo = di->get_image_repo(di);
    Image::install_repo(image_repo);
    auto image = Images::get_image_1();

    string new_mime_type = "new mime type";

    auto updated_multimedia = make_unique<Multimedia>(image->get_multimedia().get_id(),
                                                      image->get_multimedia().getPath(),
                                                      image->get_multimedia().getSize(),
                                                      new_mime_type);
    auto updated_image = make_unique<Image>(image->get_id(), image->get_resolution(), move(updated_multimedia));

    updated_image->save();

    auto res = Image::fetch_by_id(image->get_id());

    ASSERT_EQ(*(res.value()), *updated_image);

};

TEST(image_updating, update_many_fields_image){
    string fileName = "testdata.db";
    ASSERT_EQ(Database::drop_database(fileName), true);
    shared_ptr<DependencyInjector> di = make_shared<DependencyInjector> ();
    di->install_data_base(fileName);
    di->install_multimedia_repo(di);
    di->install_image_repo(di);
    ASSERT_EQ( Database::init_database(di), true);
    Images::seed_db_with_images(di);
    auto image_repo = di->get_image_repo(di);
    auto image = Images::get_image_1();

    string new_resolution = "999:999";

    string new_mime_type = "new mime type";

    unsigned int new_size = 4040;

    auto updated_multimedia = make_unique<Multimedia>(image->get_multimedia().get_id(),
                                                      image->get_multimedia().getPath(),
                                                      new_size,
                                                      new_mime_type);
    auto updated_image = make_unique<Image>(image->get_id(), new_resolution, move(updated_multimedia));

    updated_image->save();

    auto res = Image::fetch_by_id(image->get_id());

    ASSERT_EQ(*(res.value()), *updated_image);

};