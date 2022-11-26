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

//call this if square is empty, direction char will have N, S, E, W, and will return spawn details if vehicle is to be spawned
vector<string> spawnOutcome(char direction, mt19937& randomNumberGenerator, vector<double> vehicleProb, 
                            vector<double> vehicleProportion, vector<double> carTurns, vector<double> SUVTurns, 
                            vector<double> TruckTurns) {
    vector<string> result;
    std::uniform_real_distribution<double> rand_double(0,1);

    //check is the direction if north, and if it is generate a random number to determine if it is a car, SUV, or truck. If it is
    //none of these options, return NONE for both options to show that a vehicle will not spawn.
    //if it is one of those three vehicles, push the name of the vehicle to be spawned to the first index of the return vector,
    //and generate a new random number (turnsProb) to calculate what direction the vehicle will go once spawned in. Push back
    //the turn direction to the second element of the return vector, then return it. This repeats for the other directions.
    if (direction == 'N' || direction == 'n') {

        double randNum = rand_double(randomNumberGenerator); 
        if (vehicleProb[0] < randNum) {

            result.push_back("CAR");
            double turnsProb = rand_double(randomNumberGenerator);
            if (carTurns[0] < turnsProb) {
                result.push_back("RIGHT");
            }
            else if (carTurns[1] < turnsProb) {
                result.push_back("LEFT");
            }
            else if (carTurns[2] < turnsProb) {
                result.push_back("STRAIGHT");
            }
            return result;
        }

        else if (vehicleProb[1] < randNum) {

            result.push_back("SUV");
            double turnsProb = rand_double(randomNumberGenerator);
            if (SUVTurns[0] < turnsProb) {
                result.push_back("RIGHT");
            }
            else if (SUVTurns[1] < turnsProb) {
                result.push_back("LEFT");
            }
            else if (SUVTurns[2] < turnsProb) {
                result.push_back("STRAIGHT");
            }
            return result;
        }

        else if (vehicleProb[2] < randNum) {

            result.push_back("TRUCK");
            double turnsProb = rand_double(randomNumberGenerator);
            if (TruckTurns[0] < turnsProb) {
                result.push_back("RIGHT");
            }
            else if (TruckTurns[1] < turnsProb) {
                result.push_back("LEFT");
            }
            else if (TruckTurns[2] < turnsProb) {
                result.push_back("STRAIGHT");
            }
            return result;
        }
        result.push_back("NONE");
        result.push_back("NONE");
        return result;
    }
    else if (direction == 'S' || direction == 's') {
        double randNum = rand_double(randomNumberGenerator); 
        if (vehicleProb[0] < randNum) {

            result.push_back("CAR");
            double turnsProb = rand_double(randomNumberGenerator);
            if (carTurns[0] < turnsProb) {
                result.push_back("RIGHT");
            }
            else if (carTurns[1] < turnsProb) {
                result.push_back("LEFT");
            }
            else if (carTurns[2] < turnsProb) {
                result.push_back("STRAIGHT");
            }
            return result;
        }

        else if (vehicleProb[1] < randNum) {

            result.push_back("SUV");
            double turnsProb = rand_double(randomNumberGenerator);
            if (SUVTurns[0] < turnsProb) {
                result.push_back("RIGHT");
            }
            else if (SUVTurns[1] < turnsProb) {
                result.push_back("LEFT");
            }
            else if (SUVTurns[2] < turnsProb) {
                result.push_back("STRAIGHT");
            }
            return result;
        }

        if (vehicleProb[2] < randNum) {

            result.push_back("TRUCK");
            double turnsProb = rand_double(randomNumberGenerator);
            if (TruckTurns[0] < turnsProb) {
                result.push_back("RIGHT");
            }
            else if (TruckTurns[1] < turnsProb) {
                result.push_back("LEFT");
            }
            else if (TruckTurns[2] < turnsProb) {
                result.push_back("STRAIGHT");
            }
            return result;
        }
        result.push_back("NONE");
        result.push_back("NONE");
        return result;
    }
    else if (direction == 'E' || direction == 'e') {
        double randNum = rand_double(randomNumberGenerator); 
        if (vehicleProb[0] < randNum) {

            result.push_back("CAR");
            double turnsProb = rand_double(randomNumberGenerator);
            if (carTurns[0] < turnsProb) {
                result.push_back("RIGHT");
            }
            else if (carTurns[1] < turnsProb) {
                result.push_back("LEFT");
            }
            else if (carTurns[2] < turnsProb) {
                result.push_back("STRAIGHT");
            }
            return result;
        }

        else if (vehicleProb[1] < randNum) {

            result.push_back("SUV");
            double turnsProb = rand_double(randomNumberGenerator);
            if (SUVTurns[0] < turnsProb) {
                result.push_back("RIGHT");
            }
            else if (SUVTurns[1] < turnsProb) {
                result.push_back("LEFT");
            }
            else if (SUVTurns[2] < turnsProb) {
                result.push_back("STRAIGHT");
            }
            return result;
        }

        else if (vehicleProb[2] < randNum) {

            result.push_back("TRUCK");
            double turnsProb = rand_double(randomNumberGenerator);
            if (TruckTurns[0] < turnsProb) {
                result.push_back("RIGHT");
            }
            else if (TruckTurns[1] < turnsProb) {
                result.push_back("LEFT");
            }
            else if (TruckTurns[2] < turnsProb) {
                result.push_back("STRAIGHT");
            }
            return result;
        }
        result.push_back("NONE");
        result.push_back("NONE");
        return result;
    }
    else if (direction == 'W' || direction == 'w') {
        double randNum = rand_double(randomNumberGenerator); 
        if (vehicleProb[0] < randNum) {

            result.push_back("CAR");
            double turnsProb = rand_double(randomNumberGenerator);
            if (carTurns[0] < turnsProb) {
                result.push_back("RIGHT");
            }
            else if (carTurns[1] < turnsProb) {
                result.push_back("LEFT");
            }
            else if (carTurns[2] < turnsProb) {
                result.push_back("STRAIGHT");
            }
            return result;
        }

        else if (vehicleProb[1] < randNum) {

            result.push_back("SUV");
            double turnsProb = rand_double(randomNumberGenerator);
            if (SUVTurns[0] < turnsProb) {
                result.push_back("RIGHT");
            }
            else if (SUVTurns[1] < turnsProb) {
                result.push_back("LEFT");
            }
            else if (SUVTurns[2] < turnsProb) {
                result.push_back("STRAIGHT");
            }
            return result;
        }

        else if (vehicleProb[2] < randNum) {

            result.push_back("TRUCK");
            double turnsProb = rand_double(randomNumberGenerator);
            if (TruckTurns[0] < turnsProb) {
                result.push_back("RIGHT");
            }
            else if (TruckTurns[1] < turnsProb) {
                result.push_back("LEFT");
            }
            else if (TruckTurns[2] < turnsProb) {
                result.push_back("STRAIGHT");
            }
            return result;
        }
        result.push_back("NONE");
        result.push_back("NONE");
        return result;
    }
    result.push_back("NONE");
    result.push_back("NONE");
    return result;
}

int main(int argc, char* argv[]) {

    //Makes sure correct amount of command line arguments
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " [input file]" << "[initial seed]" << endl;
        exit(0);
    }


    std::mt19937 randomNumberGenerator; // Mersenne twister
    std::uniform_real_distribution<double> rand_double(0,1);
    int seed {stoi(argv[2])};
    randomNumberGenerator.seed(seed);

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
    vector<double> prob_new_vehicle;
    prob_new_vehicle.push_back(prob_new_vehicle_northbound);
    prob_new_vehicle.push_back(prob_new_vehicle_southbound);
    prob_new_vehicle.push_back(prob_new_vehicle_eastbound);
    prob_new_vehicle.push_back(prob_new_vehicle_westbound);

    double proportion_of_cars{getDoubleAt(inputData[10])};          
    double proportion_of_SUVs{getDoubleAt(inputData[11])};
    double proportion_of_trucks{1-proportion_of_cars-proportion_of_SUVs};
    vector<double> new_vehicle_proportion;
    new_vehicle_proportion.push_back(proportion_of_cars);
    new_vehicle_proportion.push_back(proportion_of_SUVs);
    new_vehicle_proportion.push_back(proportion_of_trucks);

    double proportion_right_turn_cars{getDoubleAt(inputData[12])};  
    double proportion_left_turn_cars{getDoubleAt(inputData[13])};
    double proportion_straight_cars{1-proportion_right_turn_cars-proportion_left_turn_cars};
    vector<double> car_turns;
    car_turns.push_back(proportion_right_turn_cars);
    car_turns.push_back(proportion_left_turn_cars);
    car_turns.push_back(proportion_straight_cars);

    double proportion_right_turn_SUVs{getDoubleAt(inputData[14])};  
    double proportion_left_turn_SUVs{getDoubleAt(inputData[15])};   
    double proportion_straight_SUVs{1-proportion_right_turn_SUVs-proportion_left_turn_SUVs};
    vector<double> SUV_turns;
    SUV_turns.push_back(proportion_right_turn_SUVs);
    SUV_turns.push_back(proportion_left_turn_SUVs);
    SUV_turns.push_back(proportion_straight_SUVs);

    double proportion_right_turn_trucks{getDoubleAt(inputData[16])};
    double proportion_left_turn_trucks{getDoubleAt(inputData[17])};
    double proportion_straight_trucks{1-proportion_right_turn_trucks-proportion_left_turn_trucks};
    vector<double> truck_turns;
    truck_turns.push_back(proportion_right_turn_trucks);
    truck_turns.push_back(proportion_left_turn_trucks);
    truck_turns.push_back(proportion_straight_trucks);

    char direction {'N'};
    vector<string>vehicleSpawn = spawnOutcome(direction, randomNumberGenerator, prob_new_vehicle, new_vehicle_proportion,
                                                car_turns, SUV_turns, truck_turns);
    cout << vehicleSpawn.at(0) << " " << vehicleSpawn.at(1) << endl;
    return 0;
}