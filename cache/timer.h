//
// Created by guangcan on 2020/7/20.
//

#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <mutex>
#include <functional>

namespace hicache {
#define PERIOD_TIME     50

class Timer {
public:
    Timer(std::function<void()> task, int interval)
    :task_(task), interval_(interval), /*expired_(true), */is_stop_(false){
        StartTimer();
    }
    ~Timer() {}

public:
    void Expire(){
//        if(expired_) { return;}

        is_stop_ = true;
        if (th_timer_.joinable()) {
            th_timer_.join();
        }
//        {
//            std::unique_lock<std::mutex> lock(mutex_);
////            expired_cond_.wait(lock, [this](){
////                return expired_ = true;
////            });
////            expired_cond_.wait(lock, false);
//            int a = 1;
//        }
    }
private:
    void StartTimer() {
        std::cout << "StartTime"  << std::endl;

//        expired_ = false;
//        std::thread th(&Cache::TheadCheck, this);

//        th_ = std::move(th);
//        th_.detach();
        std::thread th([this](){
            int total_interval = 0;
            std::cout << "start task111" << total_interval << std::endl;

            while (!is_stop_) {
                if (total_interval - interval_ > 0) {
                    total_interval = 0;
                    // to do task
                    std::cout << "start task" << total_interval << std::endl;
                    task_();
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(PERIOD_TIME));
                total_interval += PERIOD_TIME;
            }
            // stop
//            {
            std::cout << "to sleep 20s" << std::endl;

//                std::this_thread::sleep_for(std::chrono::seconds (20));
            std::cout << "to sleep 20s finish" << std::endl;

//
//                std::lock_guard<std::mutex> lock(mutex_);
//                expired_ = true;
//                expired_cond_.notify_one();
//            }
        });
//        th.detach();
        th_timer_ = std::move(th);
    }

private:
//    std::atomic<bool> expired_;
    std::atomic<bool> is_stop_;
//    std::mutex mutex_;
//    std::condition_variable expired_cond_;
    int interval_; // ms
    std::function<void()> task_;
    std::thread th_timer_;


};
}



#endif //UNTITLED_CACHE_H
