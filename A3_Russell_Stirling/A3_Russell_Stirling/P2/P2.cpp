// P2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <unordered_map>
#include "fileRead.h"
#include "VectorHash.h"

using namespace std;

typedef string T;

int main(int argc, char *argv[])
{
	if (argc != 5)
	{
		cout << "Incorrect input parameters. Please enter filename as string and k as int, ex: " << endl;
		cout << "P2 text1.txt text2.txt 5 0 " << endl;
		cout << "Ending execution...";
		cout << argc;
		string endingString2;
		cout << "Press any key to exit" << endl;
		cin >> endingString2;
		return 0;
	}

	string filename1 = argv[1];
	string filename2 = argv[2];
	unsigned int n = stoi(argv[3]);
	int print = stoi(argv[4]);

	vector<T> tokens;     // stores tokens read from file
	int N1 = 0;
	int N2 = 0;


	unordered_map<vector<T>, int> database1;
	unordered_map<vector<T>, int> database2;


	read_tokens(filename1, tokens, false);
	N1 = tokens.size();    // that is the number of words to process

	for (int i = 0; i <= tokens.size() - n; i++)
	{
		vector<T> nGram(n);   // for temporarily storing tokens to go into next n-gram
							  // Take next n tokens read from the input file 

		for (unsigned int j = 0; j < n; j++) // put next n tokens into vector temp
			nGram[j] = tokens[i + j];

		if (database1.count(nGram) == 0) // nGram is not in the database yet, insert it with count 1
			database1[nGram] = 1;
		else // nGram is already in the database, increase its count by 1
			database1[nGram] = database1[nGram] + 1;

	}
	read_tokens(filename2, tokens, false);
	N2 = tokens.size();

	for (int i = 0; i <= tokens.size() - n; i++)
	{
		vector<T> nGram(n);   // for temporarily storing tokens to go into next n-gram
							  // Take next n tokens read from the input file 

		for (unsigned int j = 0; j < n; j++) // put next n tokens into vector temp
			nGram[j] = tokens[i + j];

		if (database2.count(nGram) == 0) // nGram is not in the database yet, insert it with count 1
			database2[nGram] = 1;

		else // nGram is already in the database, increase its count by 1
			database2[nGram] = database2[nGram] + 1;
	}

	int db2NotInDb1 = 0;
	int N = 0;
	double percentNotInDB1;
	for (auto i = database2.begin(); i != database2.end(); ++i)
	{
		vector<T> nGram = i->first;
		N++;

		if (database1.count(nGram) == 0)
		{
			db2NotInDb1++;
		}
		else if (print == 1)
		{
			cout <<endl;
			for (unsigned int j = 0; j < nGram.size(); j++)
				cout << nGram[j] << " ";  // prints out next string in the current nGram
		}

	}

	percentNotInDB1 = 100.0*double(db2NotInDb1) / double(N);

	cout << endl << percentNotInDB1 << "%" << endl << endl;
	
	string endingString;
	cout << "Press any key to exit" << endl;
	cin >> endingString;

    return 0;
}

