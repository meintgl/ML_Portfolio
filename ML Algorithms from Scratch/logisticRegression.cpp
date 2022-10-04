#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <vector>       // std::vector
#include <bits/stdc++.h> 
#include <math.h>       //for math functions such as pow, sqrt, etc.
#include <chrono>        //keeping time

using namespace std;

void printVector(vector <double> vectorData);
void printStats(vector<double> vectorData);
const double vectorSum(vector <double> vectorData);
const double vectorMean(vector <double> vectorData);
const double vectorMedian(vector <double> vectorData);
const double vectorRange(vector <double> vectorData);
const double covar(vector <double> vectorData1, vector<double> vectorData2);
const double cor(vector <double> vectorData1, vector<double> vectorData2);
vector <double> sigmoidVector(vector <double> vectorData);
double sigmoid(double vectorData);

int main(int argc, char** argv) {

    auto start = chrono::steady_clock::now();
    //declaring constants for input streams. rm_in and medv_in are doubles put into vectors during input stream.
    ifstream indata;
    string survived;
    string sex;
    string line, word;
    string pclass;
    string passNum;
    string age;

    const int MAX_LEN = 2000;
    vector<double> ageVector(MAX_LEN);
    vector<double> sexVector(MAX_LEN);
    vector<double> passVector(MAX_LEN);
    vector<double> classVector(MAX_LEN);
    vector<double> surviveVector(MAX_LEN);
    
    vector<double> weightsVector(1);

    vector<double> data_matrix(800);
    vector<double> label_matrix(800);
    vector<double> probabilityVector(800);
    vector<double> error_matrix(800);
    

    
    double error = 0;
    double w0 = 0;
    double w1 = 0;
    double learningRate = 0.001;

    indata.open("titanic_project.csv");
    if (indata.is_open()){
        cout << "File is open" << endl;
    } else {
        cout << "No file was open" << endl;
    }
    getline(indata, line, '\n');
    // cout << "Heading: " << line << endl;

    int totalEntries = 0;
    int numberOfObservations = 0;
    while (indata.good()){

        getline(indata, passNum, ',');
        getline(indata, pclass, ',' );
        getline(indata, survived, ',');
        getline(indata, sex, ',');
        getline(indata, age, '\n');

        //passVector.at(numberOfObservations) = stof(passNum); "234"
        classVector.at(numberOfObservations) = stof(pclass);
        surviveVector.at(numberOfObservations) = stof(survived);
        sexVector.at(numberOfObservations) = stof(sex);
        ageVector.at(numberOfObservations) = stof(age);
        numberOfObservations++;
    }

    passVector.resize(numberOfObservations);
    ageVector.resize(numberOfObservations);
    sexVector.resize(numberOfObservations);
    classVector.resize(numberOfObservations);
    surviveVector.resize(numberOfObservations);
    
        
    weightsVector.at(0) = 1;
    for (int i = 0; i < data_matrix.size(); i++) {
        data_matrix.at(i) = sexVector.at(i);
    }

    for (int i = 0; i < label_matrix.size(); i++) {
        label_matrix.at(i) = surviveVector.at(i);
    }

    
    


for (int epochs = 0; epochs < 500; epochs++) {
    
    for (int i = 0; i < data_matrix.size(); i++) {
        probabilityVector.at(i) = sigmoid(data_matrix.at(i) * weightsVector.at(0));

        // cout << "Data Matrix at Index " << i << " :" << data_matrix.at(i) << endl;
        // cout << "   Sigmoid: " << sigmoid(data_matrix.at(i) * weightsVector.at(0)) << endl;
    }

    // printVector(probabilityVector);
    
     for (int i = 0; i < label_matrix.size(); i++) {
        error_matrix.at(i) = label_matrix.at(i) - probabilityVector.at(i);
    }

    vector<double> dataError(800);
    for (int i = 0; i < data_matrix.size(); i++) {
        dataError.at(i) = data_matrix.at(i) * error_matrix.at(i);
    } 

    weightsVector.at(0) = weightsVector.at(0) + learningRate * vectorSum(dataError);

}

   
    cout << "Weights Vector: " << weightsVector.at(0) << endl;

     auto end = chrono::steady_clock::now();
    chrono::duration<double> elapsed_seconds = end-start;
    cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";

    vector<double> test_matrix(247);
    vector<double> test_label(247);

    double menSurvived, menDead, womenSurvived, womenDead = 0;

    for (int i = 0; i < 247; i++) {
       if (surviveVector.at(i+799) == 1 && sexVector.at(i+799) == 0) {
       menSurvived++; 
       } else if (surviveVector.at(i+799) == 0 && sexVector.at(i+799) == 0) {
        menDead++; 
       }
       else if (surviveVector.at(i+799) == 1 && sexVector.at(i+799) == 1) {
       womenSurvived++;
       } else if (surviveVector.at(i+799) == 0 && sexVector.at(i+799) == 1)
        womenDead++;
    }


    cout << endl << "Training Data Statistics: " << endl << "Men Survived: " << menSurvived << endl;
    cout << "Men Died: " << menDead<< endl;
    cout << "Women Survived: " << womenSurvived << endl;
    cout << "Women Died: " << womenDead << endl;


     
    for (int i = 0; i < 247; i++) {
       test_matrix.at(i) = sexVector.at(i+799);
    }
       for (int i = 0; i < 247; i++) {
        test_label.at(i) = surviveVector.at(i+799);
    }

     vector<double> predicted(247);
     vector<double> probabilities(247);
     vector<double> predictions(247);


      for (int i = 0; i < test_matrix.size(); i++) {
        predicted.at(i) = test_matrix.at(i) * weightsVector.at(0);
    }



    
    


     for (int i = 0; i < probabilities.size(); i++) {
        probabilities.at(i) = exp(predicted.at(i)) / (1 + exp(predicted.at(i)));
    }



     for (int i = 0; i < predictions.size(); i++) {
        if (probabilities.at(i) >= 0.5) {
            predictions.at(i) = 1;
        } else {
            predictions.at(i) = 0;
        }
    }

  double meanAccuracy = 0;
    for (int i = 0; i < predictions.size(); i++) {
         if (predictions.at(i) == test_label.at(i)) {
            meanAccuracy++;
         };
    }


    double truePositive = 0;
    double trueNegative = 0;
    double falsePositive = 0;
    double falseNegative = 0;


    for (int i = 0; i < predictions.size(); i++) {
         if (predictions.at(i) == 1 && test_label.at(i) == 1) {
            truePositive++;
         } else if (predictions.at(i) == 0 && test_label.at(i) == 0) {
            trueNegative++;
         } else if (predictions.at(i) == 1 && test_label.at(i) == 0) {
            falsePositive++;
         } else if (predictions.at(i) == 0 && test_label.at(i) == 1) {
            falseNegative++;
         }

    }
    



    cout << endl << "Correctly Predicted Survive: " << truePositive << endl;
    cout << "Correctly Predicted Died: " << trueNegative<< endl;
    cout << "Incorrectly Predicted Survived: " << falsePositive << endl;
    cout << "Incorrectly Predicted Died " << falseNegative << endl;



    double accuracy = 0;
    double sensitivity = 0;
    double specificity = 0;

    accuracy = (truePositive+trueNegative) / (truePositive + trueNegative + falsePositive + falseNegative);
    sensitivity = truePositive/(truePositive + falseNegative);
    specificity = trueNegative/ (trueNegative + falsePositive);
  
     cout << endl << "Accuracy: " << (accuracy);
     cout << endl << "Sensitivity: " << (sensitivity);
     cout << endl << "Specificity: " << (specificity);
    


    // printVector(probabilityVector);

    indata.close();
    return 0;

    //declaring a vector of doubles for first column named rm and a vector of doubles for second column named medv.
        
    //opens csv file for data reading, and returns if the file can't be opened.

    return 0;



}


//function that prints out the contentss of a vector of doubles.
void printVector(vector <double> vectorData) {
   for (int i = 0; i < vectorData.size(); i++) {
        cout << vectorData.at(i) << ' ';
    }
}

//function that prints out the sum, mean, median, and range of a numeric vector of doubles.
void printStats(vector<double> vectorData) {
    double sum = vectorSum(vectorData);
    cout << "Sum: " << sum << endl;

    double mean = vectorMean(vectorData);
    cout << "Mean: " << mean << endl;

    double median = vectorMedian(vectorData);
    cout << "Median: " << median << endl;

    double range = vectorRange(vectorData);
    cout << "Range: " << range << endl;
}

//function that prints out the sum of all values from a numeric vector of doubles.
const double vectorSum(vector <double> vectorData) {
    double sum = 0;
    for (int i = 0; i < vectorData.size(); i++) {
        sum += vectorData.at(i);
    }
    return sum;
}

//function that prints out the mean of all values from a numeric vector of doubles.
const double vectorMean(vector <double> vectorData) {
    double sum = vectorSum(vectorData);

    //the mean is calculated from the sum of the numeric vector divided by the total number of elements.
    double mean = sum/vectorData.size();
    return mean;
}

//function that prints out the median  of a numeric vector of doubles.
const double vectorMedian(vector <double> vectorData) {
    //the vector is sorted in ascending order so that the median can be found by getting the middle index.
    sort(vectorData.begin(), vectorData.end());
    double median = vectorData.at(vectorData.size()/2);
    return median;
}

//function that prints out the total range of numbers from a numeric vector of doubles.
const double vectorRange(vector <double> vectorData) {
     //the vector is sorted so that the range can be found by subtracting the maximum from the minimum value.
    sort(vectorData.begin(), vectorData.end());
    double range = vectorData.at(vectorData.size()- 1) - vectorData.at(0);
    return range;
}




//function that prints out the covariance two numeric vector of doubles, vectorData1 and vectorData2.
const double covar(vector <double> vectorData1, vector<double> vectorData2) {
    
    //mean is calculated for both vectors
    double sum, covariance = 0;
    double mean1 = vectorMean(vectorData1);
    double mean2 = vectorMean(vectorData2);

    //sums the values of the result from each element of first vector minus the mean multiplied by
    //each element of the second vector minus the mean.
    // sum of (element of vector1 - mean of vector1) * (element of vector2 - mean of vector2) , then go to next element
    for (int i = 0; i < vectorData1.size(); i++) {
        sum += (vectorData1.at(i) - mean1) * (vectorData2.at(i) - mean2);
    }

    //covariance is calculated by dividing sum from amount of elements in the vector - 1
    covariance = sum / (vectorData1.size() - 1);
    return covariance;
}


//function that prints out the correlation of two numeric vector of doubles, vectorData1 and vectorData2.
const double cor(vector <double> vectorData1, vector<double> vectorData2) {

    //mean is calculated from both vectors.
    double varianceX, varianceY, stDevX, stDevY, correlation = 0;
    double mean1 = vectorMean(vectorData1);
    double mean2 = vectorMean(vectorData2);
    

    //calculates the variance of vectorData1 and vectorData2 separately by getting the sum of all elements minus
    //the mean of each respective vector, then squaring the result.
    // sum of (element of vector1/vector2 - mean of vector1/vector2)^2
    for (int i = 0; i < vectorData1.size(); i++) {
        varianceX += pow((vectorData1.at(i) - mean1), 2);
        varianceY += pow((vectorData2.at(i) - mean2), 2);
    }

    //calcualtes stdev of vectorData1 and vectorData2 by squaring the variance of each vector.
    varianceX = varianceX / (vectorData1.size() - 1);
    varianceY = varianceY / (vectorData2.size() - 1);
    stDevX = sqrt(varianceX);
    stDevY = sqrt(varianceY);

    //correlation is returned by calculating the covariance of vectorData1 and vectorData2 divided by
    //the product of both vectors standard deviations.
    return ((covar(vectorData1, vectorData2)) / (stDevX * stDevY));
}

// function that calculates the sigmoid values of a vector, then outputs it out as a new vector with corresponding indexes.
vector <double> sigmoidVector(vector <double> vectorData) {
    const int vectorSize  = vectorData.size();
    vector <double> newData(vectorSize);

    for (int i = 0; i <= vectorSize; i++) {
            newData[i] = 1 / (1 + exp(-vectorData[i]));
    }
return newData;
}

double sigmoid(double vectorIndex) {
    double value = vectorIndex;
    vectorIndex = 1 / (1 + exp(-value));
    return vectorIndex;
    }

 





