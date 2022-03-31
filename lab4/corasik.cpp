#include <queue>
#include "corasik.hpp"

using namespace std;

namespace NAlgo
{

	TNode *TNode::GetChild(string &str)
	{
		auto iter = this->Childs.find(str);
		if (iter == this->Childs.end())
		{
			return nullptr;
		}
		return iter->second;
	}

	void TTrie::AddPattern(vector<string> &pattern, TUll line)
	{
		TNode *node = Root;
		for (TUll i = 0; i < pattern.size(); i++)
		{
			TNode *child = node->GetChild(pattern[i]);
			if (child == nullptr)
			{
				child = new TNode(pattern[i], node);
				node->Childs.insert({pattern[i], child});
			}
			node = child;
		}
		node->Line = line;
		node->Length = pattern.size();
	}

	TNode *TTrie::GetSuffix(TNode *node, string &val)
	{
		TNode *prev = node->Par;
		TNode *cur = prev->SuffLink;

		TNode *res = nullptr;
		while ((res = cur->GetChild(val)) == nullptr && prev != cur)
		{
			prev = cur;
			cur = cur->SuffLink;
		}
		if (cur == Root && prev == cur)
		{
			return Root;
		}
		return res;
	}

	void TTrie::MakeSuffixes()
	{
		queue<TNode *> nodes;
		for (const auto &node : Root->Childs)
		{
			nodes.push(node.second);
		}

		while (!nodes.empty())
		{
			TNode *node = nodes.front();
			nodes.pop();

			node->SuffLink = GetSuffix(node, node->Value);
			if (node->SuffLink->IsTerminal())
			{
				node->TerminalLink = node->SuffLink;
			}
			else
			{
				node->TerminalLink = node->SuffLink->TerminalLink;
			}

			for (const auto &child : node->Childs)
			{
				nodes.push(child.second);
			}
		}
	}

	void TTrie::SearchPatterns(vector<VInput> &text, vector<TResults> &res)
	{
		TNode *node = Root;
		for (TUll i = 0; i < text.size(); i++)
		{
			TNode *child = nullptr;

			while ((child = node->GetChild(text[i].Str)) == nullptr && node != Root)
			{
				node = node->SuffLink;
			}
			if (child != nullptr)
			{
				if (child->IsTerminal())
				{
					TUll index = i - child->Length + 1;
					res.push_back({text[index].Line, text[index].Number, child->Line});
				}

				TNode *tmp = child->TerminalLink;
				while (tmp != nullptr)
				{
					TUll index = i - tmp->Length + 1;
					res.push_back({text[index].Line, text[index].Number, tmp->Line});
					tmp = tmp->TerminalLink;
				}
				node = child;
			}
		}
	}

	void TTrie::DeleteTrie(TNode *node)
	{
		for (const auto &child : node->Childs)
		{
			DeleteTrie(child.second);
		}
		delete node;
	}

}