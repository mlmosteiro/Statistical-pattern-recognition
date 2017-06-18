//
// Created by mary_mosteiro on 19.03.17.
//

#include "Set.h"
#include "Utility.h"

int Set::getNumClasses() const {
    return numClasses;
}

void Set::setNumClasses(int numClasses) {
    Set::numClasses = numClasses;
}

void Set::setNumItems(int numItems) {
    Set::numItems = numItems;
}

void Set::setNumFeatures(int numFeatures) {
    Set::numFeatures = numFeatures;
}

void Set::setItems(const vector<vector<vector<float>>> &items) {
    Set::items = items;
}

const vector<vector<float>> &Set::getUnclasifiedItems() const {
    return unclasifiedItems;
}

void Set::setUnclasifiedItems(const vector<vector<float>> &unclasifiedItems) {
    Set::unclasifiedItems = unclasifiedItems;
}

const vector<vector<float>> &Set::getGravityCenters() const {
    return gravityCenters;
}

const vector<vector<float>> &Set::getStandardGravityCenters() const {
    return standardGravityCenters;
}

const vector<vector<float>> &Set::getWeights() const {
    return weights;
}

const vector<vector<float>> &Set::getStandardWeights() const {
    return standardWeights;
}

void Set::resizeVectors() {
    items.resize(numClasses);
    standardItems.resize(numClasses);
    gravityCenters.resize(numClasses);
    standardGravityCenters.resize(numClasses);
    weights.resize(numClasses);
    standardWeights.resize(numClasses);
    weight_i.resize(numClasses);
    average.resize(numFeatures);
    standarDeviation.resize(numFeatures);
}

void Set::calculateGravityCenter() {
    for (int noClass = 0; noClass < items.size(); ++noClass) {
        gravityCenters[noClass].resize(numFeatures);
        for (int noItem = 0; noItem < items[noClass].size(); noItem++) {
            for (int noFeature = 0; noFeature < items[noClass][noItem].size(); noFeature++) {
                gravityCenters[noClass][noFeature] += items[noClass][noItem][noFeature];
            }
        }
    }
    for (int noClass = 0; noClass < numClasses; ++noClass) {
        for (int noFeature = 0; noFeature < numFeatures; noFeature++) {
            gravityCenters[noClass][noFeature] /= items[noClass].size();
        }
    }
}

void Set::calculateStandardGravityCenter() {
    for (int noClass = 0; noClass < standardItems.size(); ++noClass) {
        standardGravityCenters[noClass].resize(numFeatures);
        for (int noItem = 0; noItem < standardItems[noClass].size(); noItem++) {
            for (int noFeature = 0; noFeature < standardItems[noClass][noItem].size(); noFeature++) {
                standardGravityCenters[noClass][noFeature] += standardItems[noClass][noItem][noFeature];
            }
        }
    }
    for (int noClass = 0; noClass < numClasses; ++noClass) {
        for (int noFeature = 0; noFeature < numFeatures; noFeature++) {
            standardGravityCenters[noClass][noFeature] /= standardItems[noClass].size();
        }
    }
}

void Set::calculateAverage() {
    for (int noClass = 0; noClass < items.size(); ++noClass) {
        for (int noItem = 0; noItem < items[noClass].size(); ++noItem) {
            for (int noFeature = 0; noFeature < items[noClass][noItem].size(); ++noFeature) {
                average[noFeature] += items[noClass][noItem][noFeature];
            }
        }
    }

    for (int i = 0; i < average.size(); ++i) {
        average[i] /= numItems;
    }
}

void Set::calculateStandardDeviation() {

    //Varianzas
    for (int noClase = 0; noClase < items.size(); ++noClase) {
        for (int noItem = 0; noItem < items[noClase].size(); ++noItem) {
            for (int noFeature = 0; noFeature < items[noClase][noItem].size(); ++noFeature) {
                standarDeviation[noFeature] += pow(items[noClase][noItem][noFeature] - average[noFeature], 2);
            }
        }
    }

    //Desviaciones
    for (int position = 0; position < numFeatures; ++position) {
        standarDeviation[position] /= numItems;
        standarDeviation[position] = sqrt(standarDeviation[position]);
        //cout<< standarDeviationVector[position] << " ";
    }
}

void Set::doStandardisation() {

    for (int noClass = 0; noClass < items.size(); ++noClass) {
        for (int noItem = 0; noItem < items[noClass].size(); ++noItem) {
            vector<float> aux;
            for (int noFeature = 0; noFeature < items[noClass][noItem].size(); ++noFeature) {
                aux.push_back((items[noClass][noItem][noFeature] - average[noFeature]) / standarDeviation[noFeature]);
            }
            standardItems[noClass].push_back(aux);
        }
    }
}

vector<float>  Set::doStandardisationToItem(vector<float> item) {
    vector<float> standardItems;
    float aux;
    for (int noFeature = 0; noFeature < item.size(); ++noFeature) {
        aux=((item[noFeature] - average[noFeature]) / standarDeviation[noFeature]);
        standardItems.push_back(aux);
    }
    return  standardItems;
}

void Set::calculateStandardWeights() {
    for (int noClass = 0; noClass < standardGravityCenters.size(); noClass++) {
        standardWeights[noClass].resize(numFeatures);
        for (int noFeature = 0; noFeature < standardGravityCenters[noClass].size(); noFeature++) {
            standardWeights[noClass][noFeature] += 2 * standardGravityCenters[noClass][noFeature] / standarDeviation[noFeature];
        }
    }

    calculateWeight_i(standardGravityCenters,standarDeviation,average);
}

void Set::calculateWeights() {
    for (int noClass = 0; noClass < standardGravityCenters.size(); noClass++) {
        weights[noClass].resize(numFeatures);
        for (int noFeature = 0; noFeature < standardGravityCenters[noClass].size(); noFeature++) {
            weights[noClass][noFeature] += 2 * standardGravityCenters[noClass][noFeature];
        }
    }
}

void Set::calculateWeight_i(vector<vector<float>> gravityCenters, vector<float> deviations, vector<float> average){
    vector<float> secondTerm (numClasses,0);

    for(int noClass=0; noClass<numClasses; ++noClass){
        for(int noFeature = 0; noFeature<numFeatures; ++noFeature){
            weight_i[noClass] += 2*gravityCenters[noClass][noFeature]*average[noFeature] / deviations[noFeature];
            secondTerm[noClass] += gravityCenters[noClass][noFeature] * gravityCenters[noClass][noFeature];
        }
    }

    for(int noClass=0; noClass<numClasses; ++noClass){
        weight_i[noClass] += secondTerm[noClass];
    }
}

const vector<vector<vector<float>>> &Set::getStandardItems() const {
    return standardItems;
}
