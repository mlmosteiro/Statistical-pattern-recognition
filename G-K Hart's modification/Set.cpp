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

float Set::calculateDistance(vector<float> x, vector<float> y){
    vector<float> tmp (x.size(),0);
    float distance = 0;

    for(int i =0; i<x.size(); i++){
        tmp[i]= x[i] - y[i];
    }
    for(int i=0; i<tmp.size(); i++){
        tmp[i] = tmp[i]*tmp[i];
    }
    for (int i=0; i<tmp.size(); i++){
        distance += tmp[i];
    }

    return sqrt(distance);
}

pair<vector<float>,pair<int,int>> Set::minDistFromSet(pair<vector<float>,pair<int,int>>item, vector<pair<vector<float>,pair<int,int>>>set){
    int id = 0;
    float minDistance = calculateDistance(item.first,set[0].first);
    float distance;
    for(int i = 0; i < set.size(); i++){
        distance = calculateDistance(item.first, set[i].first);
        if(distance < minDistance){
            minDistance = distance;
            id = i;
        }
    }
    return set[id];
}

float Set::calculateMinDistanceToOtherClass (int myClass, int myItem){
    float distance = numeric_limits<float>::max();
    float tmpDist = 0;
    for(int noClass=0; noClass < standardItems.size(); ++noClass){
        if(myClass!= noClass){
            for(int noItem =0; noItem<standardItems[noClass].size(); ++noItem){
                tmpDist = calculateDistance(standardItems[noClass][noItem], standardItems[myClass][myItem]);
                if(tmpDist < distance){
                    distance = tmpDist;
                }
            }
        }
    }
    return  distance;
}

int Set::calculateMutualDistance(int myClass, int myItem){
    float minDistanceOtherClass  = calculateMinDistanceToOtherClass(myClass, myItem);
    int md = 0;
    for(int noItem = 0; noItem<standardItems[myClass].size(); ++noItem){
        if(calculateDistance(standardItems[myClass][noItem],standardItems[myClass][myItem]) < minDistanceOtherClass){
            md++;
        }
    }
    return md;

}

bool pairCompare(const pair<vector<float>, pair<int, int>>& firstElem, const pair<vector<float>, pair<int,int>>& secondElem) {
    return firstElem.second.second <= secondElem.second.second;

}

void Set::calculateReducedSet(){
    vector<pair<vector<float>,pair<int,int>>> sortedData;
    vector<pair<vector<float>,pair<int,int>>> tmpReducedSet;

    for( int noClass = 0; noClass < standardItems.size(); noClass++) {//para cada clase
        for (int noItem = 0; noItem < standardItems[noClass].size(); noItem++) { //para cada item
            sortedData.push_back(pair<vector<float>, pair<int,int>>(standardItems[noClass][noItem], pair<int,int>(noClass,calculateMutualDistance(noClass, noItem))));
        }
    }

    sort(sortedData.begin(), sortedData.end(), pairCompare);
    tmpReducedSet.push_back( sortedData[0]);

    bool adding = true;
    int iterations = 1;

    while( adding){
        adding = false;
        vector<pair<vector<float>,pair<int,int>>>::iterator itemIter;

        for(itemIter = sortedData.begin(); itemIter != sortedData.end(); ++itemIter){
            pair<vector<float>,pair<int,int>> p = minDistFromSet(*itemIter,tmpReducedSet);
            if(p.second.first != (*itemIter).second.first){
                tmpReducedSet.push_back(*itemIter);
                sortedData.erase(itemIter);
                adding = true;
            }
        }

        cout << "Iteration: "<< iterations <<" Number of elements in the reduce set: " << tmpReducedSet.size()<< endl;
        iterations++;

    }

    vector<pair<vector<float>,pair<int,int>>>::iterator iterator;
    for(iterator = tmpReducedSet.begin(); iterator != tmpReducedSet.end(); ++iterator){
        pair<vector<float>,int>realObject((*iterator).first,(*iterator).second.first);
        reducedSet.push_back(realObject);
    }

    reducedSetToFile();
}

const vector<pair<vector<float>, int>> &Set::getReducedSet() const {
    return reducedSet;
}

void Set::reducedSetToFile(){

    ofstream dataOutputFile;
    dataOutputFile.open("ReducedData.txt");

    dataOutputFile<<numClasses << " " << numFeatures << " "<< reducedSet.size()<<endl;

    for(int noItem = 0; noItem<reducedSet.size(); ++noItem){
        dataOutputFile<< reducedSet[noItem].second<< " ";
        for(int noFeature = 0; noFeature<reducedSet[noItem].first.size(); ++noFeature){
            dataOutputFile<<setprecision(5)<< reducedSet[noItem].first[noFeature] << " ";
        }
        dataOutputFile<<endl;
    }

    dataOutputFile.close();
}