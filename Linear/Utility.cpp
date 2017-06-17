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
            out<<setprecision(5) <<setw(12) << left<<v[i][j];
        }
        out<< endl;
    }
}

int Utility::getIndexMax(vector<float> v){
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

int Utility::classifyNewItem(vector<float> item, Set trainSet){
    vector<float> value(trainSet.getNumClasses(),0);

    for(int noClass=0; noClass < trainSet.getNumClasses(); ++noClass){
        for(int noFeature = 0; noFeature < trainSet.getNumFeatures(); ++noFeature){
            value[noClass] += trainSet.getStandardWeights()[noClass][noFeature]*item[noFeature];
        }
    }
    for(int noClass=0; noClass < trainSet.getNumClasses(); ++noClass){
        value[noClass] -=  trainSet.getWeight_i()[noClass];
    }

    return Utility::getIndexMax(value);
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






