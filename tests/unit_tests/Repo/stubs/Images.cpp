//
// Created by alro on 3/20/20.
//

#include "Images.h"

unique_ptr<Image> Unit_testing::Images::get_image_1() {
    auto multimedia = make_unique<Multimedia>(1, "image1.png", 1400, "image/png");
    auto image = make_unique<Image>(1, "1080:720", move(multimedia));
    return image;
}

unique_ptr<Image> Unit_testing::Images::get_image_2() {
    auto multimedia = make_unique<Multimedia>(2, "image2.jpg", 2000, "image/jpeg");
    auto image = make_unique<Image>(2, "1920:1080", move(multimedia));
    return image;
}

unique_ptr<Image> Unit_testing::Images::get_image_3() {
    auto multimedia = make_unique<Multimedia>(3, "image3.png", 4000, "image/png");
    auto image = make_unique<Image>(3, "3840:2160", move(multimedia));
    return image;
}

void Unit_testing::Images::seed_db_with_images(const shared_ptr<DependencyInjector> &di) {
    auto repo = di->get_image_repo(di);
    Image::install_repo(repo);
    get_image_1()->save();
    get_image_2()->save();
    get_image_3()->save();

}





