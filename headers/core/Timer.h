//
// Created by alro on 6‏/12‏/2020.
//

#ifndef VALRAVEN_TIMER_H
#define VALRAVEN_TIMER_H

#include <iostream>
#include <thread>
#include <chrono>
#include <memory>

using namespace std;
template <typename Functor>

class Timer {

    bool clear = false;
    std::unique_ptr<std::thread> task = nullptr;
    bool joined = false;
    int index = 0;

public:

    static int count;
    Timer() {
        index = ++count;
    }
    void setTimeout(Functor function, long delay_ms){
        this->clear = false;
        task = std::make_unique<std::thread> ([=]() {
            cout<<"[Time Out Timer] "<< this->index<<" before: "<<delay_ms<<endl;
            if(this->clear) return;
            std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
            cout<<"[Time Out Timer] "<< this->index<<" after: "<<delay_ms<<endl;
            if(this->clear) return;
            cout<<"[Time Out Timer] "<< this->index<<" before calling : "<<this->clear<<delay_ms<<endl;
            function();
            cout<<"[Time Out Timer] "<< this->index<<" after calling : "<<delay_ms<<endl;
        });

    };

    void setAlarm(Functor function, time_t t){
        this->clear = false;
        auto time_point = chrono::system_clock::from_time_t(t);
        auto time_point1 = chrono::system_clock::now();
        task = std::make_unique<std::thread> ([=]() {
            if(this->clear) return;
            std::this_thread::sleep_until(time_point);
            if(this->clear) return;
            function();
        });

    }

    void setInterval(Functor function, long interval){
        this->clear = false;
        std::thread t([=]() {
            while(true) {
                if(this->clear) return;
                std::this_thread::sleep_for(std::chrono::milliseconds(interval));
                if(this->clear) return;
                function();
            }
        });
        t.detach();
    };
    void stop(){
        this->clear = true;
        cout<<"stopped"<<endl;
    };

    bool join(){
        if (joined) return false;
        if(task != nullptr && task->joinable()){
            joined  = true;
            task->join();
            return true;
        }
        return false;

    }

    bool detach(){
        if(joined)
            return false;
        std::cout<<"[TIMER DETACH]"<<std::endl;
        if(task != nullptr && task->joinable() ){
            joined = true;
            std::cout<<"[TIMER DETACH] JOINABLE"<<std::endl;
            task->detach();
            return true;
        }
        std::cout<<"[TIMER DETACH]"<<std::endl;
        return true;
    }

};
template<class T> int Timer<T>::count = 0;

#endif //VALRAVEN_TIMER_H
