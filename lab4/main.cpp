#include <iostream>
#include <string>
#include <vector>

#include "corasik.hpp"

using namespace std;

void SplitLine(string &line, vector<string> &vec)
{
	TUll i = 0;
	string word = "";
	while (i < line.size() && isspace(line[i]))
	{
		i++;
	}
	while (i < line.size())
	{
		while (i < line.size() && !isspace(line[i]))
		{
			word += tolower(line[i]);
			i++;
		}
		vec.push_back(word);
		word.clear();

		while (i < line.size() && isspace(line[i]))
		{
			i++;
		}
	}

	if (word != "")
	{
		vec.push_back(word);
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	NAlgo::TTrie trie;
	string word;

	TUll line = 1;
	string strline = "";
	while (getline(cin, strline))
	{
		vector<string> pattern;
		SplitLine(strline, pattern);

		if (pattern.size() == 0)
		{
			break;
		}

		trie.AddPattern(pattern, line);
		line++;
	}

	trie.MakeSuffixes();

	vector<VInput> text;
	vector<TResults> results;
	line = 1;
	while (getline(cin, strline))
	{
		vector<string> vecline;
		SplitLine(strline, vecline);
		for (size_t i = 0; i < vecline.size(); i++)
		{
			text.push_back({vecline[i], line, i + 1});
		}
		line++;
	}

	trie.SearchPatterns(text, results);

	for (const auto &res : results)
	{
		cout << res.Line << ", " << res.Word << ", " << res.Sample << '\n';
	}
}