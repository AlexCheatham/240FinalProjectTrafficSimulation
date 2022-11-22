//==========================================================================
//* class trafficSim
//* Authors: Henley Smith, Alex Cheatham
//* Written: 11/21/2022
//==========================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <iterator>
#include <map>
#include <bitset>

using namespace std;

class trafficSim {

    vector<string> inputData;       //the data for the simulation fed through the input file, raw lines to be cleaned
    vector<string> varNames;        //holds all the variable names for the input data
    vector<int> varValues;          //holds all of the values for the input data
    map<string, int> simData;       //map that holds all of the data for the simulation

    string getVarName(string line) {
        //size_t pos{line.find_first_of(' ')};
        string varName{line.substr(0, line.find(':'))};
        cout << varName << endl;
        return varName;
    }
public:
    //Constructor
    trafficSim(vector<string> input) {

        //stores input
        inputData = input;

    }

    //destructor
    ~trafficSim() {};

    //stores the data from the imput into simData
    vector<string> loadData() {

        //Useful variables for setting up a while loop
        vector<string> tokens;
        size_t i{0};   

        while(i < inputData.size()) {
            string name = trafficSim::getVarName(inputData[i]);
            varNames.push_back(name);
        }
    }
    
};

int main(int argc, char* argv[]) {

    //Makes sure correct amount of command line arguments
    if (argc < 1) {
        cerr << "Usage: " << argv[0] << " [input file]" << endl;
        exit(0);
    }    

    vector<string> inputData; //Vector containing the lines of code from the file
    string str; //used for inputting the lines into the vector
    //Collects the input file and opens it 
    string inputFile = argv[0];
    ifstream myFile(inputFile);
    //Adds lines to vector
    if (myFile.is_open()) {
        while(getline(myFile, str)) {
            if(str.size() > 0) {
                inputData.push_back(str);
            }
        }
    }
    //Closes the input file
    myFile.close();

    trafficSim test(inputData);
    test.loadData();
}