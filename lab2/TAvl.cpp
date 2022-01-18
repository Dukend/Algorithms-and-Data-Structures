#include <algorithm>
#include <new>
#include <iostream>
#include "TData.hpp"
#include "TAvl.hpp"

//Повороты
TAvlNode* TAvl::RotLeft(TAvlNode* node)
{
	TAvlNode* new_node = node->r_;
	node->r_ = new_node->l_;
	new_node->l_ = node;
	ReHeight(node);
	ReHeight(new_node);
	return new_node;
}

TAvlNode* TAvl::RotRight(TAvlNode* node)
{
	TAvlNode* new_node = node->l_;
	node->l_= new_node->r_;
	new_node->r_ = node;
	ReHeight(node);
	ReHeight(new_node);
	return new_node;
}

TAvlNode* TAvl::RotRightLeft(TAvlNode* node)
{
	node->r_ = RotRight(node->r_);
	return RotLeft(node);
}

TAvlNode* TAvl::RotLeftRight(TAvlNode* node)
{
	node->l_ = RotLeft(node->l_);
	return RotRight(node);
}

//Перебалансировка
TAvlNode* TAvl::ReBalance(TAvlNode* node)
{
	if (node == nullptr) { return nullptr; }
	ReHeight(node);
	uint64_t balance = Balance(node);
	if (balance == -2)
	{
		if (Balance(node->r_) == 1) { return RotRightLeft(node); }
		return RotLeft(node);
	}
	else if (balance == 2)
	{
		if (Balance(node->l_) == -1) { return RotLeftRight(node); }
		return RotRight(node);
	}
	return node;
}

//Вставка с печатью на экран
TAvlNode* TAvl::InsertPrint(TAvlNode* node, TData k, uint64_t v, bool const& benchmark_flag)
{
	if (node == nullptr)
	{
		try { node = new TAvlNode(k, v); }
		catch (std::exception& e)
		{
			if(!benchmark_flag) { std::cout << "ERROR: " << e.what() << "\n"; }
			return nullptr;
		}
		if(!benchmark_flag) {std::cout << "OK\n";}
		return node;
	}
	if (k < node->key_) { node->l_ = InsertPrint(node->l_, k, v, benchmark_flag); }
	else if (k > node->key_) { node->r_ = InsertPrint(node->r_, k, v, benchmark_flag); }
	else { std::cout << "Exist\n"; }
	return ReBalance(node);
}

//Удаление минимального
TAvlNode* TAvl::RemoveMin(TAvlNode* node, TAvlNode* tmp)
{
	if (tmp->l_ != nullptr) { tmp->l_ = RemoveMin(node, tmp->l_); }
	else
	{
		TAvlNode* r = tmp->r_;
		node->key_ = std::move(tmp->key_);
		node->val_ = tmp->val_;
		delete tmp;
		tmp = r;
	}
	return ReBalance(tmp);
}

//Удаление с печатью
TAvlNode* TAvl::RemovePrint(TAvlNode* node, TData k, bool const& benchmark_flag)
{
	if (node == nullptr)
	{
		if(!benchmark_flag) { std::cout << "NoSuchWord\n"; }
		return nullptr;
	}
	if (k < node->key_) {node->l_ = RemovePrint(node->l_, k, benchmark_flag); }
	else if (k > node->key_) { node->r_ = RemovePrint(node->r_, k, benchmark_flag);	}
	else
	{
		TAvlNode* l = node->l_;
		TAvlNode* r = node->r_;
		if (l == nullptr && r == nullptr)
		{
			delete node;
			if(!benchmark_flag) { std::cout << "OK\n"; }
			return nullptr;
		}
		if (r == nullptr)
		{
			delete node;
			if(!benchmark_flag) { std::cout << "OK\n"; }
			return l;
		}
		if (l == nullptr)
		{
			delete node;
			if(!benchmark_flag) { std::cout << "OK\n"; }
			return r;
		}
		node->r_ = RemoveMin(node, r);
		if(!benchmark_flag) { std::cout << "OK\n"; }
	}
	return ReBalance(node);
}

//Поиск
TAvlNode* TAvl::Find(TAvlNode* node, TData k)
{
	if (node == nullptr) { return nullptr; }
	for (TAvlNode* iter = node; iter != nullptr; )
	{
		if (k < iter->key_) { iter = iter->l_; }
		else if (k > iter->key_) { iter = iter->r_;	}
		else { return iter;	}
	}
	return nullptr;
}

void TAvl::TreeDelete(TAvlNode* node)
{
	if (node != nullptr)
	{
		TreeDelete(node->l_);
		TreeDelete(node->r_);
		delete node;
	}
}
