//Meinhard Capucao
// 9-10-22
// CS 4375.003

//This program reads in two columns from a .csv file into and puts them into two separate vectors of doubles
//It calculates the sum, mean, median, range of a numeric vector, and the covariance and correlation between
//two numberic vectors, then prints them all out.

#include <iostream>
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <vector>       // std::vector
#include <bits/stdc++.h> 
#include <math.h>       //for math functions such as pow, sqrt, etc.
using namespace std;

//function headers
void printVector(vector <double> vectorData);
void printStats(vector<double> vectorData);
const double vectorSum(vector <double> vectorData);
const double vectorMean(vector <double> vectorData);
const double vectorMedian(vector <double> vectorData);
const double vectorRange(vector <double> vectorData);
const double covar(vector <double> vectorData1, vector<double> vectorData2);
const double cor(vector <double> vectorData1, vector<double> vectorData2);

int main(int argc, char** argv) {
    //declaring constants for input streams. rm_in and medv_in are doubles put into vectors during input stream.
    ifstream inFS;                                 
    string line;                                    
    string rm_in, medv_in;
    const int initialLength = 0;

    //declaring a vector of doubles for first column named rm and a vector of doubles for second column named medv.
    vector<double> rm(initialLength);                     
    vector<double> medv(initialLength);          

    //opens csv file for data reading, and returns if the file can't be opened.
    cout << "Opening file Boston.csv." << endl;
    inFS.open("Boston.csv");
    if (!inFS.is_open()) {
        cout << "Could not open file Boston.csv." << endl;
        return 1;   
    }

    //reads first line which separates column header String names from the rest of the data.
    cout << "Reading Line 1" << endl;
    getline(inFS, line);
    cout << "heading: " << line << endl;
    int numObservations = 0;

    while (inFS.good()) {
        //Getting first column strings, converting it to doubles and storing it into vector rm. stops at next column
        getline(inFS, rm_in, ',');
        
        // cout << "rm: " << rm_in << " | line num: " << numObservations << endl;   //outputs 1st column data for testing
        rm.push_back(stod(rm_in));

        //Getting second column doubles, converting it to doubles and storing it into vector medv. stops at new line
        getline(inFS, medv_in, '\n');

       // cout << "medv: " << medv_in << " | line num: " << numObservations << endl; //outputs 2nd column data for testing
        medv.push_back(stod(medv_in));

        numObservations++;
    }

    //resize vectors to the total number of data read.
    rm.resize(numObservations); 
    medv.resize(numObservations);

    //printVector(rm); //test function to check contents of a vector.

    cout << "New Length: " << rm.size() << endl;
    cout << "Closing file Boston.csv." << endl;
    cout << "Number of records: " << numObservations << endl;
   
   //prints the sum, mean, median, and range for vector rm, which contains first column data in the csv file.
    cout << "\n Stats for rm" << endl;
    printStats(rm);

    //prints the sum, mean, median, and range for vector rm, which contains second column data in the csv file.
    cout << "\n Stats for medv" << endl;
    printStats(medv);

    //prints the covariance of vectors between rm and medv. 
    cout << "\n Covariance = " << covar(rm, medv) << endl;  // COVARIANCE PRINTING

    //prints the correlation of vectors between rm and medv. 
    cout << "\n Correlation = " << cor(rm, medv) << endl;   //CORRELATION PRINTING
    cout << "\nProgram terminated.";
    inFS.close();       
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