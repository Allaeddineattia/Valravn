//
// Created by rawaa on 22‏/3‏/2021.
//

#ifndef MYPROJECT_VIDEOS_H
#define MYPROJECT_VIDEOS_H

#include <Entity/Contract/Video.h>
#include <Shared/DependencyInjector.h>


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



#endif //MYPROJECT_VIDEOS_H
