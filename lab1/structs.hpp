#pragma once
#include <string>

typedef unsigned long long TUll;

struct TPair
{
    TPair(){}
    TPair(std::string const& key_0, std::string const& key_1, std::string const& key_2, TUll const& val)
    {
        key_[0] = key_0;
        key_[1] = key_1;
        key_[2] = key_2;
        val_ = val;
    }
    TPair(TPair const& obj)
    {
        val_ = obj.val_;
        key_[0] = obj.key_[0];
        key_[1] = obj.key_[1];
        key_[2] = obj.key_[2];
    }
    std::string key_[3];
    TUll val_;
};