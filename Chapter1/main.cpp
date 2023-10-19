//name: Christian Hernandez
//date: 9/2/2023
//subscription: CMPR131

#include<iostream>
#include"input (1).h"
#include<vector>
#include<map>
#include<fstream>
#include<iomanip>
#include<cmath>
#include"DescriptiveStatistics.h"
using namespace std;

//Prototypes
int menuOption();
void challenge1();
void challenge2();
void challenge3();

int main()
{
    do{
        switch (menuOption()){
        case 0: exit(1); break;
        case 1: challenge1(); break;
        case 2: challenge2(); break;
        case 3: challenge3(); break;
        default: cout << "\t\tERROR - Invalid option. Please re-enter."; break;
        }
        cout << "\n";
        system("pause");

    } while (true);

    return EXIT_SUCCESS;
}

//precondition: making a menu option
//postcondition: it will return an int (the choice of the menu)
int menuOption()
{
	system("cls");
	cout << "\n\tCMPR131 - Chapter 1 Software Development by Christian Hernandez(9/2/2023)";
	cout << "\n\t" << string(78, char(205));
	cout << "\n\t\t1> ASCII Text To ASCII Numbers";
	cout << "\n\t\t2> Base Converter";
    cout << "\n\t\t3> Descriptive Statistics";
    cout << "\n\t" << string(78, char(205));
	cout << "\n\t\t0> Exit";
	cout << "\n\t" << string(78, char(205));
	//calling the input.h and we are inputting numbers from 0 through 8
	return inputInteger("\n\t\tOption: ", 0, 3);
}

//precondition: going to create a vector(STL) 
//postcondition: while using the vector, I'm going to get text line and turn to ASCII then write and read in binary
void challenge1()
{
    system("cls");
    char option;
    string textLine;
    //convert the word using STL Vector
    vector<int> ascii;
    //file name
    string fileName = "test.bin";
    //opening the file to write and read
    fstream writingAndRedingInBinary;
    do {
        beginning:
        cout << "\n\t1> - ASCII Text To ASCII Numbers";
        cout << "\n\t" << string(78, char(205));
        cout << "\n\t\tA> Enter a text string";
        cout << "\n\t\tB> Convert the text string to ASCII numbers";
        cout << "\n\t\tC> Save the converted ASCII numbers into a binary file";
        cout << "\n\t\tD> Read the binary file";
        cout << "\n\t" << string(78, char(205));
        cout << "\n\t\t0> return";
        cout << "\n\t" << string(78, char(205))<<"\n";
        option = inputChar("\t\tOption: ", (static_cast<string>("ABCD0")));

        switch (toupper(option)) {

        case 'A': {
            //if there is file, remove it so it opens a new file
            remove(fileName.c_str());
            //if its not empty
            if (!textLine.empty()) {
                //clear the ascii values
                ascii.clear();
            }
            cout << "\n\t\tEnter a text line: ";
            //going to use getline to get spaces 
            getline(cin,textLine);
            cout << "\n";
            system("pause");
            system("cls");
        }
                break;
        case 'B': {
            //checking if its empty(no word entered)
            if (textLine.empty()) {
                cout << "\n\t\tERROR: empty input text.\n\n";
                system("pause");
                system("cls");
                goto beginning;
            }
            //clear the ascii values so it does not keep pushing them
            ascii.clear();
            //ranged base loop to look for each character
            for (char c : textLine) {
                //going to push back the elements to the back
                //use static cast to convert the index[c](char) to an int
                ascii.push_back(static_cast<int>(c));
            }
            cout << "\n\t\tConverted to ASCII numbers:\n ";
            cout << "\t\t";
            //now print the values in the ascii
            for (int i : ascii) {
                cout << " " << i;
            }
            cout << "\n\n";
            system("pause");
            system("cls");
        }
                break;
        case 'C': {
            //checking if its empty(no word entered)
            if (ascii.empty()) {
                cout << "\n\t\tERROR: empty binary text.\n\n";
                system("pause");
                system("cls");
                goto beginning;
            }
            //going to be opening the file then writing to it
            writingAndRedingInBinary.open(fileName, ios::out | ios::binary);
           
			for (int i : ascii) {
				writingAndRedingInBinary.write(reinterpret_cast<char*>(&i), sizeof(int));
			}
			//closing the file
			writingAndRedingInBinary.close();
            cout << "\n\t\tFile, "<< fileName <<", has been written and saved.\n\n";
            system("pause");
            system("cls");
        }
                break;
        case 'D': {
            int num;
            //opening the file to read from
            writingAndRedingInBinary.open(fileName, ios::in | ios::binary);
            
            //check if the file exists 
            if (writingAndRedingInBinary.is_open()) {
                //clearing so it does not reapeat the same ascii numbers
                ascii.clear();
                //while it does not fail(end of the file)
				while (!writingAndRedingInBinary.fail()) {
                    //reading the file
					writingAndRedingInBinary.read(reinterpret_cast<char*>(&num), sizeof(int));
                    //prevents from printing an extra letter
                    if (writingAndRedingInBinary.fail()) {
                        break;
                    }
                    //pushback the num(read from the file)
					ascii.push_back(num);
				}
                //closing the file
                writingAndRedingInBinary.close();
				cout << "\n\t\tReading file, " << fileName << "...\n\t\t";
				for (int i : ascii) {
					cout << " " << i;
				}
                cout << "\n\n";
            }
            else {
                cout << "\n\t\tERROR: Cannot open file, " << fileName << ".\n\n";
            }
            system("pause");
            system("cls");
        }
                break;
        case '0': {
            return;
        }

        }
    } while (true);
}

//precondition: going to create a vector(STL)
//postcondition: going to create two vector classes, first one that holds the values, and the second one for temporary to display values
void challenge2()
{
    system("cls");
    char option;
    string baseChars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int baseNum, targetBase;
    bool check = false;
    int num = 0;
    //convert the values using Vector STL
    vector<char> values;
    do {
        
        beginning:
		cout << "\n\t2> - Base Converter";
		cout << "\n\t" << string(78, char(205));
		cout << "\n\t\tA> Enter an integer number (base 10)";
		cout << "\n\t\tB> Specify and converting base";
		cout << "\n\t\tC> Display all converted bases (2..36)";
		cout << "\n\t" << string(78, char(205));
		cout << "\n\t\t0> return";
		cout << "\n\t" << string(78, char(205)) << "\n";
		option = inputChar("\t\tOption: ", (static_cast<string>("ABC0")));

        switch (toupper(option)) {
        case 'A': {
            //going to clear the vec so it does not keep adding them
            if (!values.empty()) {
                values.clear();
            }
            baseNum = inputInteger("\n\t\tEnter an integer number of base 10: ");
            //num will hold the baseNum input number
            num = baseNum;
            check = true;
            cout << "\n\n";
            system("pause");
            system("cls");
        }
                break;
        case 'B': {
            //if there are no numbers error
            if (!check) {
                cout << "\n\t\tERROR: No input integer has been entered.\n\n";
                system("pause");
                system("cls");
                goto beginning;
            }
            //going to clear the vec so it does not keep adding them
            if (!values.empty()) {
                values.clear();
            }
            int absNum = abs(baseNum);
            targetBase = inputInteger("\n\t\tEnter the base (2..36) to convert to: ", 2, 36);
            //will hold the data of the baseNum(turn negative number to positive)
            int tempNum1 = absNum;
            while (tempNum1 > 0) {
                //getting the modoulo of the baseNum and the targetBase
                int remainder = tempNum1 % targetBase;
                //going to call the baseCars that has our information and putting it in array that grabs me the remainder
                values.insert(values.begin(), baseChars[remainder]);
                //will help me get 0
                tempNum1 /= targetBase;
            }
            //print out the values
            cout << "\n\t\t" << num << " (base of 10) = ";
            for (char i : values) {
                cout << i << "";
                
            }
            //if base is 2, its binary
            if (targetBase == 2) {
                cout << " (base of 2 - binary)";
            }
            //else if its octal
            else if (targetBase == 8) {
                cout << " (base of 8 - octal)";
            }
            //else if its hex
            else if (targetBase == 16) {
                cout << " (base of 16 - hex)";
            }
            //else its just the base
            else{
                cout << " (base of " << targetBase << ")";
            }
            
            cout << "\n\n";
            system("pause");
            system("cls");
        } 
                break;
        case 'C': {
            //if there are no numbers error
            if (!check) {
                cout << "\n\t\tERROR: No input integer has been entered.\n\n";
                system("pause");
                system("cls");
                goto beginning;
            }
            //turning negative number back to a positive
            int absNum = abs(num);
            cout << "\n\t\t" << num << " (base of 10) = \n";
            for (int base = 2; base <= 36; ++base) {
                //creating another vec to hold the new values
                vector<char> valuesTemp;
                //this temp will hold the baseNum, since num is equal to the baseNum(input valid)
                int tempNum2 = absNum;
                while (tempNum2 > 0) {
                    //get remainder
                    int numberRem = tempNum2 % base;
                    //insert each of the values to the data
                    valuesTemp.insert(valuesTemp.begin(), baseChars[numberRem]);
                    //will help me get 0
                    tempNum2 /= base;
                }
                //print out the values
                cout << "\t\t\t";
                for (char digit : valuesTemp) {
                    cout << digit;
                }
                //if base is 2, its binary
                if (base == 2) {
                    cout << " (base of " << base << " - binary)";
                }
                //else if its octal
                else if (base == 8) {
                    cout << " (base of " << base << " - octal)";
                }
                //else if its hex
                else if (base == 16) {
                    cout << " (base of " << base << " - hex)";
                }
                //else its just the base
                else {
                    cout << " (base of " << base << ")";
                }
                cout << endl;
            }
            cout << "\n\n";
            system("pause");
            system("cls");
        }
                break;
        case '0': {
            return;
        }
        }

    } while (true);
}


//precondition: going to call my class, in the class it has the vector(STL)
//postcondition: going to then read from that information in the class, vector is private, then access the information
void challenge3()
{
    system("cls");
    char option;
    string filename;
    DescriptiveStatistics stats;
    do {
        beginning:
        cout << "\n\t3> - Descriptive Statistics";
        cout << "\n\t" << string(78, char(205));
        cout << "\n\t\tA> Read data file, store into a sorted dynamic array and display the data set";
        cout << "\n\t\tB> Minimum" <<"\t\t\tM> Mid Range";
        cout << "\n\t\tC> Maxium" <<"\t\t\tN> Quartiles";
        cout << "\n\t\tD> Range" <<"\t\t\tO> Interquartile Range";
        cout << "\n\t\tE> Size" <<"\t\t\t\tP> Outliers";
        cout << "\n\t\tF> Sum" <<"\t\t\t\tQ> Sum of Squares";
        cout << "\n\t\tG> Mean" <<"\t\t\t\tR> Mean Absoulte Deviation";
        cout << "\n\t\tH> Median" <<"\t\t\tS> Root Mean Square";
        cout << "\n\t\tI> Frequencies" <<"\t\t\tT> Standard Error of the Mean";
        cout << "\n\t\tJ> Mode"<<"\t\t\t\tU> Coefficient of Variation";
        cout << "\n\t\tK> Standard Deviation"<<"\t\tV> Relative Standard Deviation";
        cout << "\n\t\tL> Variance";
        cout << "\n\t\tW> Display all results and write to an output text file";
        cout << "\n\t" << string(78, char(205));
        cout << "\n\t\t0> return";
        cout << "\n\t" << string(78, char(205)) << "\n";
        option = inputChar("\t\tOption: ", static_cast<string>("ABCDEFGHIJKLWMNOPQRSTUV0"));

        switch (toupper(option)) {
        case 'A': {
            cout << "\n\t\tEnter a data file name: ";
            getline(cin, filename);
            stats.readDate(filename);
        }
                break;
        case 'B': {
            if (stats.isEmpty()) {
                cout << "\n\t\tERROR: Data set is empty.\n\n";
                system("pause");
                system("cls");
                goto beginning;
            }
			//since sorted, going to get the front(first) data for the min
			cout << "\n\t\tMinimum \t\t\t= " << stats.getMin();
			cout << "\n\n";
			system("pause");
			system("cls");
        }
                break;
        case 'C': {
            if (stats.isEmpty()) {
                cout << "\n\t\tERROR: Data set is empty.\n\n";
                system("pause");
                system("cls");
                goto beginning;
            }
			//since sorted, going to get the front(first) data for the min
			cout << "\n\t\tMaximum \t\t\t= " << stats.getMax();
			cout << "\n\n";
			system("pause");
			system("cls");
        }
                break;
        case 'D': {
            if (stats.isEmpty()) {
                cout << "\n\t\tERROR: Data set is empty.\n\n";
                system("pause");
                system("cls");
                goto beginning;
            }
            //since sorted, going to get the front(first) data for the min
            cout << "\n\t\tRange \t\t\t= " << stats.getRange();
            cout << "\n\n";
            system("pause");
            system("cls");
        }
                break;
        case 'E': {
            if (stats.isEmpty()) {
                cout << "\n\t\tERROR: Data set is empty.\n\n";
                system("pause");
                system("cls");
                goto beginning;
            }
            //going to get the size of the data(how many is there)
            cout << "\n\t\tSize \t\t\t= " << stats.getSize();
            cout << "\n\n";
            system("pause");
            system("cls");
        }
                break;
        case 'F': {
            if (stats.isEmpty()) {
                cout << "\n\t\tERROR: Data set is empty.\n\n";
                system("pause");
                system("cls");
                goto beginning;
            }
            cout << "\n\t\tSum \t\t\t= " << stats.getSum();
            cout << "\n\n";
            system("pause");
            system("cls");
        }
                break;
        case 'G': {
            if (stats.isEmpty()) {
                cout << "\n\t\tERROR: Data set is empty.\n\n";
                system("pause");
                system("cls");
                goto beginning;
            }
            cout << "\n\t\tMean \t\t\t= "<<stats.getMean();
            cout << "\n\n";
            system("pause");
            system("cls");
        }
                break;
        case 'H': {
            if (stats.isEmpty()) {
                cout << "\n\t\tERROR: Data set is empty.\n\n";
                system("pause");
                system("cls");
                goto beginning;
            }
            cout << "\n\t\tMedian \t\t\t= " << stats.getMedian();
            cout << "\n\n";
            system("pause");
            system("cls");
        }
                break;
        case 'I': {
            if (stats.isEmpty()) {
                cout << "\n\t\tERROR: Data set is empty.\n\n";
                system("pause");
                system("cls");
                goto beginning;
            }
            stats.repeatedFreq();
            cout << "\n\t\tFrequency Table";
            cout << "\n\t\t\tValue\tFrequency\tFrequency %";
            stats.displayFreq();
            cout << "\n\n";
            system("pause");
            system("cls");
        }
                break;
        case 'J': {
            if (stats.isEmpty()) {
                cout << "\n\t\tERROR: Data set is empty.\n\n";
                system("pause");
                system("cls");
                goto beginning;
            }
            cout << "\n\t\tMode \t\t\t= ";
            stats.repeatedModes();
            cout << "\n\n";
            system("pause");
            system("cls");
        }
                break;
        case 'K': {
            if (stats.isEmpty()) {
                cout << "\n\t\tERROR: Data set is empty.\n\n";
                system("pause");
                system("cls");
                goto beginning;
            }
            cout << "\n\t\tStandard Deviation \t\t\t= " << stats.getStandardDeviation();
            cout << "\n\n";
            system("pause");
            system("cls");
        }
                break;
        case 'L': {
            if (stats.isEmpty()) {
                cout << "\n\t\tERROR: Data set is empty.\n\n";
                system("pause");
                system("cls");
                goto beginning;
            }
            cout << "\n\t\tVariance \t\t\t= " << stats.getVariance();
            cout << "\n\n";
            system("pause");
            system("cls");
        }
                break;
        case 'W': {
            if (stats.isEmpty()) {
                cout << "\n\t\tERROR: Data set is empty.\n\n";
                system("pause");
                system("cls");
                goto beginning;
            }
            string fileName;
            stats.displayInformation();
            cout << "\n\n\t\tEnter an ouput file name: ";
            getline(cin, fileName);
            stats.displayFileWrite(fileName);
            cout << "\n\n";
            system("pause");
            system("cls");
        }
                break;
        case 'M': {
            if (stats.isEmpty()) {
                cout << "\n\t\tERROR: Data set is empty.\n\n";
                system("pause");
                system("cls");
                goto beginning;
            }
            //calculating the mid range, min + max then divide
            cout << "\n\t\tMidRange \t\t\t= " << stats.getMidRange();
            cout << "\n\n";
            system("pause");
            system("cls");
        }
                break;
        case 'N': {
            if (stats.isEmpty()) {
                cout << "\n\t\tERROR: Data set is empty.\n\n";
                system("pause");
                system("cls");
                goto beginning;
            }
            cout << "\n\t\tQuartiles \n\t\t\t\t";
            cout << "Q1 --> " << stats.getFirstQuartile() << "\n\t\t\t\t";
            cout << "Q2 --> " << stats.getMedian() << "\n\t\t\t\t";
            cout << "Q3 --> " << stats.getThirdQuartile();

            cout << "\n\n";
            system("pause");
            system("cls");
        }
                break;
        case 'O': {
            if (stats.isEmpty()) {
                cout << "\n\t\tERROR: Data set is empty.\n\n";
                system("pause");
                system("cls");
                goto beginning;
            }
            cout << "\n\t\tInterquartile Range \t\t= " << stats.getInterquartileRange();
            cout << "\n\n";
            system("pause");
            system("cls");
        }
                break;
        case 'P': {
            if (stats.isEmpty()) {
                cout << "\n\t\tERROR: Data set is empty.\n\n";
                system("pause");
                system("cls");
                goto beginning;
            }
            cout << "\n\t\tOutliers \t\t= ";
            stats.outliers();
            cout << "\n\n";
            system("pause");
            system("cls");
        }
                break;
        case 'Q': {
            if (stats.isEmpty()) {
                cout << "\n\t\tERROR: Data set is empty.\n\n";
                system("pause");
                system("cls");
                goto beginning;
            }
            cout << "\n\t\tSum of Squares \t\t\t= " << setprecision(5)<< fixed<< stats.getSumSquares();
            cout << "\n\n";
            system("pause");
            system("cls");
        }
                break;
        case 'R': {
            if (stats.isEmpty()) {
                cout << "\n\t\tERROR: Data set is empty.\n\n";
                system("pause");
                system("cls");
                goto beginning;
            }
            cout << "\n\t\tMean Absolute Deviation \t\t= " << stats.getMeanAbsoluteDeviation();
            cout << "\n\n";
            system("pause");
            system("cls");
        }
                break;
        case 'S': {
            if (stats.isEmpty()) {
                cout << "\n\t\tERROR: Data set is empty.\n\n";
                system("pause");
                system("cls");
                goto beginning;
            }
            cout << "\n\t\tRoot Mean Square \t\t= " << stats.getRootMeanSquare();
            cout << "\n\n";
            system("pause");
            system("cls");

        }
                break;
        case 'T': {
            if (stats.isEmpty()) {
                cout << "\n\t\tERROR: Data set is empty.\n\n";
                system("pause");
                system("cls");
                goto beginning;
            }
            cout << "\n\t\tStandard Error of the Mean \t= " << stats.getStandardErrorOfTheMean();
            cout << "\n\n";
            system("pause");
            system("cls");
        }
                break;
        case 'U': {
            if (stats.isEmpty()) {
                cout << "\n\t\tERROR: Data set is empty.\n\n";
                system("pause");
                system("cls");
                goto beginning;
            }
            cout << "\n\t\tCoefficient of Variation \t= " << stats.getCoefficientOfVariation();
            cout << "\n\n";
            system("pause");
            system("cls");
        }
                break;
        case 'V': {
            if (stats.isEmpty()) {
                cout << "\n\t\tERROR: Data set is empty.\n\n";
                system("pause");
                system("cls");
                goto beginning;
            }
            cout << "\n\t\tRelative Standard Deviation \t= " << stats.getRelativeStandardDeviation()<<"%";
            cout << "\n\n";
            system("pause");
            system("cls");
        }
                break;
        case '0': {
            //close the file
            stats.closeFile(filename);
            return;
        }
        }
    } while (true);
}