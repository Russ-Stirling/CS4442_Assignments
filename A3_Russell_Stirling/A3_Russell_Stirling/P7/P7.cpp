// P7.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <unordered_map>
#include "fileRead.h"
#include "VectorHash.h"
#include "utilsToStudents.h"

using namespace std;

typedef string T;

int main(int argc, char *argv[])
{
	string trainFile = (argv[1]);
	string checkFile = (argv[2]);
	string dictionaryFile = (argv[3]);

	int n = stoi(argv[4]);
	double threshold = stod(argv[5]);
	int delta = stod(argv[6]);
	int model = stoi(argv[7]);

	vector<T> tokens;

	vector<string> dictionary;

	vector<vector<T>> uniGrams;
	double N = 0;

	read_tokens(trainFile, tokens, false);
	N = double(tokens.size());
	vector<vector<double>> nCounts(n);

	unordered_map<int, unordered_map<vector<T>, double>> databases;

	for (int k = 0; k < n; k++)
	{
		for (int i = 0; i <= tokens.size() - (n - k); i++)
		{
			vector<T> nGram(n - k);     // for temporarily storing tokens to go into next n-gram
										// Take next n tokens read from the input file 

			for (unsigned int j = 0; j < (n - k); j++) // put next n tokens into vector temp
			{
				nGram[j] = tokens[i + j];

			}

			if (databases[n-k].count(nGram) == 0) // nGram is not in the database yet, insert it with count 1
			{
				databases[n-k][nGram] = 1;
				if ((n - k) == 1)
				{
					uniGrams.push_back(nGram);
				}
			}
			else // nGram is already in the database, increase its count by 1
				databases[n-k][nGram] = databases[n-k][nGram] + 1;

			if (nCounts[n-k].size() < databases[n-k][nGram])   // update maximum nGram count, if needed 
				nCounts[n-k].push_back(0);
		}
		//for N0
		nCounts[k].push_back(0);
	}

	tokens.clear();
	read_tokens(dictionaryFile, tokens, false);

	for (int i = 0; i <= tokens.size(); i++)
	{
		dictionary.push_back(tokens[i]);
	}
	double V = double(uniGrams.size() + 1.0);
	for (auto k = databases.begin(); k != databases.end(); ++k)
	{
		int sumN1toMax = 0;
		for (auto i = k->second.begin(); i != k->second.end(); ++i)
		{
			while (nCounts[k->first].size()-1 < i->second)
			{
				nCounts[k->first].push_back(0);
			}
			nCounts[k->first][(i->second)]++;
			sumN1toMax++;
		}
		double N0 = pow(V, n - k->first) - sumN1toMax;
		nCounts[k->first][0] = N0;
	}

	tokens.clear();
	read_tokens(checkFile, tokens, true);

	vector<vector<T>> sentences;

	for (int i = 0; i < tokens.size(); i++)
	{
		vector<T> nGram;
		while (tokens[i] != "<END>")
		{
			nGram.push_back(tokens[i]);
			i++;
		}
		sentences.push_back(nGram);
	}

	vector<vector<double>> probs(nCounts.size());

	if (model == 0)
	{
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
	}

	for (int i = 0; i < sentences.size(); i++)
	{
		vector<T> sentence = sentences[i];
		vector<string> newSentance;

		unordered_map<string, vector<string>> replaceCandidates;
		for (int j = 0; j < sentence.size(); j++)
		{
			string word = sentence[j];
			vector<string> canditdates;
			canditdates.push_back(word);
			for (int k = 0; k < dictionary.size(); k++)
			{
				double probW = uiLevenshteinDistance(word, dictionary[k]);
				if (probW <= 1.0)
					canditdates.push_back(dictionary[k]);
			}
			replaceCandidates[word] = canditdates;
		}
		double maxProb = -1 * DBL_MAX;

		if (model == 0)
		{
			for (auto j = replaceCandidates.begin(); j != replaceCandidates.end(); ++j)
			{
				for (int it = 0; it < j->second.size(); it++)
				{
					vector<string> prevWords;
					vector<string> tempSentence;
					double logSum = -1 * DBL_MAX;
					double num = 0.0;
					double den = 0.0;
					for (int i = 0; i < sentence.size(); i++)
					{

						if (prevWords.size() == 0)
						{
							den = 1.0;
							string tempWord = sentence[i];
							if (sentence[i] == j->first)
								tempWord = j->second[it];
							prevWords.push_back(tempWord);
							tempSentence.push_back(tempWord);
							double r = double(databases[prevWords.size()][prevWords]);
							num = probs[prevWords.size()][r];
						}
						else
						{
							double r = double(databases[prevWords.size()][prevWords]);
							den = probs[prevWords.size()][r];
							string tempWord = sentence[i];
							if (sentence[i] == j->first)
								tempWord = j->second[it];
							prevWords.push_back(tempWord);
							tempSentence.push_back(tempWord);
							if (prevWords.size() > n)
								prevWords.erase(prevWords.begin());
							r = double(databases[prevWords.size()][prevWords]);
							num = probs[prevWords.size()][r];
						}

						logSum += log(num / den);
						if (prevWords.size() > (n - 1))
							prevWords.erase(prevWords.begin());

					}
					if (logSum > maxProb)
					{
						maxProb = logSum;
						newSentance = tempSentence;
					}
				}

			}
			//Good turing
		}

		else
		{
			for (auto j = replaceCandidates.begin(); j != replaceCandidates.end(); ++j)
			{


			}
			//delta
		}

		for (int tempIt = 0; tempIt < newSentance.size(); tempIt++)
		{
			cout << newSentance[tempIt] << " ";
		}
		cout << endl;
	}

	

	//hugeTrain.txt textCheck.txt dictionary.txt 2 2 0.01 0

    return 0;
}

