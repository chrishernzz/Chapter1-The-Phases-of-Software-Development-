#include "DescriptiveStatistics.h"
#include<algorithm>

//precondition: going to call my vector data and its bool function 
//postcondition: going to check if its empty
bool DescriptiveStatistics::isEmpty() const{
    return data.empty();
}
//precondition: going to have a parameter that reads the file
//postcondition: going to open the file and read from the file, then print out the data, sorted them out
void DescriptiveStatistics::readDate(string& fileName){
    ifstream readFile;
    //if there is file, remove it so it opens a new file
           //remove(filename.c_str());
    if (readFile.is_open()) {
        readFile.close();
    }
    //clear the data so it does add the other data
    data.clear();
    double theValues = 0.0;
    //opening the file to read from
    readFile.open(fileName, ios::in);

    //IF file does not open(exits)
    if (readFile.fail()) {
        cout << "\n\t\tERROR: File " << fileName << ", cannot be found.\n\n";
        cout << endl;
        system("pause");
        system("cls");
        return;
    }
    if (readFile.is_open()) {
        //while file does not fail(the end of the file) loop
        while (!readFile.fail()) {
            //read the file
            if (readFile >> theValues) {
                //push back the values in the data
                data.push_back(theValues);
            }
            else {
                //clear the file if it has strings or chars
                readFile.clear();
                string invalidValue;
                //reading it, then ignore it
                readFile >> invalidValue;
            }
        }
    }
    //get the size of the data
    cout << "\n\t\tData set with " << data.size() << " data: \n\t\t{ ";
    //sorting the data first
    sort(data.begin(), data.end());
    for (double i : data) {
        cout << i << ", ";
    }
    cout << "}";
    cout << "\n\n";
    system("pause");
    system("cls");
}
//precondition: going to pass in an argu that accepts the filename
//postcondition: going to then make sure to close the file;
void DescriptiveStatistics::closeFile(string& filename){
    ifstream readFile;
    readFile.close();
}

//precondition: going to return the minimum
//postcondition: going to call the .front() since its sorted, will read the first  number
double DescriptiveStatistics::getMin() const{
    
    return data.front();
}
//precondition: going to call the maximum
//postcondition: going to call the .back() since its sorted, will return the max(last element in data)
double DescriptiveStatistics::getMax() const{
    return data.back();
}

//precondition: going to get the range
//postcondition: going to call the .functions getMax() and getMin() and subtract 
double DescriptiveStatistics::getRange() const{
    //calling the functions to get the range
    return getMax() - getMin();
}
//precondition: going to get the size
//precondition: going to return the size of the vector
double DescriptiveStatistics::getSize() const{
    return data.size();
}
//precondition: going to get the sum
//postcondition: going to look at the data and return the sum 
double DescriptiveStatistics::getSum() const{
    double sum = 0.0;
    //go through the data 
    for (double i : data) {
        //going to be adding to get the sum
        sum += i;
    }
    return sum;
}
//precondition: going to get the mean
//postcondition: going to call my getSum() function and divide it by the getSize() function
double DescriptiveStatistics::getMean() const{
    double mean;
    //calling getSum function that has the sum then divide the numbers there is in the data
    mean = getSum() / getSize();

    return mean;
}
//precondition: going to get the median of the vector
//postcondition: going to find the firstsize and second size, return the median
double DescriptiveStatistics::getMedian() const{
    double medianNum;

    //going to retreive the first index 
    double firstSize = data[getSize() / 2.0];
    //going to retreive the second index and subtract 1.0 so it can look at the index before
    double secondSize = data[getSize() / 2.0 - 1.0];
    //if its not the remainder of 0, run this if statement
    if (data.size() % 2 != 0) {
        //going to get the data size then divide and remainder it is
        //that is our index; data[index]
        medianNum = data[getSize() / 2.0];
    }
    //else if remainder(even)
    else {
        //adding the two index then divide it by 2.0
        medianNum = (firstSize + secondSize) / 2.0;
    }
    return medianNum;
}
//precondition: going to create a map that can get the freq
//postcondition: going to use the .count() to find the word, and the .at() to return and increment when it seen more than once
map<double, double> DescriptiveStatistics::repeatedFreq() const{
    //using map to get the key(value) we are looking for
    map<double, double> repeated;
   
    //print the data values(going to be sorted)
    for (double i : data) {
        //.count() is checking if it exits in the map container
        if (repeated.count(i)) {
            //increment the number if seen more than ones
            repeated.at(i)++;
        }
        else {
            //using .emplace to check if the value exits, if yes then it does nothing
            repeated.emplace(i, 1);
        }
    }
    return repeated;
    cout << "\n\t\tFrequency Table";
    cout << "\n\t\t\tValue\tFrequency\tFrequency %";

}
//precondition: displaying the information
//postcondition: going to call the repeatedFreq() function so it can read how many times it frequencies
void DescriptiveStatistics::displayFreq() const{
    map<double, double> display = repeatedFreq();
    for (auto& words : display) {
        //going to get the freq, divide how many times it repeats by the total values in the data, then multiply 100
        double freq = (words.second / data.size()) * 100.0;
        cout << "\n\t\t\t" << words.first << "\t" << words.second << "\t\t" << freq;
    }
}
//precondition: creating a map that can check the modes, doubles 
//postcondition: going to check if there is duplicates, if yes then return and if more than one then return both
map<double, double> DescriptiveStatistics::repeatedModes() const{
    map<double, double> duplicates;
    double maxValue = 0.0, maxCount = 0.0, modeCount = -1.0;
    for (double i : data) {
        //.count() is checking if it exits in the map container
        if (duplicates.count(i)) {
            //increment the number if seen more than ones
            duplicates.at(i)++;
        }
        else {
            //using .emplace to check if the value exits, if yes then it does nothing
            duplicates.emplace(i, 1);
        }
    }
    //going to go through the vector and check each number
    for (auto& number : duplicates) {
        //if the pair is greater than
        if (number.second > maxValue) {
            maxValue = number.second;
        }
    }
    //print the numbers with the max
    for (auto& numbers : duplicates) {
        if (numbers.second == maxValue) {
            cout << numbers.first << ", ";
        }
    }
    return duplicates;
}
//precondition: going to get the standard deviation
//postcondition: going to use the getMean() function and then sqrt and return the value
double DescriptiveStatistics::getStandardDeviation() const{
    double squaredSum = 0.0;
    for (double i : data) {
        //going to use the pow(lets me square), add all the numbers in the data, call the getMean(mean) function
        squaredSum += pow(i - getMean(), 2.0);
    }
    //going to then get the square sum and divide it by the size - 1 since thats the formula
    double totalDev = squaredSum / (getSize() - 1);
    double standardDev = sqrt(totalDev);

    return standardDev;
}
//precondition: going to get the variance 
//postcondition: going to use the getMean() function, totalVar will return and subtract the getSize() by 1
double DescriptiveStatistics::getVariance() const{
    double varSquare = 0.0;
    for (double i : data) {
        //this is my sum of squares
        varSquare += pow(i - getMean(), 2.0);
    }
    //going to then get the square sum and divide it by the size - 1(n-1)
    double totalVar = varSquare / (getSize() - 1);
    return totalVar;
}
//precondition: going to get the the mid range 
//postcondition: going to use the getMin() and getMax() functions to add then divide by 2
double DescriptiveStatistics::getMidRange() const{
    return (getMin() + getMax())/ 2.0;
}
//precondition: going to get the first quartile 
//postcondition: going to use the getSize() to divide by 4 so the vector divide by 4 and then return the data[index]
double DescriptiveStatistics::getFirstQuartile() const{
    //find the q1
    int lowerHalfSize = getSize() / 4; 

    if (data.size() % 4 == 0) {
        // If the total number of elements is divisible by 4, take the average of two middle elements
        return (data[lowerHalfSize - 1] + data[lowerHalfSize]) / 2.0;
    }
    else {
        //if not divisible by 4, simply return the middle element of the lower half
        return data[lowerHalfSize];
    }
}
//precondition: going to get the third quartile 
//postcondition: going to use the getSize() to multiply by 3 and divide by 4 then return the data[index]
double DescriptiveStatistics::getThirdQuartile() const{
    //find the q3
    int upperHalfSize = 3 * getSize() / 4;

    if (data.size() % 4 == 0) {
        //if the total number of elements is divisible by 4, take the average of two middle elements
        return (data[upperHalfSize - 1] + data[upperHalfSize]) / 2.0;
    }
    else {
        //if not divisible by 4, simply return the middle element of the upper half
        return data[upperHalfSize];
    }
}
//precondition: going to get the the range of the quartile 
//postcondition: going to call the getThirdQuartile() and getFirstQuartile() fuction to subtarct and return range
double DescriptiveStatistics::getInterquartileRange() const{
    return getThirdQuartile() - getFirstQuartile();
}
//precondition: going to get the outliers
//postcondition: going to use the getSize() to divide by 4 so the vector divide by 4 and then return the data[index]
void DescriptiveStatistics::outliers() const{
    double firstQuartileValue = getFirstQuartile();
    double thirdQuartileValue = getThirdQuartile();
    double interquartileRange = getInterquartileRange();
    double lowerBound = firstQuartileValue - 1.5 * interquartileRange;
    double upperBound = thirdQuartileValue + 1.5 * interquartileRange;
    bool hasOutLiers = false;

    for (int i = 0; i < data.size(); ++i) {
        if (data[i] < lowerBound || data[i] > upperBound) {
            cout << data[i] << " ";
            hasOutLiers = true;
        }
    }
    if (!hasOutLiers) {
        cout << "none";
    }
}
//precondition: going to get the sum of square
//postcondition: going to call the getMean() function, then return the sum squares by taking the power of 2
double DescriptiveStatistics::getSumSquares() const{
    double sumSquares = 0.0;
    for (double i : data) {
        //using the pow function to square the difference
        sumSquares += pow(i - getMean(), 2);
    }
    return sumSquares;
}
//precondition: going to get the mean absolute devaiton
//postcondition: going to call the getMean() and getSize() so it can return the abosulte
double DescriptiveStatistics::getMeanAbsoluteDeviation() const{
    double totalAbs = 0.0;
    for (double i : data) {
        //have to get the absolute value of each individual and subtract by the mean
        totalAbs += abs(i - getMean());
    }
    //divide by the size(how many number we have)
    double absolute = totalAbs / getSize();
    return absolute;
}
//precondition: going to get the root mean square
//postcondition: going to get the sum and take the power of 2, then sqrt the sum and divide by the getSize() function
double DescriptiveStatistics::getRootMeanSquare() const{
    double sum = 0.0, totalRoot = 0.0;
    //go through the data 
    for (double i : data) {
        //going to be adding to get the sum
        sum += pow(i, 2);
    }
    //sqrt the sum and divide it by the data(numbers)
    totalRoot = sqrt((sum / getSize()));
    return totalRoot;
}
//precondition: going to get the stand error of the mean
//postcondition: going to call the getStandardDeviation() function and divid it by the getSize() function 
double DescriptiveStatistics::getStandardErrorOfTheMean() const{
    //going to call the deviation and square the size of vec
    double totalStand = getStandardDeviation() / sqrt(getSize());
    return totalStand;
}
//precondition: going to get the coef of variation
//postcondition: going to call the getStandaradDeviation() function then divide by the getMean() function and return
double DescriptiveStatistics::getCoefficientOfVariation() const{
    double totalCoef = getStandardDeviation() / getMean();
    return totalCoef;
}
//precondition: going to get the rel stand devi
//postcondition: going to call the getStandaradDeviation() function times 100 then divide by the getMean() function and return total
double DescriptiveStatistics::getRelativeStandardDeviation() const{
    double totalRelStaDev = (getStandardDeviation() * 100.0) / getMean();
    return totalRelStaDev;
}
//precondition: going to pass is an string parameter to get the file to write
//postcondition: going to then return the information and write to the file we want it to
void DescriptiveStatistics::displayFileWrite(string& ouputFileName) const{
    ofstream writeFile;
    //open file to write to
    writeFile.open(ouputFileName, ios::out);
    map<double, double> tempModes;
    double maxValue = 0.0, maxCount = 0.0, modeCount = -1.0;
    for (double i : data) {
        //.count() is checking if it exits in the map container
        if (tempModes.count(i)) {
            //increment the number if seen more than ones
            tempModes.at(i)++;
        }
        else {
            //using .emplace to check if the value exits, if yes then it does nothing
            tempModes.emplace(i, 1);
        }
    }
    double skewnessTotal = 0.0;
    for (double i : data) {
        //using the power to the third, already have the mean and standardDev
        skewnessTotal += pow((i - getMean()) / getStandardDeviation(), 3.0);
    }
    //calculating the total now
    skewnessTotal *= (data.size() * 1.0) / ((data.size() - 1.0) * (data.size() - 2.0));
    double sumFourthMoment = 0;
    for (double value : data) {
        sumFourthMoment += pow(value - getMean(), 4);
    }
    double kurtosis = sumFourthMoment / (getSize()* getStandardDeviation() * getStandardDeviation() * getStandardDeviation() * getStandardDeviation());
    double kurtosisExcess = kurtosis - 3;

    if (writeFile.is_open()) {
        writeFile << "\n\t\t\tDescriptive Statistics: \n";
        writeFile << "\n\t\t\tData set with " << data.size() << " data: \n\t\t\t{ ";
        for (double i : data) {
            writeFile << i << ", ";
        }
        writeFile << "}";
        writeFile << "\n";
        writeFile << "\n\t\t\tMinimum \t\t\t= " << getMin() << "\n";
        writeFile << "\n\t\t\tMaximum \t\t\t= " << getMax() << "\n";
        writeFile << "\n\t\t\tRange \t\t\t\t= " << getRange() << "\n";
        writeFile << "\n\t\t\tSize \t\t\t\t= " << getSize() << "\n";
        writeFile << "\n\t\t\tSum \t\t\t\t= " << getSum() << "\n";
        writeFile << "\n\t\t\tMean \t\t\t\t= " << getMean() << "\n";
        writeFile << "\n\t\t\tMedian \t\t\t\t= " << getMedian() << "\n";
       for (auto& number : tempModes) {

            if (number.second > maxValue) {
                maxValue = number.second;
            }
        }
        writeFile << "\n\t\t\tModes \t\t\t\t= ";
        
        for (auto& numbers : tempModes) {
            if (numbers.second == maxValue) {
                writeFile << numbers.first << ", ";
            }
        }
        writeFile << "\n";
        writeFile << "\n\t\t\tStandard Deviation \t\t= " << getStandardDeviation() << "\n";
        writeFile << "\n\t\t\tVariance \t\t\t= " << getVariance() << "\n";
        writeFile << "\n\t\t\tMid Range \t\t\t= " << getMidRange()<< "\n";
        writeFile << "\n\t\t\tQuartiles \n\t\t\t\t\t\t";
        writeFile << "Q1 --> " << getFirstQuartile() << "\n\t\t\t\t\t\t";
        writeFile << "Q2 --> " << getMedian() << "\n\t\t\t\t\t\t";
        writeFile << "Q3 --> " << getThirdQuartile() << "\n";
        writeFile << "\n\t\t\tInterquartile Range \t\t= " << getInterquartileRange() << "\n";
        writeFile << "\n\t\t\tOutLiers \t\t\t= ";
        double firstQuartileValue = getFirstQuartile();
        double thirdQuartileValue = getThirdQuartile();
        double interquartileRange = getInterquartileRange();
        double lowerBound = firstQuartileValue - 1.5 * interquartileRange;
        double upperBound = thirdQuartileValue + 1.5 * interquartileRange;
        for (int i = 0; i < data.size(); ++i) {
            if (data[i] < lowerBound || data[i] > upperBound) {
                writeFile << data[i] << " ";
            }
            else {
                writeFile << "none";
                break;
            }
        }
        writeFile << "\n";
        writeFile << "\n\t\t\tSum of Squares \t\t\t= " << getSumSquares() << "\n";
        writeFile << "\n\t\t\tMean Absolute Deviation \t= " << getMeanAbsoluteDeviation() << "\n";
        writeFile << "\n\t\t\tRoot Mean Square \t\t= " << getRootMeanSquare() << "\n";
        writeFile << "\n\t\t\tStandard Error of the Mean \t= " << getStandardErrorOfTheMean() << "\n";
        writeFile << "\n\t\t\tSkweness \t\t\t= " << skewnessTotal << "\n";
        writeFile << "\n\t\t\tKurtosis \t\t\t= "<< kurtosis<<"\n";
        writeFile << "\n\t\t\tKurtosis Excess \t\t= " << kurtosisExcess <<"\n";
        writeFile << "\n\t\t\tCoefficient of Variation \t= " << getCoefficientOfVariation() << "\n";
        writeFile << "\n\t\t\tRelative Standard Deviation \t= " << getRelativeStandardDeviation() << "%\n";
        writeFile << "\n\t\t\tFrequency Table";
        writeFile << "\n\t\t\t\tValue\tFrequency\tFrequency %";
        displayFreqWrite(writeFile);
    }
    //closing file
    writeFile.close();
}
//precondition: going to get the display information
//postcondition: going to return all the information that is needed to read
void DescriptiveStatistics::displayInformation() const{
    map<double, double> tempModes;
    double maxValue = 0.0, maxCount = 0.0, modeCount = -1.0;
    for (double i : data) {
        //.count() is checking if it exits in the map container
        if (tempModes.count(i)) {
            //increment the number if seen more than ones
            tempModes.at(i)++;
        }
        else {
            //using .emplace to check if the value exits, if yes then it does nothing
            tempModes.emplace(i, 1);
        }
    }
    double skewnessTotal = 0.0;
    for (double i : data) {
        //using the power to the third, already have the mean and standardDev
        skewnessTotal += pow((i - getMean()) / getStandardDeviation(), 3.0);
    }
    //calculating the total now
    skewnessTotal *= (data.size() * 1.0) / ((data.size() - 1.0) * (data.size() - 2.0));

    double sumFourthMoment = 0;
    for (double value : data) {
        sumFourthMoment += pow(value - getMean(), 4);
    }
    double kurtosis = sumFourthMoment / (getSize() * getStandardDeviation() * getStandardDeviation() * getStandardDeviation() * getStandardDeviation());
    double kurtosisExcess = kurtosis - 3;

    cout << "\n\t\tDescriptive Statistics: ";
    cout << "\n\n\t\tDate set with " << getSize() << " data: \n\t\t{ ";
    for (double i : data) {
        cout << i << ", ";
    }
    cout << "}";
    cout << "\n\n\t\tMinimum \t\t\t= " << getMin();
    cout << "\n\n\t\tMaximum \t\t\t= " << getMax();
    cout << "\n\n\t\tRange \t\t\t\t= " << getRange();
    cout << "\n\n\t\tSize \t\t\t\t= " << getSize();
    cout << "\n\n\t\tSum \t\t\t\t= " << getSum();
    cout << "\n\n\t\tMean \t\t\t\t= " << getMean();
    cout << "\n\n\t\tMedian \t\t\t\t= " << getMedian();

    for (auto& number : tempModes) {
        if (number.second > maxValue) {
            maxValue = number.second;
        }
    }
    cout << "\n\n\t\tMode \t\t\t\t= ";
    for (auto& numbers : tempModes) {
        if (numbers.second == maxValue) {
            cout << numbers.first << ", ";
        }
    }
    cout << "\n\n\t\tStandard Deviation \t\t= " << getStandardDeviation();
    cout << "\n\n\t\tVariance \t\t\t= " << getVariance();
    cout << "\n\n\t\tMid Range \t\t\t= " << (data.front() + data.back()) / 2.0;
    cout << "\n\n\t\tQuartiles \n\t\t\t\t\t";
    cout << "Q1 --> " << getFirstQuartile() << "\n\t\t\t\t\t";
    cout << "Q2 --> " << getMedian() << "\n\t\t\t\t\t";
    cout << "Q3 --> " << getThirdQuartile();
    cout << "\n\n\t\tInterquartile Range \t\t= " << getInterquartileRange();
    cout << "\n\n\t\tOutliers \t\t\t= ";
    outliers();
    cout << "\n\n\t\tSum of Squares \t\t\t= " << getSumSquares();
    cout << "\n\n\t\tMean Absolute Deviation \t= " << getMeanAbsoluteDeviation();
    cout << "\n\n\t\tRoot Mean Square \t\t= " << getRootMeanSquare();
    cout << "\n\n\t\tStandard Error of the Mean \t= " << getStandardErrorOfTheMean();
    cout << "\n\n\t\tSkweness \t\t\t= " << skewnessTotal;
    cout << "\n\n\t\tKurtosis \t\t\t= "<< kurtosis;
    cout << "\n\n\t\tKurtosis Excess \t\t= " << kurtosisExcess;
    cout << "\n\n\t\tCoefficient of Variation \t= " << getCoefficientOfVariation();
    cout << "\n\n\t\tRelative Standard Deviation \t= " << getRelativeStandardDeviation() << "%";
    cout << "\n\n\t\tFrequency Table";
    cout << "\n\t\t\tValue\tFrequency\tFrequency %";
    displayFreq();
}
//precondition: going to make a display function to write too
//postcondition: going to write in the file, it is the same thing as a void but this time accepts the file we want to write to
void DescriptiveStatistics::displayFreqWrite(ostream& writeToFile) const{
    map<double, double> display = repeatedFreq();
    writeToFile << "\n\t\t\t\tValue\tFrequency\tFrequency %";
    for (const auto& words : display) {
        double freq = (words.second / data.size()) * 100.0;
        writeToFile << "\n\t\t\t\t" << words.first << "\t" << words.second << "\t\t" << freq;
    }
}
