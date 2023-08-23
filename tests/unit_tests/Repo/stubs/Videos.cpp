//
// Created by rawaa on 22‏/3‏/2021.
//

#include "Videos.h"
unique_ptr<Video> Unit_testing::Videos::get_video_1() {
    auto multimedia = make_unique<Multimedia>(1, "image1.png", 1400, "image/png");
    auto video = make_unique<Video>(1,20,move(multimedia),"1080:720");
    return video;
}

unique_ptr<Video> Unit_testing::Videos::get_video_2() {
    auto multimedia = make_unique<Multimedia>(2, "image2.jpg", 2000, "image/jpeg");
    auto video = make_unique<Video>(2,30, move(multimedia),"1920:1080");
    return video;
}

unique_ptr<Video> Unit_testing::Videos::get_video_3() {
    auto multimedia = make_unique<Multimedia>(3, "image3.png", 4000, "image/png");
    auto video = make_unique<Video>(3, 40,move(multimedia),"3840:2160" );
    return video;
}

void Unit_testing::Videos::seed_db_with_videos(const shared_ptr<DependencyInjector> &di) {
    auto repo = di->get_video_repo(di);
    Video::install_repo(repo);
    get_video_1()->save();
    get_video_2()->save();
    get_video_3()->save();

}

