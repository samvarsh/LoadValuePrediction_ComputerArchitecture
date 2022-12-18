// LoadValuePrediction.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "TraceFile.h"
#include "Predictor.h"

int main()
{
    string fileName = "Input5000.txt";
    TraceFile trace(fileName);
    string insAddress = "", actualValue = "";

    Predictor predictor(0, 8);
    while (trace.GetNextInstruction(insAddress, actualValue))
    {
        predictor.Predict(insAddress, actualValue);
    }
    predictor.PrintStats();

}
