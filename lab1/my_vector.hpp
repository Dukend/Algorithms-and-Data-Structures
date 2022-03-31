#pragma once
#include <iostream>
#include <string>

template<typename T>
class TVector
{
    private:
        size_t size_;
        size_t cap_;
        T* data_;
    public:
        TVector(){}
        TVector(size_t cap);
        ~TVector(){ delete [] data_; }
        TVector(TVector<T> const& obj);
        void Print() const;
        T& operator[](size_t index) const { return data_[index]; }
        T& operator[](size_t index){ return data_[index]; }
        size_t Size() const {return size_;}
        void PushBack(T const& val);
};

template <typename T>
TVector<T>::TVector(size_t cap)
{
    size_ = 0;
    cap_ = cap;
    data_ = new T[cap_];
}

template <typename T>
TVector<T>::TVector(TVector<T> const& obj)
{
    size_ = obj.size_;
    cap_ = obj.cap_;
    data_ = new T[cap_];
    for(size_t i = 0; i < size_; ++i)
    {
        data_[i] = obj.data_[i];
    }
}

template <typename T>
void TVector<T>::PushBack(T const& val)
{
    if(size_ == cap_)
    {
        cap_ *= 2;
        T* new_data = new T[cap_];
        for(size_t i = 0; i < size_; ++i) 
        {
            new_data[i] = data_[i];
        }
        delete [] data_;
        data_ = new_data;
    }
    data_[size_] = val;
    size_ += 1;
}

template <typename T>
void TVector<T>::Print() const
{
    for(size_t i = 0; i < size_; ++i) 
    {
        std::cout << data_[i].key_[0] << " " << data_[i].key_[1] << " " << data_[i].key_[2] << "\t" << data_[i].val_ << "\n";
    }
} 