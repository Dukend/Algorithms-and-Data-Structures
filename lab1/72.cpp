#include <stdio.h>
#include <iostream>
#include <chrono>
#include <stack>
const int Auto = 9;
const int STR = 2049;
const int HUNDR = 100;

struct Data
{
public:
	char key[Auto];
	int index;
	Data() {}
	Data(char k[Auto], int x)
	{
		index = x;
		for (int i = 0; i < Auto; i++)
		{
			key[i] = k[i];
		}
	}
};

struct Str
{
private:
	char str[STR];

public:
	Str() {}
	Str(std::istream &in)
	{
		in >> str;
	}
	friend std::ostream &operator<<(std::ostream &out, const Str &point)
	{
		out << point.str;
		return out;
	}
};

template <class T>
class TVector
{
private:
	T *storage;
	int size;
	int capacity;

public:
	TVector() : storage(nullptr), size(0), capacity(0){};
	TVector(int ssize, const T default_value = T())
	{
		storage = new T[ssize];
		size = ssize;
		capacity = ssize;
		for (int i = 0; i < (int)size; i++)
			storage[i] = default_value;
	}
	~TVector()
	{
		delete[] storage;
		storage = nullptr;
		size = 0;
		capacity = 0;
	}
	int Size() const
	{
		return size;
	}
	bool Empty() const
	{
		return Size() == 0;
	}
	int Capacity() const
	{
		return capacity;
	}
	T *Begin() const
	{
		return storage;
	}
	T *End() const
	{
		return storage ? storage + size : nullptr;
	}

	T &At(int index) const
	{
		if (index < 0 || index >= (int)size)
			throw std::out_of_range("Error memory");
		return storage[index];
	}
	T &operator[](int index) const
	{
		return At(index);
	}
	void PushBack(T &&value)
	{
		if (size == capacity)
		{
			T *temp_storage = storage;
			size == 0 ? capacity = 1 : capacity *= 2;
			storage = new T[capacity];
			for (int i = 0; i < size; i++)
				storage[i] = temp_storage[i];
			delete[] temp_storage;
		}
		storage[size++] = value;
		return;
	}
	TVector<T> &operator=(const TVector<T> &other)
	{
		if (Size() != other.Size())
		{
			delete[] storage;
			storage = new T[other.capacity];
			capacity = other.capacity;
			size = other.size;
		}
		for (int i = 0; i < size; i++)
			storage[i] = other.storage[i];
		return *this;
	}
};

void RadixSort(TVector<Data> &str)
{
	int c[HUNDR];
	TVector<Data> temp = TVector<Data>(str.Size());
	for (int j = 7; j >= 0; --j)
	{
		if (j == 1 || j == 5)
			continue;
		for (int i = '0'; i < 'Z' + 1; ++i)
		{
			c[i] = 0;
		}
		for (int i = 0; i < str.Size(); ++i)
		{
			c[(int)str[i].key[j]]++;
		}
		for (int i = '0' + 1; i < 'Z' + 1; ++i)
		{
			c[i] += c[i - 1];
		}
		for (int i = str.Size() - 1; i >= 0; --i)
		{
			temp[--c[(int)str[i].key[j]]] = str[i];
		}
		str = temp;
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	TVector<Data> data; // вектор с ключами и индексами str
	TVector<Str> str;	// массив строк, которые мы не будем копировать и будем обращаться с помощью индексов data
	char key[9];
	int i = 0;
	while (std::cin >> key[0])
	{
		std::cin.getline(key + 1, Auto - 1, '\t'); // считываем номер авто
		data.PushBack(Data(key, i));			   // пушим номер авто в data
		i++;

		str.PushBack(Str(std::cin)); // считываем строку и пушим в str
	}

	// auto t1 = std::chrono::high_resolution_clock::now();
	RadixSort(data); // поразрядно сортим
	// auto t2 = std::chrono::high_resolution_clock::now();
	// auto res = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
	// std::cout << "res = " << res.count() << '\n';

	for (int i = 0; i < data.Size(); ++i)
	{
		std::cout << data[i].key << '\t' << str[data[i].index] << '\n'; // вывод
	}

	return 0;
}
stack<int> steck;

