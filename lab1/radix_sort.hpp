#pragma once
#include <string>

template <typename T>
size_t TmpChange(TVector<T>& vec, size_t count, size_t i)
{
    size_t tmp = 0;
    if(count == 0)
    {
        const char* str = vec[i].key_[2].c_str();
        tmp = (50 * str[0] + str[1] -'A'-'A');
    }
    else if(count == 1)
    {
        const char* str = vec[i].key_[1].c_str();
        tmp = 100*(str[0]-'0')+10*(str[1]-'0')+(str[2]-'0');
    }
    else
    {
        const char* str = vec[i].key_[0].c_str();
        tmp = (str[0] - 'A');
    }
    return tmp;
}

template <typename T>
void CountingSort(TVector<T>& vec, size_t const& max, size_t& count)
{
    TVector<T> res_vec(vec.Size());
    TVector<int> ptr(max+1);
    for(size_t i = 0; i <= max; ++i)
    {
        ptr[i] = 0;
    }
    for(size_t i = 0; i < vec.Size(); ++i) 
    {
        ptr[TmpChange(vec, count, i)] += 1;
    }
    for(size_t i = 1; i <= max; ++i)
    {
        ptr[i] += ptr[i-1];
    }
    for(size_t i = vec.Size(); i > 0; --i)
    {
        res_vec[ptr[TmpChange(vec, count, i-1)] - 1] = vec[i-1];
        ptr[TmpChange(vec, count, i-1)] -= 1;
    }
    for(size_t i = 0; i < vec.Size(); ++i)
    {
        vec[i] = res_vec[i];
    }
    count += 1;
}

template <typename T>
void RadixSort(TVector<T>& vec, size_t const& max_1, size_t const& max_2, size_t const& max_3)
{
    size_t count = 0;
    CountingSort(vec, max_3, count);
    CountingSort(vec, max_2, count);
    CountingSort(vec, max_1, count);
}
