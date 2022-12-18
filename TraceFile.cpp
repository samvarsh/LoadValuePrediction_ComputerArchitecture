#include "TraceFile.h"

TraceFile::TraceFile(string fileName) {
    this->fileName = fileName;
    this->inputStream.open(this->fileName.c_str());
    if (!this->inputStream.is_open()) {
        cout << "error opening file: " << this->fileName << endl;
        exit(1);
    }
}


bool TraceFile::GetNextInstruction(string& insAddress, string& actualValue) {
    //if closed return 0
    if (!this->inputStream.is_open()) {
        return 0;
    }
    string input1, input2, input3, input4;
    //check if can get input
    if (this->inputStream >> input1 >> input2 >> input3 >> input4) {
        insAddress = input1;
        actualValue = input4;
        return 1;
    }
    else {
        this->inputStream.close();
        return 0;
    }
}