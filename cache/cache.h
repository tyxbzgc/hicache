//
// Created by guangcan on 2020/7/20.
//

#ifndef UNTITLED_CACHE_H
#define UNTITLED_CACHE_H

#include <iostream>
#include <unordered_map>
#include <mutex>
#include <future>
#include <memory>

#include "timer.h"

namespace hicache {
    typedef std::function<void()> CallBack;

#define EXPIRATION_DEFAULT  0
#define EXPIRATION_NO       -1

template<typename Object>
struct Item {
    Object val;
    long long expiration;
};


    enum ErrCode {
        OK,
        KEY_ALREADY_EXIST,
        KEY_NOT_EXIST,


    };

    long long GetCurrentSystemTime();

    template<typename Key, typename Object>
    class Cache {
    public:
//    Cache(int expiration, int clean_Interval);
//    virtual ~Cache();
        // 设置 有修改，无添加
//    int Set(std::string key, Object value, int expiration=0);
//    int SetDefault(std::string key, Object value);
//    // 添加
//    int Add(std::string key, Object value, int expiration=0);
//    // 替换
//    int Replace(std::string key, Object value, int expiration=0);
//    bool Get(std::string key, Object& value);
//    bool GetWithExpiration(std::string key, Object& value, long long& expiration_time);
//    void Delete(std::string key);
//    bool Exist(std::string key);
////    bool Expired();
//    void All(std::unordered_map<std::string, Item>& items);
//    void Flush();
//    int Count();
//    void Print();

//    void SetEvicted(CallBack func);
    public:
        Cache(int expiration, int cleanInterval) { Init(expiration, cleanInterval); }

        virtual ~Cache() { Stop(); }

        int Set(const Key &key, Object value, int expiration = 0) {
            Item<Object> item;
            if (EXPIRATION_DEFAULT == expiration) {
                expiration = default_expiration_;
            }
            if (expiration > 0) {
                item.expiration = GetCurrentSystemTime() + expiration;
            }
            item.val = value;

            std::lock_guard<std::mutex> lock(mutex_);
            items_[key] = item;

            return OK;
        }

        int SetDefault(const Key &key, Object value) {
            return Set(key, value, EXPIRATION_DEFAULT);
        }

        int Add(const Key &key, Object value, int expiration = 0) {
            if (Exist(key)) {
                return KEY_ALREADY_EXIST;
            }
            return Set(key, value, expiration);
        }

        int Replace(const Key &key, Object value, int expiration = 0) {
            if (!Exist(key)) {
                return KEY_NOT_EXIST;
            }

            return Set(key, value, expiration);
        }

        bool Get(const Key &key, Object &value) {
            std::lock_guard<std::mutex> lock(mutex_);
            auto itor = items_.find(key);
            if (itor == items_.end()) {
                return false;
            }
            if (itor->second.expiration > 0 &&
                GetCurrentSystemTime() > itor->second.expiration) {
                return false;
            }
            value = itor->second.val;

            return true;
        }

        bool GetWithExpiration(const Key &key, Object &value, long long &expiration_time) {
            std::lock_guard<std::mutex> lock(mutex_);
            auto itor = items_.find(key);
            if (itor == items_.end()) {
                return false;
            }
            if (itor->second.expiration > 0 &&
                GetCurrentSystemTime() > itor->second.expiration) {
                return false;
            }
            value = itor->second.val;
            expiration_time = itor->second.expiration;

            return true;
        }

        void Delete(const Key &key) {
            std::lock_guard<std::mutex> lock(mutex_);
            auto itor = items_.find(key);
            if (itor == items_.end()) {
                return;
            }
            items_.erase(itor);
            // todo
            if (0) {
                func_(); // 回调，让使用方进行处理。
            }

        }

        bool Exist(const Key &key) {
            std::lock_guard<std::mutex> lock(mutex_);
            auto itor = items_.find(key);
            if (itor == items_.end()) {
                return false;
            }
            if (itor->second.expiration > 0 &&
                GetCurrentSystemTime() > itor->second.expiration) {
                return false;
            }

            return true;
        }

        void All(std::unordered_map<Key, Item<Object>> &items) {
            std::lock_guard<std::mutex> lock(mutex_);
            long long now = GetCurrentSystemTime();
            for (auto &item : items_) {
                if (item.second.expiration > 0 && now > item.second.expiration) {
                    continue;
                }
                items.emplace(item);
            }
        }

        void Flush() {
            std::lock_guard<std::mutex> lock(mutex_);
            items_.clear();
        }

        int Count() {
            std::lock_guard<std::mutex> lock(mutex_);
            return items_.size();
        }

        void SetEvicted(CallBack func) {}

        void Print() {
            std::lock_guard<std::mutex> lock(mutex_);
            for (auto &itor : items_) {
                std::cout << "k:" << itor.first << "  v:" << itor.second.val << "  t:" << itor.second.expiration
                          << std::endl;
            }
        }

    private:
        void Init(int expiration, int cleaInterval) {
            if (EXPIRATION_DEFAULT == expiration) {
                expiration = EXPIRATION_NO;
            }
            default_expiration_ = expiration;
            items_.clear();

            auto f = [this]() { DeleteExpired(); };
            tt = std::make_shared<Timer>(f, cleaInterval);
        }

        void Stop() {
            std::cout << "~Cache start" << std::endl;
            if (tt) {
                tt->Expire();
                std::cout << "tt->Expire() finish" << std::endl;

            }
            std::cout << "~Cache finish" << std::endl;
        }

        void DeleteExpired() {
            long long now = GetCurrentSystemTime();
            std::lock_guard<std::mutex> lock(mutex_);
            for (auto itor = items_.begin(); itor != items_.end();) {
                if (itor->second.expiration > 0 && now > itor->second.expiration) {
                    items_.erase(itor++);
                } else {
                    ++itor;
                }
            }

            // todo 后期释放问题
        }

    private:
        int default_expiration_;
        int clean_Interval_;
        std::unordered_map<Key, Item<Object>> items_;
        std::mutex mutex_;
        CallBack func_;
        bool is_stop_;
        std::thread th_;
        std::shared_ptr<Timer> tt;
    };


}


#endif //UNTITLED_CACHE_H
