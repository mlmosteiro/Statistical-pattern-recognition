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

    void print1DVector(vector<float>v);

    void print2DVector(vector<vector<float>>v);

    virtual ~Utility();

    const string &getOutFileString() const;

    int getIndexMax(vector<int> v);

    float calculateDistance(vector<float> x, vector<float> y);

    int classifyNewItem(vector<float> item, Set trainSet, int kNN);
};


#endif //LINEAR_UTILITY_H
