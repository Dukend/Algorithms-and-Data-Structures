#pragma once

#include <unordered_map>
#include <string>
#include <vector>

using TUll = unsigned long long;

struct VInput
{
	std::string Str;
	TUll Line;
	TUll Number;
};

struct TResults
{
	TUll Line;
	TUll Word;
	TUll Sample;
	TResults(TUll line, TUll word, TUll sample) : Line(line), Word(word), Sample(sample) {}
};

namespace NAlgo
{

	struct TNode
	{
		std::string Value;
		TUll Line;
		TUll Length;
		TNode *Par;
		TNode *SuffLink;
		TNode *TerminalLink;
		std::unordered_map<std::string, TNode *> Childs;
		std::unordered_map<std::string, TNode *> Next;

		TNode() : Value(""), Line(0), Length(0), Par(nullptr), SuffLink(nullptr), TerminalLink(nullptr) {}

		TNode(std::string &val, TNode *p) : Value(val), Line(0), Length(0), Par(p), SuffLink(nullptr), TerminalLink(nullptr) {}

		TNode *GetChild(std::string &str);
		bool IsTerminal()
		{
			return Length > 0;
		}
	};

	class TTrie
	{
		TNode *GetSuffix(TNode *node, std::string &val);
		void DeleteTrie(TNode *root);

		TNode *Root;

	public:
		void AddPattern(std::vector<std::string> &pattern, TUll line);
		void MakeSuffixes();
		void SearchPatterns(std::vector<VInput> &text, std::vector<TResults> &res);

		TTrie() : Root(new TNode())
		{
			Root->SuffLink = Root;
		}

		~TTrie()
		{
			DeleteTrie(Root);
		}
	};

}