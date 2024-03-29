// P3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <unordered_map>
#include "fileRead.h"
#include "VectorHash.h"
#include "utilsToStudents.h"

#include <vector>
#include <algorithm>

using namespace std;

typedef string T;



int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		cout << "Incorrect input parameters. Please enter filename as string and k as int, ex: " << endl;
		cout << "P1 p1_text.txt 4 " << endl;
		cout << "Ending execution...";
		return 0;
	}
	string eosValue = "<END>";
	string filename = argv[1];
	int n = stoi(argv[2]);
	vector<double> probs;
	vector<vector<T>> uniGrams;
	vector<T> tokens;     // stores tokens read from file
	int N = 0;

	vector<unordered_map<vector<T>, int>> databases(n);


	read_tokens(filename, tokens, true);
	N = tokens.size();    // that is the number of words to process

	for (int k = 0; k < databases.size(); k++)
	{
		for (int i = 0; i <= tokens.size() - (n-k); i++)
		{
			vector<T> nGram(n-k);     // for temporarily storing tokens to go into next n-gram
									// Take next n tokens read from the input file 

			for (unsigned int j = 0; j < (n-k); j++) // put next n tokens into vector temp
			{
				nGram[j] = tokens[i + j];
				
			}

			if (databases[k].count(nGram) == 0) // nGram is not in the database yet, insert it with count 1
			{
				databases[k][nGram] = 1;
				if ((n-k) == 1)
				{
					uniGrams.push_back(nGram);
				}
			}
			else // nGram is already in the database, increase its count by 1
				databases[k][nGram] = databases[k][nGram] + 1;
		}
	}

	if (n == 1)
	{
		srand(time(NULL));
		//the unigram probablilities
		for (int k = 0; k < uniGrams.size(); k++)
		{
			double prob = (databases[0][uniGrams[k]] / double(N));
			probs.push_back(prob);
		}

		int index = databases.size() - 1;
		
		bool eosSelected = false;
		do {
			int nxtWord = drawIndex(probs);
			vector<string> nGram = uniGrams[nxtWord];
			for (unsigned int j = 0; j < nGram.size(); j++)
				cout << nGram[j] << " ";  // prints out next string in the current nGram

			if (nGram[0] == eosValue)
				eosSelected = true;

		} while (!eosSelected);
		
	}
	else
	{
		srand(time(NULL));
		vector<string> prevWords = { eosValue };
		int dbIndex = databases.size() - prevWords.size();
		bool eosSelected = false;
		do {
			//c(eos w1)/c(eos)
			dbIndex = databases.size() - prevWords.size();
			double denom = double(databases[dbIndex][prevWords]);
			probs.clear();
			for (int i = 0; i < uniGrams.size(); i++)
			{
				prevWords.push_back(uniGrams[i][0]);
				double num = double(databases[dbIndex - 1][prevWords]);
				double prob = num / denom;
				probs.push_back(prob);
				prevWords.pop_back();
			}


			int nxtWord = drawIndex(probs);
			string nextWord = uniGrams[nxtWord][0];

			cout << nextWord << " ";  // prints out next string in the current nGram

			prevWords.push_back(nextWord);

			if (prevWords.size() > (n - 1))
			{
				prevWords.erase(prevWords.begin());
			}

			if (nextWord == eosValue)
				eosSelected = true;

		} while (!eosSelected);

	}

	string endingString;
	cout << endl << endl << "Press any key and enter to exit" << endl;
	cin >> endingString;

    return 0;
}

