//
// Created by mary_mosteiro on 19.03.17.
//

#ifndef LINEAR_SET_H
#define LINEAR_SET_H

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Set {

private:
    int numClasses;
    int numItems;
    int numFeatures;
    vector <vector<vector<float>>> items;
    vector <vector<float>> gravityCenters;
    vector <vector<vector<float>>> standardItems;
    vector <vector<float>> standardGravityCenters;
    vector <vector<float>> weights;
    vector <vector<float>> standardWeights;
    vector<float> weight_i;
    vector<float> average;
    vector<float> standarDeviation;

public:
    Set(){};

    int getNumItems() const;

    int getNumFeatures() const;

    int getNumClasses() const;

    void setNumClasses(int numClasses);

    void setNumItems(int numItems);

    void setNumFeatures(int numFeatures);

    void setItems(const vector<vector<vector<float>>> &items);

    void resizeVectors();

    void calculateAverage();

    void calculateStandardDeviation();

    void doStandardisation();

    void checkOverlap();

    float calculateDistance(vector<float> x, vector<float> y);

    vector<float> setMaxMinDist();

    float minDistToSameClassObject(int idObject, int idClass);
};

#endif //LINEAR_SET_H
