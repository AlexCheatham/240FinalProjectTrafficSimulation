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


//takes in a string and removes whitespace from it and returns the cleaned string, whitespace is assumed to be at the front
//taken from stackoverflow https://stackoverflow.com/a/16329377
string removeWhitespace(string input) {
    input.erase(remove(input.begin(),input.end(),' '),input.end());
    return input;
}

//takes in a string and returns the number contained at the end of the line. Used for the traffic sim input
int getIntAt(string data) {
    size_t end = data.size();
    string str {data.substr(data.find(':') + 1, end)};
    str = removeWhitespace(str);
    return stoi(str);
}

//takes in a string and retuns a double at the end of the line, used for the traffic sim input
double getDoubleAt(string data) {
    size_t end = data.size();
    string str {data.substr(data.find(':') + 1, end)};
    str = removeWhitespace(str);
    return stod(str);
}

int main(int argc, char* argv[]) {

    //Makes sure correct amount of command line arguments
    if (argc < 1) {
        cerr << "Usage: " << argv[0] << " [input file]" << endl;
        exit(0);
    }    

    

    vector<string> inputData; //Vector containing the lines of code from the file
    string str; //used for inputting the lines into the vector
    //Collects the input file and opens it 
    string inputFile = argv[1];
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
    int maximum_simulated_time {getIntAt(inputData[0])};
    int number_of_sections_before_intersection{getIntAt(inputData[1])};
    int green_north_south{getIntAt(inputData[2])};
    int yellow_north_south{getIntAt(inputData[3])};
    int green_east_west{getIntAt(inputData[4])};
    int yellow_east_west{getIntAt(inputData[5])};
    double prob_new_vehicle_northbound{getDoubleAt(inputData[6])};
    double prob_new_vehicle_southbound{getDoubleAt(inputData[7])}; 
    double prob_new_vehicle_eastbound{getDoubleAt(inputData[8])};   
    double prob_new_vehicle_westbound{getDoubleAt(inputData[9])};   
    double proportion_of_cars{getDoubleAt(inputData[10])};          
    double proportion_of_SUVs{getDoubleAt(inputData[11])};
    double proportion_of_trucks{1-proportion_of_cars-proportion_of_SUVs};
    double proportion_right_turn_cars{getDoubleAt(inputData[12])};  
    double proportion_left_turn_cars{getDoubleAt(inputData[13])};
    double proportion_straight_cars{1-proportion_right_turn_cars-proportion_left_turn_cars};
    double proportion_right_turn_SUVs{getDoubleAt(inputData[14])};  
    double proportion_left_turn_SUVs{getDoubleAt(inputData[15])};   
    double proportion_straight_SUVs{1-proportion_right_turn_SUVs-proportion_left_turn_SUVs};
    double proportion_right_turn_trucks{getDoubleAt(inputData[16])};
    double proportion_left_turn_trucks{getDoubleAt(inputData[17])};
    double proportion_straight_trucks{1-proportion_right_turn_trucks-proportion_left_turn_trucks};
}