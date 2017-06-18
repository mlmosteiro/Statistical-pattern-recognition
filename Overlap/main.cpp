#include "Utility.h"

Set train(Utility& utility){
    Set trainSet = utility.readTrainFile();
    cout<<"Summary of the set:" << endl;
    cout<<"Number of classes: "<< trainSet.getNumClasses()<<endl<<endl;
    cout<<"Number of items: "<< trainSet.getNumItems()<<endl;
    cout<<"Number of features: "<< trainSet.getNumFeatures()<<endl<<endl;;

    trainSet.resizeVectors();
    trainSet.calculateAverage();
    trainSet.calculateStandardDeviation();
    trainSet.doStandardisation();

    return trainSet;
}


int main (int argc, char *argv[]) {
    if(argc<2){
        cout <<"Use the following format:\n "<< argv[0]<<" <nameOfFile>";
        return EXIT_FAILURE;
    }

    Utility utility(argv[1]);
    Set trainSet = train(utility);
    trainSet.checkOverlap();

    return EXIT_SUCCESS;
}