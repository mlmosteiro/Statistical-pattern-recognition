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
    string testFile;
    string trainFile;
    string outFileString = "linearResults.txt";
    fstream out;

public:
    Utility(const string &testFile, const string &trainFile);

    void outln(string s);

    void split(const string& s, char c, vector<string>& v);

    Set readTrainFile();

    Set readTestFile();

    void print2DVector(vector<vector<float>>v);

    int getIndexMax(vector<float> v);

    int classifyNewItem(vector<float> item, Set set);

    virtual ~Utility();

};


#endif //LINEAR_UTILITY_H
