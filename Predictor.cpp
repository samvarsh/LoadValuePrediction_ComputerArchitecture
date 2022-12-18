#include "Predictor.h"
#include <sstream>

Predictor::Predictor(unsigned int historyBits, unsigned int addrBits)
{
	this->historyBits = historyBits;
	this->addrBits = addrBits;

	this->total = 0;
	this->notPredicted = 0;
	this->predicted = 0;
	this->correct = 0;
}

//void Predictor::Predict(string insAddress, string actualValue)
//{
//	string previousValue = "";
//	// unsigned int address = truncateAddress(hexToInt(insAddress));
//	int flag = 0;
//	map<string, string>::iterator lvptIterator = lvpt.find(insAddress);
//	map<string, int>::iterator lctIterator = lct.find(insAddress);
//
//	this->total++;
//	if (lvptIterator != lvpt.end())
//	{
//		previousValue = lvptIterator->second;
//		int confidence = lctIterator->second;
//		if (confidence > 2)
//			this->predicted++;
//
//		if (previousValue == actualValue)
//		{
//
//			this->correct++;
//			flag = 1;	
//		}
//		else
//		{
//			lvptIterator->second = actualValue;
//			flag = -1;
//		}
//	}
//	else 
//	{
//		lvpt.insert(std::pair<string, string>(insAddress, actualValue));
//		this->notPredicted++;
//		// initially inserting 0 - 'not predict' - 
//		// determines the confidence to predict
//		lct.insert(std::pair<string, int>(insAddress, 1));
//	}
//
//
//}

void Predictor::Predict(string insAddress, string actualValue)
{
	string previousValue = "";
	// unsigned int address = truncateAddress(hexToInt(insAddress));
	map<string, string>::iterator lvptIterator = lvpt.find(insAddress);
	map<string, int>::iterator lctIterator = lct.find(insAddress);

	this->total++;
	if (lvptIterator != lvpt.end())
	{
		previousValue = lvptIterator->second;
		if (previousValue != actualValue)
			lvptIterator->second = actualValue;

		UpdateLCT(lctIterator, previousValue, actualValue);

	}
	else
	{
		lvpt.insert(std::pair<string, string>(insAddress, actualValue));
		this->notPredicted += 1;
		// initially inserting 0 - 'not predict' - 
		// determines the confidence to predict
		lct.insert(std::pair<string, int>(insAddress, 1));
	}


}

void Predictor::UpdateLCT(map<string, int>::iterator lctIterator, string previousValue, string actualValue)
{
	int val = lctIterator->second;
	if (previousValue != actualValue)
		DeterminePredictabilityOnNotEq(val);
	else
		DeterminePredictabilityOnSuccess(val);
	lctIterator->second = val;
}

void Predictor::DeterminePredictabilityOnSuccess(int &val)
{
	switch(val)
	{
	case 1:
		val = 2;
		this->notPredicted += 1;
		break;
	case 2:
		val = 3;
		this->predicted += 1;
		this->correct += 1;
		break;
	case 3:
		val = 4;
		this->predicted += 1;
		this->correct += 1;
		break;
	case 4:
		//this->constant++;
		this->predicted += 1;
		this->correct += 1;
		val = 4;
		break;
	}

}

void Predictor::DeterminePredictabilityOnNotEq(int& val)
{
	switch (val)
	{
	case 1:
		val = 1;
		this->notPredicted += 1;
		break;
	case 2:
		val = 1;
		this->predicted += 1;
		break;
	case 3:
		val = 2;
		this->predicted += 1;
		break;
	case 4:
		//this->constant++;
		this->predicted += 1;
		val = 3;
		break;
	}

}

void Predictor::PrintStats()
{
	std::cout << "\nTotal number of instructions: " << this->total;
	std::cout << "\nNumber of instructions predicted:" << this->predicted;
	std::cout << "\nNumber of correct predictions:" << this -> correct;
	std::cout << "\nNo of instructions not predicted:" << this->notPredicted;

}


/*
  * Convert Hex string from trace file to integer address
  */
unsigned int Predictor::hexToInt(string input) {
	istringstream converter(input);
	unsigned int result;
	converter >> std::hex >> result;
	return result;
}

/*
 * Truncate Address to specified number of address bits
 */
unsigned int Predictor::truncateAddress(unsigned int input) {
	unsigned int mask = (1 << this->addrBits) - 1;
	unsigned int result = input & mask;

	return result;
}
