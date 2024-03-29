// P1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <unordered_map>
#include "fileRead.h"
#include "VectorHash.h"
#include <algorithm>

#include <vector>
using namespace std;

typedef string T;   // Currently tests string language model.

bool comp(pair<vector<T>, int> a, pair<vector<T>, int> b) {
	return a.second > b.second;
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		cout << "Incorrect input parameters. Please enter filename as string and k as int, ex: " << endl;
		cout << "P1 p1_text.txt 4 " << endl;
		cout << "Ending execution...";
		return 0;
	}

	string filename = argv[1];
	int k = stoi(argv[2]);

	/*cout << argc << endl;
	cout << filename << endl;
	cout << k << endl;*/


	vector<T> tokens;     // stores tokens read from file
	int N = 0;
	
	unordered_map<vector<T>, int> database;

	read_tokens(filename, tokens, false);
	N = tokens.size();    // that is the number of words to process
	
	vector<pair<vector<T>, int>> maxNGrams(k);

	unsigned int n = 1;

	for (int i = 0; i <= tokens.size() - n; i++)
	{
		vector<T> nGram(n);   // for temporarily storing tokens to go into next n-gram
							  // Take next n tokens read from the input file 

		for (unsigned int j = 0; j < n; j++) // put next n tokens into vector temp
			nGram[j] = tokens[i + j];

		if (database.count(nGram) == 0) // nGram is not in the database yet, insert it with count 1
			database[nGram] = 1;
		else // nGram is already in the database, increase its count by 1
			database[nGram] = database[nGram] + 1;

	}

	double percentOfText = 0;
	double sumOfTopWords = 0;
	vector<pair<vector<T>, int>> sortedElems(database.begin(), database.end());
	sort(sortedElems.begin(), sortedElems.end(), comp);
	for (auto i = sortedElems.begin(); i != sortedElems.begin()+k; ++i)
	{
		cout << endl;
		vector<T> nGram = i->first;
		for (unsigned int j = 0; j < nGram.size(); j++)
			cout << nGram[j] << " ";  // prints out next string in the current nGram
		cout << " " << i->second; // prints out the count of this nGram
		sumOfTopWords += i->second;
	}

	percentOfText = 100.0*(sumOfTopWords/N);
	cout << endl << percentOfText <<"%";

	cout << endl;
	
	//cout << "\nNumber of distinct nGrams " << database.size();
	//cout << "\nTotal number of words read " << N << endl;
	
	string endingString;
	cout << "Press any key to exit" << endl;
	cin >> endingString;
    return 0;
}

