//
// Created by mary_mosteiro on 19.03.17.
//


#include "Utility.h"


Utility::Utility(const string &trainFile, const string &testFile) : testFile(testFile), trainFile(trainFile) {
    out.open(outFileString,ios_base::out);
}

void Utility::split(const string &s, char c, vector<string> &v) {
    string::size_type i = 0;
    string::size_type j = s.find(c);

    while (j != string::npos) {
        v.push_back(s.substr(i, j - i));
        i = ++j;
        j = s.find(c, j);

        if (j == string::npos)
            v.push_back(s.substr(i, s.length()));
    }
}

Set Utility::readTrainFile() {
    fstream inputFile;
    string line;
    vector<string> data;
    vector<vector<vector<float>>> items;
    Set newSet;

    inputFile.open(trainFile.c_str(), ios::in);
    if (inputFile.is_open()) {
        getline(inputFile, line);
        split(line, ',', data);
        newSet.setNumClasses(stoi(data[0]));
        newSet.setNumFeatures(stoi(data[1]));
        newSet.setNumItems(stoi(data[2]));

        items.resize(newSet.getNumClasses());

        while (!inputFile.eof()) {
            vector<string> stringData;
            vector<float> points;
            getline(inputFile, line);
            split(line, ',', stringData);
            transform(stringData.begin() + 1, stringData.end(), back_inserter(points),
                      [](const string &astr) { return stof(astr); });
            items[stoi(stringData[0]) - 1].push_back(points);

        }

        newSet.setItems(items);
        inputFile.close();

    } else cout << "Fichero inexistente o faltan permisos para abrirlo" << endl;

    return newSet;
}

Set Utility::readTestFile() {
    fstream inputFile;
    string line;
    vector<string> data;
    vector<vector<float>> items;
    Set newSet;


    inputFile.open(testFile.c_str(), ios::in);
    if (inputFile.is_open()) {
        getline(inputFile, line);
        split(line, ',', data);
        newSet.setNumClasses(stoi(data[0]));
        newSet.setNumFeatures(stoi(data[1]));
        newSet.setNumItems(stoi(data[2]));

        while (!inputFile.eof()) {
            vector<string> stringData;
            vector<float> points;
            getline(inputFile, line);

            split(line, ',', stringData);
            transform(stringData.begin() + 1, stringData.end(), back_inserter(points),
                      [](const string &astr) { return stof(astr); });
            points.push_back(stoi(stringData[0]));
            items.push_back(points);
        }

        newSet.setUnclasifiedItems(items);
        inputFile.close();
    } else cout << "Fichero inexistente o faltan permisos para abrirlo" << endl;
    return newSet;

}

void Utility::print1DVector(vector<float>v){
    for(int i = 0; i<v.size(); ++i){
            out<<v[i]<<"\t ";
        }
    out<< endl;
}

void Utility::print2DVector(vector<vector<float>>v){
    for(int i = 0; i<v.size(); ++i){
        for(int j = 0; j<v[i].size(); j++){
            cout<<setprecision(5) <<setw(12) << left<<v[i][j];
        }
        cout<< endl;
    }
}

int Utility::getIndexMax(vector<int> v){
    float max = v[0];
    int index = 0;
    for(int i=0; i<v.size(); ++i){
        if(v[i]>max){
            max=v[i];
            index=i;
        }
    }
    return index;
}

float Utility:: calculateDistance(vector<float> x, vector<float> y){
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

// This function returns true if the first pair is "less"
// than the second one according to some metric
// In this case, we say the first pair is "less" if the first element of the first pair
// is less than the first element of the second pair
bool pairCompare(const pair<float, int>& firstElem, const pair<float, int>& secondElem) {
    return firstElem.first < secondElem.first;

}


int Utility::classifyNewItem(vector<float> item, Set trainSet, int kNN){
    vector<pair<float,int>> distances; //Value, Class
    vector<float> standardItem = trainSet.doStandardisationToItem(item);

    for (int noClass=0; noClass<trainSet.getNumClasses(); ++noClass){
        for (int noItem=0; noItem<trainSet.getStandardItems()[noClass].size(); ++noItem){
            distances.push_back(make_pair(calculateDistance(trainSet.getStandardItems()[noClass][noItem],standardItem),noClass));
        }
    }
    sort(distances.begin(), distances.end(),pairCompare);


    vector<int> results(trainSet.getNumClasses(),0);
    for(int i=0; i<kNN; ++i){
        results[distances[i].second]++;
    }

    return Utility::getIndexMax(results)+1;
}

void Utility::outln(string s){
    out<<s<<endl;
}

const string &Utility::getOutFileString() const {
    return outFileString;
}

Utility::~Utility() {
    out.close();
}






