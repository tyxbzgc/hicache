//
// Created by guangcan on 2020/7/20.
//

#include "cache.h"
#include <future>
#include <chrono>

namespace hicache {

long long GetCurrentSystemTime()
{
    auto t = std::chrono::system_clock::now();
    auto millsecond = std::chrono::duration_cast<std::chrono::milliseconds>(t.time_since_epoch());
    return millsecond.count();
}

//Cache::Cache(int expiration, int clean_Interval)
//{
//    if (EXPIRATION_DEFAULT == expiration) {
//        expiration = EXPIRATION_NO;
//    }
//    default_expiration_ = expiration;
//    items_.clear();
//
//    auto f = [this](){DeleteExpired();};
//    tt = std::make_shared<Timer>(f, clean_Interval);
//}
//Cache::~Cache()
//{
//    Stop();
//}

//int Cache::Add(std::string key, Object value, int expiration/*=0*/)
//{
//    if (Exist(key)) {
//        return KEY_ALREADY_EXIST;
//    }
//
//    return Set(key, value, expiration);
//}
//int Cache::Set(std::string key, Object value, int expiration/*=0*/)
//{
//    Item< int> item;
//    if (EXPIRATION_DEFAULT == expiration) {
//        expiration = default_expiration_;
//    }
//    if (expiration > 0) {
//        item.expiration = GetCurrentSystemTime() + expiration;
//    }
//    item.val = value;
//
//    std::lock_guard<std::mutex> lock(mutex_);
//    items_[key] = item;
//
//    return OK;
//}
#if 0
int Cache::SetDefault(std::string key, Object value)
{
    return Set(key, value, EXPIRATION_DEFAULT);
}

void Cache::Delete(std::string key)
{
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

void Cache::SetEvicted(CallBack func)
{
     func_ = std::move(func);
}

int Cache::Replace(std::string key, Object value, int expiration/*=0*/)
{
    if (!Exist(key)) {
      return KEY_NOT_EXIST;
    }

    return Set(key, value, expiration);
}
#endif
//bool Cache::Get(std::string key, Object& value) {
//    std::lock_guard<std::mutex> lock(mutex_);
//    auto itor = items_.find(key);
//    if (itor == items_.end()) {
//        return false;
//    }
//    if (itor->second.expiration > 0 &&
//        GetCurrentSystemTime() > itor->second.expiration) {
//        return false;
//    }
//    value = itor->second.val;
//
//    return true;
//}
#if 0
bool Cache::GetWithExpiration(std::string key, Object& value, long long& expiration_time)
{
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

bool Cache::Exist(std::string key)
{
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

int Cache::Count()
{
    std::lock_guard<std::mutex> lock(mutex_);
    return items_.size();
}

void Cache::All(std::unordered_map<std::string, Item>& items)
{
    std::lock_guard<std::mutex> lock(mutex_);
    long long now = GetCurrentSystemTime();
    for (auto& item : items_) {
        if (item.second.expiration > 0 && now > item.second.expiration) {
            continue;
        }
        items.emplace(item);
    }
}

void Cache::Flush()
{
    std::lock_guard<std::mutex> lock(mutex_);
    items_.clear();
}

void Cache::Stop()
{
    std::cout << "~Cache start" << std::endl;
    if (tt){
        tt->Expire();
        std::cout << "tt->Expire() finish" << std::endl;

    }
    std::cout << "~Cache finish" << std::endl;
}

void Cache::DeleteExpired()
{
    long long now = GetCurrentSystemTime();
    std::lock_guard<std::mutex> lock(mutex_);
    for (auto itor = items_.begin(); itor != items_.end(); ) {
        if (itor->second.expiration > 0 && now > itor->second.expiration) {
            items_.erase(itor++);
        }
        else {
            ++itor;
        }
    }

  // todo 后期释放问题
}
#endif
//template <typename T>
//void Cache<T>::Print()
//{
//  std::lock_guard<std::mutex> lock(mutex_);
//  for (auto& itor : items_) {
//      std::cout << "k:" << itor.first << "  v:" << itor.second.val << "  t:" << itor.second.expiration << std::endl;
//  }
//}

}