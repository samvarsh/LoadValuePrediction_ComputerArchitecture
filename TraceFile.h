#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
using namespace std;

class TraceFile
{
private:
    string fileName;
    ifstream inputStream;

public:
    TraceFile(string fileName);
    bool GetNextInstruction(string&, string&);
};

