#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<fstream>
#include<cmath>
using namespace std;

//precondition: going to create the class that has the information of stats
//postcondition: going to then create vector STL that holds the data in a file, then make functions that does the math
class DescriptiveStatistics {
private:
	//will hold the data that is in the files
	vector<double> data;
public:
	//defautl constructor
	DescriptiveStatistics() = default;

	//checking if data is empty
	bool isEmpty() const;

	void readDate(string& fileName);
	//closing file
	void closeFile(string& filename);

	double getMin() const;
	double getMax() const;
	double getRange() const;
	double getSize() const;
	double getSum() const;
	double getMean() const;
	double getMedian() const;
	//using map to keep track of the frequency
	map<double, double> repeatedFreq() const;
	//display the frequencies
	void displayFreq() const;
	//using map to keep track of the modes
	map<double, double> repeatedModes() const;
	double getStandardDeviation() const;
	double getVariance() const; 
	double getMidRange() const;

	//find first Quartile
	double getFirstQuartile() const; 
	//find third Quartile
	double getThirdQuartile() const;
	//getting the range
	double getInterquartileRange() const; 
	void outliers() const;
	double getSumSquares() const;
	double getMeanAbsoluteDeviation() const;
	double getRootMeanSquare() const;
	double getStandardErrorOfTheMean() const;
	double getCoefficientOfVariation() const;
	double getRelativeStandardDeviation() const;
	//display the file information 
	void displayFileWrite(string& writeFile) const;
	void displayInformation() const;
	void displayFreqWrite(ostream& writeToFile) const;
};

