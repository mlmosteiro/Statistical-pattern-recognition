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

public:
    Set(){};

    int getNumClasses() const;

    void setNumClasses(int numClasses);

    void setNumItems(int numItems);

    void setNumFeatures(int numFeatures);

    void setItems(const vector<vector<vector<float>>> &items);

    const vector<vector<float>> &getUnclasifiedItems() const;

    void setUnclasifiedItems(const vector<vector<float>> &unclasifiedItems);

    const vector<vector<float>> &getGravityCenters() const;

    const vector<vector<float>> &getStandardGravityCenters() const;

    const vector<vector<float>> &getWeights() const;

    const vector<vector<float>> &getStandardWeights() const;

    void resizeVectors();

    void calculateGravityCenter();

    void calculateAverage();

    void calculateStandardDeviation();

    void calculateStandardGravityCenter();

    void doStandardisation();

    void calculateWeights();

    void calculateStandardWeights();

    void calculateWeight_i(vector<vector<float>> gravityCenters, vector<float> deviations, vector<float> average);

    const vector<vector<vector<float>>> &getStandardItems() const;

    vector<float> doStandardisationToItem(vector<float> item);
};


#endif //LINEAR_SET_H
