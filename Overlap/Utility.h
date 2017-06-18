//
// Created by mary_mosteiro on 19.03.17.
//

#ifndef LINEAR_UTILITY_H
#define LINEAR_UTILITY_H

#include <fstream>
#include "Set.h"
#include <iomanip>

class Utility{

private:
    string trainFile;

public:
    Utility( const string &trainFile);

    void split(const string& s, char c, vector<string>& v);

    Set readTrainFile();

    int getIndexMax(vector<float> v);

};


#endif //LINEAR_UTILITY_H
