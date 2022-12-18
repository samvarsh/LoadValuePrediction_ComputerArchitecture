#pragma once
#include <map>
#include <iostream>

using namespace std;

class Predictor
{
	unsigned int addrBits;
	unsigned int historyBits;

	int total;
	int notPredicted;
	int predicted;
	int correct;
	unsigned int hexToInt(string);
	unsigned int truncateAddress(unsigned int);

	map< string, string > lvpt; // load value prediction table
	map< string, int> lct; // load classification table

	void UpdateLCT(map<string, int>::iterator lctIterator, string previousValue, string actualValue);
	void DeterminePredictabilityOnSuccess(int& val);
	void DeterminePredictabilityOnNotEq(int& val);


public:
	Predictor(unsigned int, unsigned int);
	void Predict(string insAdress, string actualValue);
	void PrintStats();


};

