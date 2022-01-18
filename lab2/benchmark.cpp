#include <chrono>
#include <map>
#include <string>
#include <iostream>
#include "TAvl.hpp"
#include "TData.hpp"
#include "TAvlFinal.hpp"


int main(int argc, char** argv)
{
    std::chrono::time_point<std::chrono::system_clock> start, end;
    uint64_t time = 0;
	uint64_t map_time = 0;

    TAvl avl;
    std::map<std::string, uint64_t> map;

    for(uint64_t i = 0; i < 1000000; ++i)
    {
        std::string str = std::to_string(i);
        TData data(str.c_str());
        start = std::chrono::system_clock::now();
        map.insert(std::pair<std::string, uint64_t>(str, i));
        end = std::chrono::system_clock::now();
        map_time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        start = std::chrono::system_clock::now();
        avl.root_ = avl.InsertPrint(avl.root_, data, i, true);
        end = std::chrono::system_clock::now();
        time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }

    std::cout << "Insert map time: " << (double)map_time/1000000000 << " seconds\n";
    std::cout << "Insert avl time: " << (double)time/1000000000 << " seconds\n";

    time = 0;
    map_time = 0;

    for (int i = 0; i < 1000000; ++i)
    {
        start = std::chrono::system_clock::now();
        map.find(std::to_string(999999));
        end = std::chrono::system_clock::now();
        map_time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        start = std::chrono::system_clock::now();
        TData data(std::to_string(999999).c_str());
        TAvlNode* res = avl.Find(avl.root_, data);
        end = std::chrono::system_clock::now();
        time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }
    std::cout << "Find map time: " << (double)map_time/1000000000 << " seconds\n";
    std::cout << "Find avl time: " << (double)time/1000000000 << " seconds\n";

    time = 0;
    map_time = 0;

    for (int i = 0; i < 1000000; ++i)
    {
        start = std::chrono::system_clock::now();
        map.erase(std::to_string(999999-i));
        end = std::chrono::system_clock::now();
        map_time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        start = std::chrono::system_clock::now();
        TData data(std::to_string(999999-i).c_str());
        avl.root_ = avl.RemovePrint(avl.root_, data, true);
        end = std::chrono::system_clock::now();
        time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }

    std::cout << "Delete map time: " << (double)map_time/1000000000 << " seconds\n";
    std::cout << "Delete avl time: " << (double)time/1000000000 << " seconds\n";

	return 0;
}
