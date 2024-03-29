// P5.cpp : Defines the entry point for the console application.
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
		cout << "P5 textModel.txt sentences.txt 5 0.5 " << endl;
		cout << "Ending execution...";
		cout << endl << argc << endl;
		string tjid;
		cin >> tjid;
		return 0;
	}
	string filename = argv[1];
	string filenameSentance = argv[2];
	int n = stoi(argv[3]);
	double threshold = stod(argv[4]);
	double N;
	vector<T> tokens;
	vector<vector<T>> uniGrams;
	vector<vector<double>> nCounts(n);
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

			if (nCounts[k].size() < databases[k][nGram])   // update maximum nGram count, if needed 
				nCounts[k].push_back(0);
		}
		//for N0
		nCounts[k].push_back(0);
	}
	double V = double(uniGrams.size() + 1.0);
	tokens.clear();
	read_tokens(filenameSentance, tokens, false);

	for (int k = 0; k < databases.size(); k++)
	{
		int sumN1toMax = 0;
		for (auto i = databases[k].begin(); i != databases[k].end(); ++i)
		{
			nCounts[k][(i->second)]++;
			sumN1toMax++;
		}
		double N0 = pow(V, n-k) - sumN1toMax;
		nCounts[k][0] = N0;
	}

	vector<vector<double>> probs(nCounts.size());
	

	for (int k = 0; k < databases.size(); k++)
	{
		for (int i = 0; i < threshold; i++)
		{
			if (nCounts[k][i] <= 0)
				threshold = i;
			else
			{
				double r = double(i);
				double numerator = double(nCounts[k][i + 1]);
				double denominator = N * double(nCounts[k][i]);
				double prob = (r + 1.0) * (numerator / denominator);
				probs[k].push_back(prob);
			}
		}
		for (int i = threshold; i < nCounts[k].size(); i++)
		{
			double probMLE = double(i) / N;
			probs[k].push_back(probMLE);
		}

		
		//C(w)/N
	}

	for (int k = 0; k < databases.size(); k++)
	{
		double unobservedWeight;
		unobservedWeight = nCounts[k][0] * probs[k][0];
		double observedWeight = 1.0 - unobservedWeight;
		double sumObservedProbabilities = 0.0;
		for (int i = 1; i < nCounts[k].size(); i++)
		{
			sumObservedProbabilities += (nCounts[k][i] * probs[k][i]);
		}
		//sumObservedProbabilities * y = observedWeight
		//y = observedWeight/sumObservedProbabilities
		double y = observedWeight / sumObservedProbabilities;
		for (int i = 1; i < nCounts[k].size(); i++)
		{
			probs[k][i] = probs[k][i] * y;
		}
	}

	//probabilities are now normalized. Now we can calculate.

	vector<string> prevWords;
	double logSum = 0.0;
	double num = 0.0;
	double den = 0.0;

	for (int i = 0; i < tokens.size(); i++)
	{
		
		if (prevWords.size() == 0)
		{
			den = 1.0;
			prevWords.push_back(tokens[i]);
			double r = double(databases[databases.size() - prevWords.size()][prevWords]);
			num = probs[databases.size() - prevWords.size()][r];
		}
		else
		{
			double r = double(databases[databases.size() - prevWords.size()][prevWords]);
			den = probs[databases.size() - prevWords.size()][r];
			prevWords.push_back(tokens[i]);
			if (prevWords.size() > n)
				prevWords.erase(prevWords.begin());
			r = double(databases[databases.size() - prevWords.size()][prevWords]);
			num = probs[databases.size() - prevWords.size()][r];
		}

		logSum += log(num / den);
		if (prevWords.size() > (n - 1))
			prevWords.erase(prevWords.begin());

	}

	cout << endl << logSum << endl;
	
	string endingString;
	cout << endl << endl << "Press any key and enter to exit" << endl;
	cin >> endingString;

    return 0;
}

