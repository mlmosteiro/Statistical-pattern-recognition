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
    vector <vector<float>> unclasifiedItems;
    vector <vector<float>> gravityCenters;
    vector <vector<vector<float>>> standardItems;
    vector <vector<float>> standardGravityCenters;
    vector <vector<float>> weights;
    vector <vector<float>> standardWeights;
    vector<float> weight_i;
    vector<float> average;
    vector<float> standarDeviation;
    vector<pair<vector<float>, int>> reducedSet;


public:
    Set(){};

    int getNumClasses() const;

    void setNumClasses(int numClasses);

    void setNumItems(int numItems);

    void setNumFeatures(int numFeatures);

    void setItems(const vector<vector<vector<float>>> &items);

    const vector<vector<float>> &getUnclasifiedItems() const;

    void setUnclasifiedItems(const vector<vector<float>> &unclasifiedItems);

    void resizeVectors();

    void calculateAverage();

    void calculateStandardDeviation();

    void doStandardisation();

    vector<float> doStandardisationToItem(vector<float> item);

    void calculateReducedSet();

    pair<vector<float>,pair<int,int>> minDistFromSet(pair<vector<float>,pair<int,int>>item, vector<pair<vector<float>,pair<int,int>>>set);

    static float calculateDistance(vector<float> x, vector<float> y);

    void reducedSetToFile();

    int calculateMutualDistance(int noClass, int noFeature);

    float calculateMinDistanceToOtherClass(int myClass, int myItem);

    const vector<pair<vector<float>, int>> &getReducedSet() const;
};


#endif //LINEAR_SET_H