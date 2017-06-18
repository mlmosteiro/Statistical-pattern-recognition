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

float Set:: calculateDistance(vector<float> x, vector<float> y){
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

float Set::minDistToSameClassObject(int idClass,int idItem){
    float maxDist = calculateDistance(standardItems[idClass][idItem], standardItems[idClass][(idItem+1)%standardItems[idClass].size()]);
    float dist;
    for( int i = 0; i < standardItems[idClass].size(); i++){
        dist = calculateDistance(standardItems[idClass][idItem],standardItems[idClass][i]);
        if( dist < maxDist and idItem != i){
            maxDist = dist;
        }
    }
    return maxDist;
}

vector<float> Set::setMaxMinDist(){

    vector<float> maxMinValues = vector < float >(standardItems.size(),0);
    for( int idClass = 0; idClass < standardItems.size(); idClass++){
        float dist;
        for(int idItem = 0; idItem < standardItems[idClass].size();idItem++){
            dist = this->minDistToSameClassObject(idClass,idItem);
            if(dist > maxMinValues[idClass]){
                maxMinValues[idClass] = dist;
            }
        }
    }
    return maxMinValues;
}

void Set::checkOverlap () {

    vector<bool> overlappedItems;
    vector<float> maxMinDistances = setMaxMinDist();
    int countItems = 0;
    int overlapedRate = 0;

    cout << setw(10) << left << "NoItem" << setw(10) << left << "Class" << setw(10) << left <<"A"<< setw(10) << left <<"B" <<setw(10) << left<<"C"<<endl;
    for (int noClass = 0; noClass < standardItems.size(); ++noClass) {
        for (int noItem = 0; noItem < standardItems[noClass].size(); ++noItem) {
            countItems++;
            overlappedItems = vector<bool>(standardItems.size(), 0);
            for (int iClass = 0; iClass < standardItems.size(); ++iClass) {
                for (int iObject = 0;
                     iObject < standardItems[iClass].size() and not overlappedItems[iClass]; ++iObject) {
                    if (calculateDistance(standardItems[noClass][noItem], standardItems[iClass][iObject]) <
                        maxMinDistances[iClass] or noClass == iClass) {
                        overlappedItems[iClass] = true;
                    }
                }
            }

            cout << setw(10) << left << countItems << setw(10) << left << noClass + 1 << setw(10) << left;
            int votes = 0;
            for(int o = 0; o < standardItems.size(); o++){
                if(overlappedItems[o]){
                    cout << "1" << setw(10) << left;
                    votes++;
                    if(votes == 2){
                        overlapedRate++;
                    }
                }
                else{
                    cout << "0" << setw(10) << left;;
                }
            }
            cout << endl;
        }
    }
    cout << "Overlapping rate: " << overlapedRate*1.0/(countItems-1);
}

int Set::getNumItems() const {
    return numItems;
}

int Set::getNumFeatures() const {
    return numFeatures;
}
