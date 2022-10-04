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