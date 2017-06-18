#include "Utility.h"

//TODO: Nothing :D
vector<vector<float>> getMatrixP( vector<vector<float>>& matrixR){
    vector<vector<float>> matrixP (3, vector<float> (3,0));
    vector<float> m(3,0);
    for(int i=0; i<matrixR.size(); i++){
        for(int j=0; j<matrixR.size(); j++){
            m[i]+=matrixR[i][j];
        }
    }

    for(int i=0; i<matrixR.size(); i++){
        for(int j=0; j<matrixR.size(); j++){
            matrixP[i][j] = matrixR[i][j]/m[i];
        }
    }
    return  matrixP;
}

vector<vector<float>> getMatrixQ( vector<vector<float>>& matrixR){
    vector<vector<float>> matrixQ (3, vector<float> (3,0));
    vector<float> m(3,0);
    for(int i=0; i<matrixR.size(); i++){
        for(int j=0; j<matrixR.size(); j++){
            m[i]+=matrixR[j][i];
        }
    }

    for(int i=0; i<matrixR.size(); i++){
        for(int j=0; j<matrixR.size(); j++){
            matrixQ[i][j] = matrixR[j][i]/m[i];
        }
    }
    return  matrixQ;
}

Set train(Utility& utility){
    Set trainSet = utility.readTrainFile();

    trainSet.resizeVectors();
    trainSet.calculateAverage();
    trainSet.calculateStandardDeviation();
    trainSet.doStandardisation();
    trainSet.calculateReducedSet();

    return trainSet;
}

int main (int argc, char *argv[]) {
    if(argc<3){
        cout <<"Use the following format:\n "<< argv[0]<<" <nameOfTrainFile> <nameOfTestFile>";
        return EXIT_FAILURE;
    }

    Utility utility(argv[1],argv[2]);
    float error = 0;
    vector<vector<float>> matrixR (3, vector<float> (3,0));


    Set trainSet = train(utility);
    Set testSet = utility.readTestFile ();
    vector<vector<float>>unClasItems = testSet.getUnclasifiedItems();


    for(int unclasItem = 0; unclasItem<unClasItems.size();++unclasItem){
        int itemClass = utility.classifyNewItem(unClasItems[unclasItem],trainSet);
        int realClass =  (int)unClasItems[unclasItem].back();
        cout<< setw(10) << left  << unclasItem << setw(10) << left << itemClass+1 << setw(10) << left << realClass;
        if(itemClass+1 != realClass){
            error++;
            cout<< setw(12) << left <<"WRONG!";
        }
        cout<<endl;

        matrixR[realClass-1][itemClass]++;
    }

    cout<<"\nPorcentaje de error: "<< error*100/testSet.getUnclasifiedItems().size()<<endl;

    cout<<"\nMatrix R:" <<endl;
    utility.print2DVector(matrixR);

    cout<<"\nMatrix P:" <<endl;
    utility.print2DVector(getMatrixP(matrixR));

    cout<<"\nMatrix Q:" <<endl;
    utility.print2DVector(getMatrixQ(matrixR));


    return EXIT_SUCCESS;
}

