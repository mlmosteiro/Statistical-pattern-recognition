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

void Utility::print2DVector(vector<vector<float>>v){
    for(int i = 0; i<v.size(); ++i){
        for(int j = 0; j<v[i].size(); j++){
            cout<<setprecision(5) <<setw(12) << left<<v[i][j];
        }
        cout<< endl;
    }
}

class PairCompare {
private:
    vector<float> item;
public:
    PairCompare(vector<float> p) : item(p){}

    bool operator()(const pair<vector<float>,int> &p1, const pair<vector<float>,int> &p2) {
        return Utility::calculateDistance(p1.first, item) < Utility::calculateDistance(p2.first, item);
    }
};

int Utility::classifyNewItem(vector<float> item, Set trainSet){
    vector<pair<float,int>> distances; //Value, Class
    vector<float> standardItem = trainSet.doStandardisationToItem(item);
    vector<pair<vector<float>,int>> tmp(trainSet.getReducedSet());

    sort(tmp.begin(),tmp.end(), PairCompare(standardItem));

    return tmp.begin()->second;
}

Utility::~Utility() {
    out.close();
}

float Utility::calculateDistance(vector<float> x, vector<float> y) {
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





