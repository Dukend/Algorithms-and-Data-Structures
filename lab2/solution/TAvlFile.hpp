#pragma once

#include <iostream>
#include <fstream>
#include <cctype>
#include <algorithm>
#include "TAvl.hpp"
#include "TData.hpp"

//Класс для работы с AVL деревом
struct TAvlFile : public TAvl
{
	private:
		void Upper(TData&);
		void Save(std::ostream&, TAvlNode const*);
		TAvlNode* Load(std::istream&, TAvlNode const*);
		bool FileSave(TData&);
		bool FileLoad(TData&);
	public:
		void DInsert();
		void DRemove();
		void DFind(TData const&);
		void LoadSave();
};
