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

public:
    Utility(const string &testFile, const string &trainFile);

    void split(const string& s, char c, vector<string>& v);

    Set readTrainFile();

    Set readTestFile();

    void print1DVector(vector<float>v);

    void print2DVector(vector<vector<float>>v);

    int getIndexMax(vector<float> v);

    int classifyNewItem(vector<float> item, Set set);


    void checkOverlap(Set trainSet);

    float calculateDistance(vector<float> x, vector<float> y);

    float reduce(vector<float> v);

    float add(vector<float> v);
};


#endif //LINEAR_UTILITY_H
