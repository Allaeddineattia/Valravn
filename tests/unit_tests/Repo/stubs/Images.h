//
// Created by alro on 3/20/20.
//

#ifndef SMART_AD_SGA_TESTS_IMAGES_H
#define SMART_AD_SGA_TESTS_IMAGES_H

#include <Entity/Image.h>
#include <memory>
#include <Shared/DependencyInjector.h>

using namespace std;
namespace Unit_testing {
    class Images {
    public:
        static unique_ptr<Image> get_image_1();
        static unique_ptr<Image> get_image_2();
        static unique_ptr<Image> get_image_3();
        static bool seed_db_with_images(const shared_ptr<DependencyInjector>& di);

    };
}

#endif //SMART_AD_SGA_TESTS_IMAGES_H
