#include <iostream>
#include "cache/cache.h"
int main() {
//    std::cout << "run" << std::endl;
//    hicache::Cache<std::string, int>* ca = new hicache::Cache<std::string, int>(1000, 2000);
//    ca->Set("a", 1);
//    ca->Set("b", 2);
//    ca->Print();
//    std::cout << "Hello, World!" << std::endl;
    long long tt = hicache::GetCurrentSystemTime();
    hicache::Cache<std::string, int>* ca = new hicache::Cache<std::string, int>(1000, 2000);
    ca->Add("a", 1, 0);
    ca->Set("a", 1, 0);
    for (int i = 0; i < 100000 ; ++i) {
        ca->Add(std::string("asdfasdfasdfasdfasd" )+ std::to_string(i).c_str() , i, 5000);
    }
    ca->Add("b", 1, 6000);

    std::this_thread::sleep_for(std::chrono::seconds (1));
    long long tt_end = hicache::GetCurrentSystemTime();

//  ca->Print();
    std::cout << "#####Get() GetWithExpiration()#####" << std::endl;
    ca->Replace("b", 22, 7000);

    std::cout << "#####Get() GetWithExpiration()#####" << std::endl;
    {
        int val;
        bool status = ca->Get("b", val);
        std::cout << "Get(), status:" << status << ", val:" << val << std::endl;
        long long t;
        status = ca->GetWithExpiration("b", val, t);
        std::cout << "GetWithExpiration(), status:" << status << ", val:" << val << ", time:" << t << std::endl;
    }

    std::cout << "#####Delete()#####" << std::endl;
    ca->Delete("b");

    std::cout << "#####Exist()#####" << std::endl;
    std::cout << "exist:" << ca->Exist("b") << std::endl;

    std::cout << "#####Flush()#####" << std::endl;
    ca->Flush();
    std::cout << "#####Count()#####" << std::endl;
    std::cout << "size:" << ca->Count() << std::endl;
    std::cout << "#####All()#####" << std::endl;

    std::unordered_map<std::string, hicache::Item<int>> items;

    ca->All(items);
    for( auto& it : items) {
        std::cout << it.first.c_str() << ":" << it.second.val << std::endl;
    }
    delete ca;
    std::cout << "ms" << tt_end - tt << std::endl;
    return 1;
//    int n1=2,n2=10;
//
//    double d1=1.5,d2=5.6;
//    std::vector<int> a,c;
//
//    a.push_back(1);
//    c.push_back(1);
//
//    std::cout<< "较小整数:"<<min(n1,n2)<<std::endl;
//
//    std::cout<< "较小实数:"<<min("ssdfsdf","lllllllll")<<std::endl;
//

    return 0;
    return 0;
}
