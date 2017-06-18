//
// Created by mary_mosteiro on 19.03.17.
//


#include "Utility.h"


Utility::Utility(const string &trainFile) : trainFile(trainFile) {

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









