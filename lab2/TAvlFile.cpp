#include <iostream>
#include <fstream>
#include <cctype>
#include <algorithm>
#include "TAvl.hpp"
#include "TData.hpp"
#include "TAvlFile.hpp"

//Приводим к верхнему регистру
void TAvlFile::Upper(TData& str)
{
	size_t size = str.Size();
	for (size_t i = 0; i < size; ++i) { str[i] = std::toupper(str[i]);	}
}

//Сохранение
void TAvlFile::Save(std::ostream& os, TAvlNode const* node)
{
	if (node == nullptr) { return; }
	size_t k_size = node->key_.Size();
	os.write((char*)(&k_size), sizeof(k_size));
	os.write(node->key_.Data(), k_size);
	os.write((char*)&node->val_, sizeof(node->val_));

	bool hasLeft = node->l_ != nullptr;
	bool hasRight = node->r_ != nullptr;

	os.write((char*)(&hasLeft), sizeof(hasLeft));
	os.write((char*)(&hasRight), sizeof(hasRight));
	if (hasLeft) { Save(os, node->l_); }
	if (hasRight) {	Save(os, node->r_);	}
}

//Загрузка
TAvlNode* TAvlFile::Load(std::istream& is, TAvlNode const* node)
{
	(void)(node);
	TAvlNode* root = nullptr;
	size_t k_size;
	is.read((char*)(&k_size), sizeof(k_size));
	if (is.gcount() == 0) {	return root; }
	char* key = new char[k_size + 1];
	key[k_size] = '\0';
	is.read(key, k_size);
	uint64_t val;
	is.read((char*)(&val), sizeof(val));

	bool hasLeft = false;
	bool hasRight = false;

	is.read((char*)(&hasLeft), sizeof(hasLeft));
	is.read((char*)(&hasRight), sizeof(hasRight));

	root = new TAvlNode();
	root->key_.Move(key);
	root->val_ = val;

	if (hasLeft) { root->l_ = Load(is, root); }
	else { root->l_ = nullptr; }
	if (hasRight) {	root->r_ = Load(is, root); }
	else { root->r_ = nullptr; }

	return root;
}

//Сохранение в файл
bool TAvlFile::FileSave(TData& fileName)
{
	std::ofstream os(fileName.Data(), std::ios::binary | std::ios::out);
	if (os) { Save(os, root_); }
	else { return false; }
	os.close();
	return true;
}

//Загрузка из файла
bool TAvlFile::FileLoad(TData& fileName)
{
	std::ifstream is(fileName.Data(), std::ios::binary | std::ios::in);
	if (is)
	{
		TreeDelete(root_);
		root_ = Load(is, nullptr);
	}
	else { return false; }
	is.close();
	return true;
}

//Методы для вставки, удаления, поиска, сохранения/загрузки
void TAvlFile::DInsert()
{
	TData key;
	uint64_t value = 0;
	std::cin >> key >> value;
	Upper(key);
	InsPrint(std::move(key), value);
}

void TAvlFile::DRemove()
{
	TData key;
	std::cin >> key;
	Upper(key);
	DeletePrint(std::move(key));
}

void TAvlFile::DFind(TData const& k)
{
	TData key(k);
	Upper(key);
	TAvlNode* res = Find(std::move(key));
	if (res != nullptr) { std::cout << "OK: " << res->val_ << "\n"; }
	else { std::cout << "NoSuchWord\n";	}

}

void TAvlFile::LoadSave()
{
	TData cmd;
	TData fileName;
	std::cin >> cmd >> fileName;
	if (cmd[0] == 'S')
	{
		if (!FileSave(fileName))
		{
			std::cout << "ERROR: can't open file\n";
			return;
		}
	}
	else
	{
		if (!FileLoad(fileName))
		{
			std::cout << "ERROR: can't open file\n";
			return;
		}
	}
	std::cout << "OK\n";
}
