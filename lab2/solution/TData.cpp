#include <cstring>
#include <utility>
#include <iostream>
#include <algorithm>
#include "TData.hpp"

//Конструктор по умолчанию
TData::TData() : cap_(0), size_(0), data_(nullptr) {}

//Конструктор с одним параметром
TData::TData(char const* str)
{
	this->size_ = std::strlen(str);
	this->cap_ = this->size_ + 1;
	this->data_ = new char[this->cap_];
	std::copy(str, str + this->size_, this->data_);
	this->data_[this->size_] = '\0';
}

//Конструктор копирования
TData::TData(TData const& str)
{
	this->cap_= str.cap_;
	this->size_ = str.size_;
	this->data_ = new char[this->cap_];
	std::copy(str.data_, str.data_ + this->size_, this->data_);
	this->data_[this->size_] = '\0';
}

//Оператор присваивания
TData& TData::operator=(TData const& str)
{
	char* tmp = new char[str.cap_];
	std::copy(str.data_, str.data_ + str.cap_, tmp);
	delete [] this->data_;
	this->data_ = tmp;
	tmp = nullptr;
	this->size_ = str.size_;
	this->cap_= str.cap_;
	return *this;
}

//Перемещение данных
void TData::Move(char* str)
{
	delete [] this->data_;
	this->data_ = str;
	this->size_ = strlen(str);
	this->cap_ = this->size_ + 1;
	str = nullptr;
}

//Обмен данных
void TData::Swap(TData& str)
{
	std::swap(this->size_, str.size_);
	std::swap(this->cap_, str.cap_);
	std::swap(this->data_, str.data_);
}

//Добавление в конец вектора
void TData::PushBack(char const& symb)
{
	if (this->size_ + 1 == this->cap_)
	{
		size_t cap = this->cap_ ? this->cap_ * 2 : 1;
		char* buff = new char[cap];
		std::copy(this->data_, this->data_ + this->cap_, buff);
		delete[] this->data_;
		this->data_ = buff;
		this->cap_ = cap;
	}
	this->data_[this->size_] = symb;
	this->size_ += 1;
	this->data_[this->size_] = '\0';
}

char* TData::end()
{
	if (this->data_ != nullptr) { return this->data_ + this->size_; }
	return nullptr;
}
char const* TData::end() const
{
	if (this->data_ != nullptr) { return this->data_ + this->size_; }
	return nullptr;
}

//Операторы ввода-вывода
std::ostream& operator<<(std::ostream& os, TData const& str)
{
	for (auto symb: str) { os << symb;	}
	return os;
}
std::istream& operator>>(std::istream& is, TData& str)
{
	char buff[260];
	if (is >> buff) { str = buff; }
	return is;
}

//Операторы сравнений
bool operator<(TData const& lhs, TData const& rhs)
{
	size_t size = std::min(lhs.Size(), rhs.Size());
	for (size_t i = 0; i < size; ++i) {	if (lhs[i] != rhs[i]) {	return lhs[i] < rhs[i];	} }
	return lhs.Size() < rhs.Size();
}

bool operator>(TData const& lhs, TData const& rhs) { return rhs < lhs; }
bool operator==(TData const& lhs, TData const& rhs) {	return !(lhs > rhs) && !(lhs < rhs); }
bool operator!=(TData const& lhs, TData const& rhs) { return !(lhs == rhs); }
