#include <iostream>
#include <sstream>

#include <fstream>
#include "../headers/funckijas.h"


using namespace std;

    string IntToStr(int cipars) {
        string line;
        stringstream buffer;

        buffer << cipars;

        buffer >> line;

        return line;
    }

    int StrToInt(string line) {
        int cipars;
        stringstream buffer;

        buffer << line;

        buffer >> cipars;

        return cipars;
    }

    int getCount(string way) {

        string buffer;

        int counter = 0;

        ifstream file (way.c_str());

        while (getline(file, buffer)) {
            counter++;
        }

        file.close();

        return counter;

    }
