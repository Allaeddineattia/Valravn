//
// Created by alro on 29‏/11‏/2020.
//

#include <Shared/DependencyInjector.h>
#include "gtest/gtest.h"
#include "tools/Database.h"
#include "stubs/Images.h"
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
    ASSERT_EQ( Images::seed_db_with_images(di), true);
    auto image_repo = di->get_image_repo(di);
    auto image = Images::get_image_1();

    string new_path = "never meant to belong ";
    auto updated_multimedia = make_unique<Multimedia>(image->getMultimedia().getId(),
                                              new_path,
                                              image->getMultimedia().getSize(),
                                              image->getMultimedia().getMimeType());
    auto updated_image = make_unique<Image>(image->getId(), image->getResolution(), move(updated_multimedia));

    ASSERT_EQ(image_repo->save(*updated_image), true);

    auto res = image_repo->get_by_id(image->getId());

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
    ASSERT_EQ( Images::seed_db_with_images(di), true);
    auto image_repo = di->get_image_repo(di);
    auto image = Images::get_image_1();

    unsigned int new_size = 4040;

    auto updated_multimedia = make_unique<Multimedia>(image->getMultimedia().getId(),
                                                      image->getMultimedia().getPath(),
                                                      new_size,
                                                      image->getMultimedia().getMimeType());
    auto updated_image = make_unique<Image>(image->getId(), image->getResolution(), move(updated_multimedia));

    ASSERT_EQ(image_repo->save(*updated_image), true);

    auto res = image_repo->get_by_id(image->getId());

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
    ASSERT_EQ( Images::seed_db_with_images(di), true);
    auto image_repo = di->get_image_repo(di);
    auto image = Images::get_image_1();

    string new_mime_type = "new mime type";

    auto updated_multimedia = make_unique<Multimedia>(image->getMultimedia().getId(),
                                                      image->getMultimedia().getPath(),
                                                      image->getMultimedia().getSize(),
                                                      new_mime_type);
    auto updated_image = make_unique<Image>(image->getId(), image->getResolution(), move(updated_multimedia));

    ASSERT_EQ(image_repo->save(*updated_image), true);

    auto res = image_repo->get_by_id(image->getId());

    ASSERT_EQ(*(res.value()), *updated_image);

};

TEST(image_updating, update_may_fields_image){
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

    string new_resolution = "999:999";

    string new_mime_type = "new mime type";

    unsigned int new_size = 4040;

    auto updated_multimedia = make_unique<Multimedia>(image->getMultimedia().getId(),
                                                      image->getMultimedia().getPath(),
                                                      new_size,
                                                      new_mime_type);
    auto updated_image = make_unique<Image>(image->getId(), new_resolution, move(updated_multimedia));

    ASSERT_EQ(image_repo->save(*updated_image), true);

    auto res = image_repo->get_by_id(image->getId());

    ASSERT_EQ(*(res.value()), *updated_image);

};