#include <iostream>
#include <string>
#include "structs.hpp"
#include "my_vector.hpp"
#include "radix_sort.hpp"

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    TVector<TPair> vec(10); 
    TUll val;
    size_t max_1 = 0;
    size_t max_2 = 0;
    size_t max_3 = 0;
    std::string key_0;
    std::string key_1;
    std::string key_2;
    size_t tmp_max_1 = 0;
    size_t tmp_max_2 = 0;
    size_t tmp_max_3 = 0;
    
    while(std::cin>>key_0>>key_1>>key_2>>val)
    {
        tmp_max_1 = key_0.c_str()[0] - 'A';
        tmp_max_2 = (100*(key_1.c_str()[0]-'0')+10*(key_1.c_str()[1]-'0')+(key_1.c_str()[2]-'0'));
        tmp_max_3 = (50*key_2.c_str()[0]+key_2.c_str()[1]-'A'-'A');
        max_1 = max_1 < tmp_max_1 ? tmp_max_1 : max_1;
        max_2 = max_2 < tmp_max_2 ? tmp_max_2 : max_2;
        max_3 = max_3 < tmp_max_3 ? tmp_max_3 : max_3; 
        TPair elem(key_0, key_1, key_2, val);
        vec.PushBack(elem);
    }
    
    RadixSort(vec, max_1, max_2, max_3);
    vec.Print();
    return 0;
}