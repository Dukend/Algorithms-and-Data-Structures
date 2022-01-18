#pragma once

#include <cstring>
#include <utility>
#include <iostream>
#include <algorithm>

//Класс для хранения данных
class TData
{
	private:
		size_t cap_;
		size_t size_;
		char* data_;
	public:
		TData();
		TData(char const*);
		TData(TData const&);
		~TData() { delete[] this->data_; }
		TData& operator=(TData const&);
		void Move(char*);
		void Swap(TData&);
		void PushBack(char const&);
		char* begin() { return this->data_; }
		char const* begin() const { return this->data_; }
		char* end();
		char const* end() const;
		size_t Size() const { return this->size_; }
		char const* Data() const { return this->data_; }
		char& operator[](size_t ind) { return this->data_[ind]; }
		char const& operator[](size_t ind) const { return this->data_[ind]; }

		friend std::ostream& operator<<(std::ostream&, TData const&);
		friend std::istream& operator>>(std::istream&, TData&);
};

//Операторы сравнений
bool operator<(TData const&, TData const&);
bool operator>(TData const&, TData const&);
bool operator==(TData const&, TData const&);
bool operator!=(TData const&, TData const&);
