//
// Created by rawaa on 22‏/3‏/2021.
//

#ifndef VALRAVEN_VIDEOS_H
#define VALRAVEN_VIDEOS_H

#include <video/Video.h>
#include <core/DependencyInjector.h>


using namespace std;
namespace Unit_testing {
    class Videos {
    public:
        static unique_ptr<Video> get_video_1();
        static unique_ptr<Video> get_video_2();
        static unique_ptr<Video> get_video_3();
        static void seed_db_with_videos(const shared_ptr<DependencyInjector>& di);

    };
}



#endif //VALRAVEN_VIDEOS_H
