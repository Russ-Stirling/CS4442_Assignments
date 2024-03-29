// P4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <unordered_map>
#include "fileRead.h"
#include "VectorHash.h"

#include "utilsToStudents.h"
#include <cmath>
using namespace std;

typedef string T;

int main(int argc, char *argv[])
{
	if (argc != 5)
	{
		cout << "Incorrect input parameters. Please enter filename as string and k as int, ex: " << endl;
		cout << "P4 textModel.txt sentences.txt 5 0.1 " << endl;
		cout << "Ending execution...";
		cout << endl << argc << endl;
		string tjid;
		cin >> tjid;
		return 0;
	}
	string filename = argv[1];
	string filenameSentance = argv[2];
	int n = stoi(argv[3]);
	double delta = stod(argv[4]);
	double N;
	vector<T> tokens;
	vector<vector<T>> uniGrams;
	vector<unordered_map<vector<T>, int>> databases(n);

	read_tokens(filename, tokens, false);
	N = double(tokens.size());    // that is the number of words to process

	for (int k = 0; k < databases.size(); k++)
	{
		for (int i = 0; i <= tokens.size() - (n - k); i++)
		{
			vector<T> nGram(n - k);     // for temporarily storing tokens to go into next n-gram
										// Take next n tokens read from the input file 

			for (unsigned int j = 0; j < (n - k); j++) // put next n tokens into vector temp
			{
				nGram[j] = tokens[i + j];

			}

			if (databases[k].count(nGram) == 0) // nGram is not in the database yet, insert it with count 1
			{
				databases[k][nGram] = 1;
				if ((n - k) == 1)
				{
					uniGrams.push_back(nGram);
				}
			}
			else // nGram is already in the database, increase its count by 1
				databases[k][nGram] = databases[k][nGram] + 1;
		}
	}

	tokens.clear();
	read_tokens(filenameSentance, tokens, false);

	//P(w1w2w3w4w5w6) under trigram
	//= Log(c(w1)/N) + Log(c(w1w2)/c(w1)) + Lo

	double logSum = 0.0;
	double V = double(uniGrams.size()+1.0);
	vector<string> prevWords;
	double numerator, denominator;
	try
	{
		for (int i = 0; i < tokens.size(); i++)
		{

			if (prevWords.size() == 0)
			{
				denominator = N + (pow(V, prevWords.size() + 1)*delta);
			}
			else
			{
				double tempNum = double(databases[databases.size() - prevWords.size()][prevWords]) + delta;
				double tempB = pow(V, prevWords.size());
				double tempDen = N + tempB*delta;

				denominator = double(tempNum / tempDen);
			}

			prevWords.push_back(tokens[i]);
			if (prevWords.size() > n)
				prevWords.erase(prevWords.begin());

			if (prevWords.size() == 1)
			{
				numerator = double(databases[databases.size() - prevWords.size()][prevWords]) + delta;
			}
			else
			{
				double tempNum = double(databases[databases.size() - prevWords.size()][prevWords]) + delta;
				double tempB = pow(V, prevWords.size());
				double tempDen = N + tempB*delta;
				numerator = double(tempNum / tempDen);

			}

			logSum += log(numerator / denominator);
			if (prevWords.size() > (n - 1))
				prevWords.erase(prevWords.begin());

		}
	}
	catch (exception e)
	{
		logSum = -1 * DBL_MAX;
	}

	if (logSum == log(0))
		logSum = -1 * DBL_MAX;


	cout << endl << logSum << endl;

	string endingString;
	cout << endl << endl << "Press any key and enter to exit" << endl;
	cin >> endingString;
	return 0;
}

