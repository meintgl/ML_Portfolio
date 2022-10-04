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
const double var(vector <double> vectorData1);
const double cor(vector <double> vectorData1, vector<double> vectorData2);
vector <double> sigmoidVector(vector <double> vectorData);
double sigmoid(double vectorData);
double calc_age_lh(double age, double mean, double variance);   
vector <double> calc_raw_prob(int pclass, int sex, double age);


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

    vector<double> probSurvived(800);
    
    vector<double> apriori(2);
    vector<double> count_survived(2);
    
    vector<double> d_pclass(3); //1x3 vector inidicating class distribution of dead titanic passengers
    vector<double> a_pclass(3); //1x3 vector inidicating class distribution of alive titanic passengers
    vector<double> d_psex(2); //1x3 vector inidicating class distribution of dead titanic passengers
    vector<double> a_psex(2); //1x3 vector inidicating class distribution of alive titanic passengers
    
    vector<double> age_mean(2);
    vector<double> age_var(2);

    vector<double> deadVector(0);
    vector<double> aliveVector(0);

    vector<double> testAge(0);
    vector<double> testSex(0);
    vector<double> testClass(0);
    vector<double> testSurvive(0);

    
 




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
    
    double dead = 0;
    double alive = 0;


//CREATING TEST DATA FOR LAST 200 or SO OBSERVATIONS

for (int i = 800; i < surviveVector.size(); i++) {
    testAge.push_back(ageVector.at(i));
    testClass.push_back(classVector.at(i));
    testSex.push_back(sexVector.at(i));
    testSurvive.push_back(surviveVector.at(i));
}


//APRIORI CALCULATION

    for (int i = 0; i < probSurvived.size(); i++) {
        if (surviveVector.at(i) == 0) {
            dead++;
        } else {
            alive++;
        }
        probSurvived.at(i) = surviveVector.at(i);

    }

    apriori.at(0) = dead/probSurvived.size();
    apriori.at(1) = alive/probSurvived.size();

    cout << endl << "P(dead) | P(survived)" << endl; 
    printVector(apriori);

//COUNT_SURVIVED

    count_survived.at(0) = dead;
    count_survived.at(1) = alive;

    cout << endl;
   cout << endl << "P(count survived) | P(count dead)" << endl; 
    printVector(count_survived);

//DEAD_C Calculation

    double deadC1 = 0;
    double deadC2 = 0;
    double deadC3 = 0;

   for (int i = 0; i < probSurvived.size(); i++) {
        if (classVector.at(i) == 1 && surviveVector.at(i) == 0) {
            deadC1++;
        } else if (classVector.at(i) == 2 && surviveVector.at(i) == 0){
            deadC2++;
        } else if (classVector.at(i) == 3 && surviveVector.at(i) == 0){
            deadC3++;
        }
       
    }
    
    /*
    cout << endl << deadC1;
    cout << endl << deadC2;
    cout << endl << deadC3;
    cout << endl << dead;
    */



    cout << endl << endl << "P(class 1 dead) | P(class 2 dead) | P(class 3 dead)"; 
    d_pclass.at(0) = deadC1/dead;
    d_pclass.at(1) = deadC2/dead;
    d_pclass.at(2) = deadC3/dead;

  

    cout << endl ;
    printVector(d_pclass);

 //ALIVE_C Calculation

    double aliveC1 = 0;
    double aliveC2 = 0;
    double aliveC3 = 0;

   for (int i = 0; i < probSurvived.size(); i++) {
        if (classVector.at(i) == 1 && surviveVector.at(i) == 1) {
            aliveC1++;
        } else if (classVector.at(i) == 2 && surviveVector.at(i) == 1){
            aliveC2++;
        } else if (classVector.at(i) == 3 && surviveVector.at(i) == 1){
            aliveC3++;
        }
       
    }

    /*
    cout << endl << aliveC1;
    cout << endl << aliveC2;
    cout << endl << aliveC3;
    cout << endl << alive;
     */



    cout <<  endl << endl << "P(class 1 alive) | P(class 2 alive) | P(class 3 alive)"; 

    a_pclass.at(0) = aliveC1/alive;
    a_pclass.at(1) = aliveC2/alive;
    a_pclass.at(2) = aliveC3/alive;

    cout << endl ;
    printVector(a_pclass);

//DEAD_C Calculation

    double deadM = 0;
    double deadF = 0;

    for (int i = 0; i < probSurvived.size(); i++) {
        if (sexVector.at(i) == 0 && surviveVector.at(i) == 0) {
            deadM++;
        } else if (sexVector.at(i) == 1 && surviveVector.at(i) == 0){
            deadF++;
        }
       
    }


    
    cout << endl << endl <<  "P(male dead) | P(female dead)"; 
    d_psex.at(0) = deadM/dead;
    d_psex.at(1) = deadF/dead;
    cout << endl;
    printVector(d_psex);

//ALIVE_C Calculation

    double aliveM = 0;
    double aliveF = 0;

    for (int i = 0; i < probSurvived.size(); i++) {
        if (sexVector.at(i) == 0 && surviveVector.at(i) == 1) {
            aliveM++;
        } else if (sexVector.at(i) == 1 && surviveVector.at(i) == 1){
            aliveF++;
        }
       
    }


    
    cout <<  endl << endl <<  "P(male survived) | P(female survived)"; 
    a_psex.at(0) = aliveM/alive;
    a_psex.at(1) = aliveF/alive;
    
    cout << endl;
    printVector(a_psex);

//AGE VECTOR Calculation

    for (int i = 0; i < probSurvived.size(); i++) {
        if (surviveVector.at(i) == 0) {
            deadVector.push_back(ageVector.at(i));
        } else if (surviveVector.at(i) == 1){
            aliveVector.push_back(ageVector.at(i));
        }
       
    }

    double deadAgeMean = vectorMean(deadVector);
    double aliveAgeMean = vectorMean(aliveVector);

    
    cout <<  endl << endl << "Mean Age Dead | Mean Age Alive"; 
    age_mean.at(0) = deadAgeMean;
    age_mean.at(1) = aliveAgeMean;
    


    cout << endl ;
    printVector(age_mean);


  

    double deadAgeVariance = var(deadVector);
    double aliveAgeVariance = var(aliveVector);

    age_var.at(0) = deadAgeVariance;
    age_var.at(1) = aliveAgeVariance;

    cout <<  endl << endl << "Var Age Dead | Var Age Alive" << endl; 
    printVector(age_var);

    cout << endl << endl;
    // printVector(age_var);

//TESTING


    // cout << endl;
    // printVector(testSex);


    double prob_survived, prob_perished = 0;
    double num_s, num_p, denominator = 0;


    vector<double> predicted(testSurvive.size());
    vector<double> survivedProb(testSurvive.size());

    for (int i = 0; i < testClass.size(); i++) {

    //calculating num_s
    num_s = a_pclass.at(testClass.at(i)-1) * a_psex.at(testSex.at(i)) * apriori.at(1) 
    * calc_age_lh(testAge.at(i), age_mean.at(1), age_var.at(1));

    //calculating num_p
    num_p = d_pclass.at(testClass.at(i)-1) * d_psex.at(testSex.at(i)) * apriori.at(0) 
    * calc_age_lh(testAge.at(i), age_mean.at(0), age_var.at(0));

    //calculating denominator
    denominator = num_s + num_p;

    prob_survived = num_s / denominator;
    prob_perished = num_p / denominator;

    survivedProb.at(i) =  prob_survived;

    

    // cout << "TEST: " << i << "  | Prob Survived: " << prob_survived << "    " << "Prob Dead: " <<  prob_perished << endl;


    }
    
    cout << "First 5 Observations Predictions (Test Data): " << endl;
    for (int i = 0; i < 5; i++) {
        cout << "Prob Survived: " << survivedProb.at(i) << "    " << "Prob Dead: " << 1 - survivedProb.at(i) << endl;
    }


    auto end = chrono::steady_clock::now();
    chrono::duration<double> elapsed_seconds = end-start;
    cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";

    for (int i = 0; i < testClass.size(); i++) {

        if(survivedProb.at(i) >=0.5) {
            predicted.at(i) = 1;
        } else {
            predicted.at(i) = 0; 
        }
    }

    double meanAccuracy = 0;

    for (int i = 0; i < predicted.size(); i++) {
         if (predicted.at(i) == testSurvive.at(i)) {
            meanAccuracy++;
         };
    }


 double truePositive = 0;
    double trueNegative = 0;
    double falsePositive = 0;
    double falseNegative = 0;


    for (int i = 0; i < predicted.size(); i++) {
         if (predicted.at(i) == 1 && testSurvive.at(i) == 1) {
            truePositive++;
         } else if (predicted.at(i) == 0 && testSurvive.at(i) == 0) {
            trueNegative++;
         } else if (predicted.at(i) == 1 && testSurvive.at(i) == 0) {
            falsePositive++;
         } else if (predicted.at(i) == 0 && testSurvive.at(i) == 1) {
            falseNegative++;
         }

    }
    
/*
    cout << "True Positive: " << truePositive << endl;
    cout << "True Negative: " << trueNegative<< endl;
    cout << "False Positive: " << falsePositive << endl;
    cout << "False Negative: " << falseNegative << endl;

*/

    double accuracy = 0;
    double sensitivity = 0;
    double specificity = 0;

    accuracy = (truePositive+trueNegative) / (truePositive + trueNegative + falsePositive + falseNegative);
    sensitivity = truePositive/(truePositive + falseNegative);
    specificity = trueNegative/ (trueNegative + falsePositive);
  
    cout << endl << "Mean Accuracy: " << (meanAccuracy / testSurvive.size());
    cout << endl << "Accuracy: " << (accuracy);
    cout << endl << "Sensitivity: " << (sensitivity);
    cout << endl << "Accuracy: " << (specificity);


}



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


//function that prints out the variance from a vector of doubles vectorData1
const double var(vector <double> vectorData1) {
    
    //mean is calculated for both vectors
    double sum, variance = 0;
    double mean1 = vectorMean(vectorData1);


    //sums the values of the result from each element of first vector minus the mean multiplied by
    //each element of the second vector minus the mean.
    // sum of (element of vector1 - mean of vector1) * (element of vector2 - mean of vector2) , then go to next element
    for (int i = 0; i < vectorData1.size(); i++) {
        sum += pow(vectorData1.at(i) - mean1, 2);
    }

    //covariance is calculated by dividing sum from amount of elements in the vector - 1
    variance = sum / (vectorData1.size() - 1);
    return variance;
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

// function that calculates the probability for a given age value from titanic data to survive.
double calc_age_lh (double age, double mean, double variance) {
    return 1 / (sqrt(2 * M_PI * variance)) * exp(-(pow((age-mean),2)) / (2 * variance));
}

//function that calculates raw probabilities through naive bayes





 