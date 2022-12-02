#include <iostream>
#include <random>
#include <map>
#include <fstream>
#include <string>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <iterator>
#include "Animator.cpp"
#include "VehicleBase.cpp"

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

string getName(string data) {
    string str {data.substr(0,data.find(':'))};
    return str;
}

int main(int argc, char* argv[]){

    //Makes sure correct amount of command line arguments
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " [input file]" << "[initial seed]" << endl;
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

    map<string, int> intMap;
    map<string, double> doubleMap;

    for(int i = 0; i < inputData.size(); i++) {
        str = getName(inputData[i]);
        if (str.compare("maximum_simulated_time") == 0 || str.compare("number_of_sections_before_intersection") == 0 ||
            str.compare("green_north_south") == 0 || str.compare("yellow_north_south") == 0 ||
            str.compare("green_east_west") == 0 || str.compare("yellow_east_west") == 0) {

                intMap.insert(pair<string, int>(str, getIntAt(inputData.at(i))));
        }
        else {
            doubleMap.insert(pair<string, double>(str, getDoubleAt(inputData.at(i))));
        }
    }

    // int maximum_simulated_time;
    // int number_of_sections_before_intersection;
    // int green_north_south;
    // int yellow_north_south;
    // int green_east_west;
    // int yellow_east_west;
    // double prob_new_vehicle_northbound;
    // double prob_new_vehicle_southbound;
    // double prob_new_vehicle_eastbound;
    // double prob_new_vehicle_westbound;
    // double proportion_of_cars;
    // double proportion_of_SUVs;
    // double proportion_right_turn_cars;
    // double proportion_left_turn_cars;
    // double proportion_right_turn_SUVs;
    // double proportion_left_turn_SUVs;
    // double proportion_right_turn_trucks;
    // double proportion_left_turn_trucks;

    // maximum_simulated_time = 1000;
    // number_of_sections_before_intersection = 10;
    // green_north_south = 12;
    // yellow_north_south = 3;
    // green_east_west = 10;
    // yellow_east_west = 3;
    // prob_new_vehicle_northbound = .25;
    // prob_new_vehicle_southbound = .1;
    // prob_new_vehicle_eastbound = .15;
    // prob_new_vehicle_westbound = .15;
    // proportion_of_cars = .6;
    // proportion_of_SUVs = .3;
    // proportion_right_turn_cars = .4;
    // proportion_left_turn_cars = .1;
    // proportion_right_turn_SUVs = .3;
    // proportion_left_turn_SUVs = .05;
    // proportion_right_turn_trucks = .2;
    // proportion_left_turn_trucks = .02;
    int maximum_simulated_time {intMap.at("maximum_simulated_time")};
    int number_of_sections_before_intersection{intMap.at("number_of_sections_before_intersection")};
    int green_north_south{intMap.at("green_north_south")};
    int yellow_north_south{intMap.at("yellow_north_south")};
    int green_east_west{intMap.at("green_east_west")};
    int yellow_east_west{intMap.at("yellow_east_west")};

    double prob_new_vehicle_northbound{doubleMap.at("prob_new_vehicle_northbound")};
    double prob_new_vehicle_southbound{doubleMap.at("prob_new_vehicle_southbound")}; 
    double prob_new_vehicle_eastbound{doubleMap.at("prob_new_vehicle_eastbound")};   
    double prob_new_vehicle_westbound{doubleMap.at("prob_new_vehicle_westbound")};
    double proportion_of_cars{doubleMap.at("proportion_of_cars")};          
    double proportion_of_SUVs{doubleMap.at("proportion_of_SUVs")};
    double proportion_right_turn_cars{doubleMap.at("proportion_right_turn_cars")};  
    double proportion_left_turn_cars{doubleMap.at("proportion_left_turn_cars")};
    double proportion_right_turn_SUVs{doubleMap.at("proportion_right_turn_SUVs")};  
    double proportion_left_turn_SUVs{doubleMap.at("proportion_left_turn_SUVs")}; 
    double proportion_right_turn_trucks{doubleMap.at("proportion_right_turn_trucks")};
    double proportion_left_turn_trucks{doubleMap.at("proportion_left_turn_trucks")};

    int initialSeed;
    initialSeed = {stoi(argv[2])};

    Animator::MAX_VEHICLE_COUNT = 999;
    // i will probably have to figure out a different implementation of vehicle base
    Animator anim(number_of_sections_before_intersection);

    vector<VehicleBase*> westbound(number_of_sections_before_intersection * 2 + 2, nullptr);
    vector<VehicleBase*> eastbound(number_of_sections_before_intersection * 2 + 2, nullptr);
    vector<VehicleBase*> southbound(number_of_sections_before_intersection * 2 + 2, nullptr);
    vector<VehicleBase*> northbound(number_of_sections_before_intersection * 2 + 2, nullptr);

    char dummy;

    //probability stuff

    mt19937 rng;
    uniform_real_distribution<double> rand_double(0.0, 1.0);
    rng.seed(initialSeed);
    double prob;
    //string vehicle_type;
    //string turn;

    //pointer to vehiclebase we will use to destruct once it goes off screen, will need to change to new vehiclebase

    bool ENpriority;
    bool NSmove;

    int eSTILL = 0;
    int wSTILL = 0;
    int nSTILL = 0;
    int sSTILL = 0;


    int timer_east = 0;
    int timer_west = 0;
    int timer_north = 0;
    int timer_south = 0;

    bool e_maderoom = false;
    bool w_maderoom = false;
    bool n_maderoom = false;
    bool s_maderoom = false;

    int right = 1;
    int straight = 2;
    int left = 3;

    int car = 1;
    int suv = 2;
    int truck = 3;

    //VehicleBase vb1(VehicleType::car, Direction::east);
    //VehicleBase vb2(VehicleType::car, Direction::east);
    //VehicleBase vb3(VehicleType::car, Direction::north);

    //test purposes only
    //eastbound[15] = &vb1;
    //eastbound[11] = &vb2;
    //northbound[12] = &vb3;
    //northbound[number_of_sections_before_intersection - 1] = new VehicleBase(VehicleType::car, Direction::west);
    //northbound[number_of_sections_before_intersection - 2] = northbound[number_of_sections_before_intersection - 1];
    //northbound[number_of_sections_before_intersection] = new VehicleBase(VehicleType::car, Direction::east);
    //westbound[number_of_sections_before_intersection + 1] = new VehicleBase(VehicleType::car, Direction::west);

    for (int i = 0; i < maximum_simulated_time; i++) {

        // setting the lights to the appropriate color at appropriate time ticks
        if (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west) == 0) {
            anim.setLightNorthSouth(LightColor::green);
            anim.setLightEastWest(LightColor::red);
        }
        else if (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west) == green_north_south) {
            anim.setLightNorthSouth(LightColor::yellow);
            eSTILL = 0;
            wSTILL = 0;
        }
        else if (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west) == green_north_south + yellow_north_south) {
            anim.setLightNorthSouth(LightColor::red);
            anim.setLightEastWest(LightColor::green);
        }
        else if (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west) == green_north_south + yellow_north_south + green_east_west) {
            anim.setLightEastWest(LightColor::yellow);
            nSTILL = 0;
            sSTILL = 0;
        }
        else {

        }

        //determines which of the opposing lanes has priority

        if (i % (2*(green_north_south + yellow_north_south + green_east_west + yellow_east_west)) == 0) {
            ENpriority = true;
        }
        if (i % (2*(green_north_south + yellow_north_south + green_east_west + yellow_east_west)) == (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) {
            ENpriority = false;
        }

        //determines whether NS has green light
        if (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west) == 0) {
            NSmove = true;
        }
        if (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west) == green_north_south + yellow_north_south) {
            NSmove = false;
        }

        //THIS IS FOR UPDATING THE SQUARES PAST THE INTERSECTION FOR EACH LANE
        //eastbound
        for (int i = (2 * number_of_sections_before_intersection) + 1; i > number_of_sections_before_intersection + 2; i--) {
            eastbound[i] = eastbound[i-1];
            eastbound[i-1] = nullptr;
        }

        //westbound
        for (int i = (2 * number_of_sections_before_intersection) + 1; i > number_of_sections_before_intersection + 2; i--) {
            westbound[i] = westbound[i-1];
            westbound[i-1] = nullptr;
        }

        //northbound
        for (int i = (2 * number_of_sections_before_intersection) + 1; i > number_of_sections_before_intersection + 2; i--) {
            northbound[i] = northbound[i-1];
            northbound[i-1] = nullptr;
        }

        //southbound
        for (int i = (2 * number_of_sections_before_intersection) + 1; i > number_of_sections_before_intersection + 2; i--) {
            southbound[i] = southbound[i-1];
            southbound[i-1] = nullptr;
        }

    // THIS IS FOR MOVING EACH MIDDLE CAR
    
    //northbound prioritized
    if (ENpriority == true && NSmove == true) {
        if (southbound[number_of_sections_before_intersection + 1] != nullptr) {
            southbound[number_of_sections_before_intersection + 2] = southbound[number_of_sections_before_intersection + 1];
            southbound[number_of_sections_before_intersection + 1] = nullptr;
        }
        if (westbound[number_of_sections_before_intersection + 1] != nullptr && westbound[number_of_sections_before_intersection + 1]->getVehicleOriginalDirection() == Direction::west) {
            westbound[number_of_sections_before_intersection + 2] = westbound[number_of_sections_before_intersection + 1];
            westbound[number_of_sections_before_intersection + 1] = nullptr;
        }
        if (southbound[number_of_sections_before_intersection] != nullptr && southbound[number_of_sections_before_intersection]->getVehicleOriginalDirection() == Direction::south) {
            southbound[number_of_sections_before_intersection + 1] = southbound[number_of_sections_before_intersection];
            southbound[number_of_sections_before_intersection] = nullptr;
        }
        if (westbound[number_of_sections_before_intersection] != nullptr && westbound[number_of_sections_before_intersection]->getVehicleOriginalDirection() == Direction::west) {
            westbound[number_of_sections_before_intersection + 1] = westbound[number_of_sections_before_intersection];
            westbound[number_of_sections_before_intersection] = nullptr;
        }
        if (northbound[number_of_sections_before_intersection + 1] != nullptr && northbound[number_of_sections_before_intersection + 1]->getVehicleOriginalDirection() == Direction::north) {
            northbound[number_of_sections_before_intersection + 2] = northbound[number_of_sections_before_intersection + 1];
            northbound[number_of_sections_before_intersection + 1] = nullptr;
        }
        if (eastbound[number_of_sections_before_intersection + 1] != nullptr && eastbound[number_of_sections_before_intersection + 1]->getVehicleOriginalDirection() == Direction::east) {
            eastbound[number_of_sections_before_intersection + 2] = eastbound[number_of_sections_before_intersection + 1];
            eastbound[number_of_sections_before_intersection + 1] = nullptr;
        }
        if (northbound[number_of_sections_before_intersection] != nullptr && northbound[number_of_sections_before_intersection]->getVehicleOriginalDirection() == Direction::north) {
            northbound[number_of_sections_before_intersection + 1] = northbound[number_of_sections_before_intersection];
            northbound[number_of_sections_before_intersection] = nullptr;
        }
        if (northbound[number_of_sections_before_intersection] != nullptr && northbound[number_of_sections_before_intersection]->getVehicleOriginalDirection() == Direction::west) {
            westbound[number_of_sections_before_intersection] = northbound[number_of_sections_before_intersection];
            northbound[number_of_sections_before_intersection] = nullptr;
        }
    }
    //eastbound prioritized
    else if (ENpriority == true && NSmove == false) {
        if (westbound[number_of_sections_before_intersection + 1] != nullptr) {
            westbound[number_of_sections_before_intersection + 2] = westbound[number_of_sections_before_intersection + 1];
            westbound[number_of_sections_before_intersection + 1] = nullptr;
        }
        if (northbound[number_of_sections_before_intersection + 1] != nullptr && northbound[number_of_sections_before_intersection + 1]->getVehicleOriginalDirection() == Direction::north) {
            northbound[number_of_sections_before_intersection + 2] = northbound[number_of_sections_before_intersection + 1];
            northbound[number_of_sections_before_intersection + 1] = nullptr;
        }
        if (westbound[number_of_sections_before_intersection] != nullptr && westbound[number_of_sections_before_intersection]->getVehicleOriginalDirection() == Direction::west) {
            westbound[number_of_sections_before_intersection + 1] = westbound[number_of_sections_before_intersection];
            westbound[number_of_sections_before_intersection] = nullptr;
        }
        if (northbound[number_of_sections_before_intersection] != nullptr && northbound[number_of_sections_before_intersection]->getVehicleOriginalDirection() == Direction::north) {
            northbound[number_of_sections_before_intersection + 1] = northbound[number_of_sections_before_intersection];
            northbound[number_of_sections_before_intersection] = nullptr;
        }
        if (eastbound[number_of_sections_before_intersection + 1] != nullptr && eastbound[number_of_sections_before_intersection + 1]->getVehicleOriginalDirection() == Direction::east) {
            eastbound[number_of_sections_before_intersection + 2] = eastbound[number_of_sections_before_intersection + 1];
            eastbound[number_of_sections_before_intersection + 1] = nullptr;
        }
        if (southbound[number_of_sections_before_intersection + 1] != nullptr && southbound[number_of_sections_before_intersection + 1]->getVehicleOriginalDirection() == Direction::south) {
            southbound[number_of_sections_before_intersection + 2] = southbound[number_of_sections_before_intersection + 1];
            southbound[number_of_sections_before_intersection + 1] = nullptr;
        }
        if (eastbound[number_of_sections_before_intersection] != nullptr && eastbound[number_of_sections_before_intersection]->getVehicleOriginalDirection() == Direction::east) {
            eastbound[number_of_sections_before_intersection + 1] = eastbound[number_of_sections_before_intersection];
            eastbound[number_of_sections_before_intersection] = nullptr;
        }
        if (eastbound[number_of_sections_before_intersection] != nullptr && eastbound[number_of_sections_before_intersection]->getVehicleOriginalDirection() == Direction::north) {
            northbound[number_of_sections_before_intersection] = eastbound[number_of_sections_before_intersection];
            eastbound[number_of_sections_before_intersection] = nullptr;
        }
    }
    //southbound prioritized
    else if (ENpriority == false && NSmove == true) {
        if (northbound[number_of_sections_before_intersection + 1] != nullptr) {
            northbound[number_of_sections_before_intersection + 2] = northbound[number_of_sections_before_intersection + 1];
            northbound[number_of_sections_before_intersection + 1] = nullptr;
        }
        if (eastbound[number_of_sections_before_intersection + 1] != nullptr && eastbound[number_of_sections_before_intersection + 1]->getVehicleOriginalDirection() == Direction::east) {
            eastbound[number_of_sections_before_intersection + 2] = eastbound[number_of_sections_before_intersection + 1];
            eastbound[number_of_sections_before_intersection + 1] = nullptr;
        }
        if (northbound[number_of_sections_before_intersection] != nullptr && northbound[number_of_sections_before_intersection]->getVehicleOriginalDirection() == Direction::north) {
            northbound[number_of_sections_before_intersection + 1] = northbound[number_of_sections_before_intersection];
            northbound[number_of_sections_before_intersection] = nullptr;
        }
        if (eastbound[number_of_sections_before_intersection] != nullptr && eastbound[number_of_sections_before_intersection]->getVehicleOriginalDirection() == Direction::east) {
            eastbound[number_of_sections_before_intersection + 1] = eastbound[number_of_sections_before_intersection];
            eastbound[number_of_sections_before_intersection] = nullptr;
        }
        if (southbound[number_of_sections_before_intersection + 1] != nullptr && southbound[number_of_sections_before_intersection + 1]->getVehicleOriginalDirection() == Direction::south) {
            southbound[number_of_sections_before_intersection + 2] = southbound[number_of_sections_before_intersection + 1];
            southbound[number_of_sections_before_intersection + 1] = nullptr;
        }
        if (westbound[number_of_sections_before_intersection + 1] != nullptr && westbound[number_of_sections_before_intersection + 1]->getVehicleOriginalDirection() == Direction::west) {
            westbound[number_of_sections_before_intersection + 2] = westbound[number_of_sections_before_intersection + 1];
            westbound[number_of_sections_before_intersection + 1] = nullptr;
        }
        if (southbound[number_of_sections_before_intersection] != nullptr && southbound[number_of_sections_before_intersection]->getVehicleOriginalDirection() == Direction::south) {
            southbound[number_of_sections_before_intersection + 1] = southbound[number_of_sections_before_intersection];
            southbound[number_of_sections_before_intersection] = nullptr;
        }
        if (southbound[number_of_sections_before_intersection] != nullptr && southbound[number_of_sections_before_intersection]->getVehicleOriginalDirection() == Direction::east) {
            eastbound[number_of_sections_before_intersection] = southbound[number_of_sections_before_intersection];
            southbound[number_of_sections_before_intersection] = nullptr;
        }
    }
    //westbound prioritized
    else if (ENpriority == false && NSmove == false) {
        if (eastbound[number_of_sections_before_intersection + 1] != nullptr) {
            eastbound[number_of_sections_before_intersection + 2] = eastbound[number_of_sections_before_intersection + 1];
            eastbound[number_of_sections_before_intersection + 1] = nullptr;
        }
        if (southbound[number_of_sections_before_intersection + 1] != nullptr && southbound[number_of_sections_before_intersection + 1]->getVehicleOriginalDirection() == Direction::south) {
            southbound[number_of_sections_before_intersection + 2] = southbound[number_of_sections_before_intersection + 1];
            southbound[number_of_sections_before_intersection + 1] = nullptr;
        }
        if (eastbound[number_of_sections_before_intersection] != nullptr && eastbound[number_of_sections_before_intersection]->getVehicleOriginalDirection() == Direction::east) {
            eastbound[number_of_sections_before_intersection + 1] = eastbound[number_of_sections_before_intersection];
            eastbound[number_of_sections_before_intersection] = nullptr;
        }
        if (southbound[number_of_sections_before_intersection] != nullptr && southbound[number_of_sections_before_intersection]->getVehicleOriginalDirection() == Direction::south) {
            southbound[number_of_sections_before_intersection + 1] = southbound[number_of_sections_before_intersection];
            southbound[number_of_sections_before_intersection] = nullptr;
        }
        if (westbound[number_of_sections_before_intersection + 1] != nullptr && westbound[number_of_sections_before_intersection + 1]->getVehicleOriginalDirection() == Direction::west) {
            westbound[number_of_sections_before_intersection + 2] = westbound[number_of_sections_before_intersection + 1];
            westbound[number_of_sections_before_intersection + 1] = nullptr;
        }
        if (northbound[number_of_sections_before_intersection + 1] != nullptr && northbound[number_of_sections_before_intersection + 1]->getVehicleOriginalDirection() == Direction::north) {
            northbound[number_of_sections_before_intersection + 2] = northbound[number_of_sections_before_intersection + 1];
            northbound[number_of_sections_before_intersection + 1] = nullptr;
        }
        if (westbound[number_of_sections_before_intersection] != nullptr && westbound[number_of_sections_before_intersection]->getVehicleOriginalDirection() == Direction::west) {
            westbound[number_of_sections_before_intersection + 1] = westbound[number_of_sections_before_intersection];
            westbound[number_of_sections_before_intersection] = nullptr;
        }
        if (westbound[number_of_sections_before_intersection] != nullptr && westbound[number_of_sections_before_intersection]->getVehicleOriginalDirection() == Direction::south) {
            southbound[number_of_sections_before_intersection] = westbound[number_of_sections_before_intersection];
            westbound[number_of_sections_before_intersection] = nullptr;
        }
    }
    

    // THIS IS FOR DECIDING whether to move vehicles into the intersection
    //northbound prioritized
    
    if (ENpriority == true && NSmove == true) {
        //right turn (prioritized)
        if (northbound[number_of_sections_before_intersection - 1] != nullptr && northbound[number_of_sections_before_intersection - 1]->getVehicleOriginalDirection() == Direction::east) {
            if (nSTILL == 0 && eastbound[number_of_sections_before_intersection + 1] == nullptr) {
                //car
                if (northbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::car) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 2) {
                        eastbound[number_of_sections_before_intersection + 1] = northbound[number_of_sections_before_intersection - 1];
                        northbound[number_of_sections_before_intersection - 1] = nullptr;
                        nSTILL = car;
                    }
                }

                //suv
                else if (northbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::suv) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 3) {
                        eastbound[number_of_sections_before_intersection + 1] = northbound[number_of_sections_before_intersection - 1];
                        northbound[number_of_sections_before_intersection - 1] = nullptr;
                        nSTILL = suv;
                    }
                }

                //truck
                else if (northbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::truck) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 4) {
                        eastbound[number_of_sections_before_intersection + 1] = northbound[number_of_sections_before_intersection - 1];
                        northbound[number_of_sections_before_intersection - 1] = nullptr;
                        nSTILL = truck;
                    }
                }
            }
            else if (nSTILL > 0) {
                eastbound[number_of_sections_before_intersection + 1] = northbound[number_of_sections_before_intersection - 1];
                northbound[number_of_sections_before_intersection - 1] = nullptr;
                nSTILL--;
            }
        }
        //straight (prioritized)
        else if (northbound[number_of_sections_before_intersection - 1] != nullptr && northbound[number_of_sections_before_intersection - 1]->getVehicleOriginalDirection() == Direction::north) {
            if (nSTILL == 0 && northbound[number_of_sections_before_intersection] == nullptr) {
                //car
                if (northbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::car) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 4) {
                        northbound[number_of_sections_before_intersection] = northbound[number_of_sections_before_intersection - 1];
                        northbound[number_of_sections_before_intersection - 1] = nullptr;
                        nSTILL = car;
                    }
                }

                //suv
                else if (northbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::suv) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 5) {
                        northbound[number_of_sections_before_intersection] = northbound[number_of_sections_before_intersection - 1];
                        northbound[number_of_sections_before_intersection - 1] = nullptr;
                        nSTILL = suv;
                    }
                }

                //truck
                else if (northbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::truck) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 6) {
                        northbound[number_of_sections_before_intersection] = northbound[number_of_sections_before_intersection - 1];
                        northbound[number_of_sections_before_intersection - 1] = nullptr;
                        nSTILL = truck;
                    }
                }
            }
            else if (nSTILL > 0) {
                northbound[number_of_sections_before_intersection] = northbound[number_of_sections_before_intersection - 1];
                northbound[number_of_sections_before_intersection - 1] = nullptr;
                nSTILL--;
            }
        }
        //left turn (prioritized)
        else if (northbound[number_of_sections_before_intersection - 1] != nullptr && northbound[number_of_sections_before_intersection - 1]->getVehicleOriginalDirection() == Direction::west) {
            if (nSTILL == 0 && northbound[number_of_sections_before_intersection] == nullptr && !(southbound[number_of_sections_before_intersection] != nullptr && southbound[number_of_sections_before_intersection] == southbound[number_of_sections_before_intersection - 1] && southbound[number_of_sections_before_intersection - 1] == southbound[number_of_sections_before_intersection - 2])) {
                //car
                if (northbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::car) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 4) {
                        northbound[number_of_sections_before_intersection] = northbound[number_of_sections_before_intersection - 1];
                        northbound[number_of_sections_before_intersection - 1] = nullptr;
                        nSTILL = car;
                    }
                }

                //suv
                else if (northbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::suv) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 5) {
                        northbound[number_of_sections_before_intersection] = northbound[number_of_sections_before_intersection - 1];
                        northbound[number_of_sections_before_intersection - 1] = nullptr;
                        nSTILL = suv;
                    }
                }

                //truck
                else if (northbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::truck) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 6) {
                        northbound[number_of_sections_before_intersection] = northbound[number_of_sections_before_intersection - 1];
                        northbound[number_of_sections_before_intersection - 1] = nullptr;
                        nSTILL = truck;
                    }
                }
            }
            else if (nSTILL > 0) {
                northbound[number_of_sections_before_intersection] = northbound[number_of_sections_before_intersection - 1];
                northbound[number_of_sections_before_intersection - 1] = nullptr;
                nSTILL--;
            }
        }
        else {

        }
        //right (deprioritized)
        if (southbound[number_of_sections_before_intersection - 1] != nullptr && southbound[number_of_sections_before_intersection - 1]->getVehicleOriginalDirection() == Direction::west) {
            if (sSTILL == 0 && westbound[number_of_sections_before_intersection + 1] == nullptr && !((northbound[number_of_sections_before_intersection] != nullptr && northbound[number_of_sections_before_intersection]->getVehicleOriginalDirection() == Direction::west) || (westbound[number_of_sections_before_intersection] != nullptr && westbound[number_of_sections_before_intersection]->getVehicleOriginalDirection() == Direction::west) || (northbound[number_of_sections_before_intersection - 1] != nullptr && northbound[number_of_sections_before_intersection - 1]->getVehicleOriginalDirection() == Direction::west))) {
                //car
                if (southbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::car) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 2) {
                        westbound[number_of_sections_before_intersection + 1] = southbound[number_of_sections_before_intersection - 1];
                        southbound[number_of_sections_before_intersection - 1] = nullptr;
                        sSTILL = car;
                    }
                }

                //suv
                else if (southbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::suv) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 3) {
                        westbound[number_of_sections_before_intersection + 1] = southbound[number_of_sections_before_intersection - 1];
                        southbound[number_of_sections_before_intersection - 1] = nullptr;
                        sSTILL = suv;
                    }
                }

                //truck
                else if (southbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::truck) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 4) {
                        westbound[number_of_sections_before_intersection + 1] = southbound[number_of_sections_before_intersection - 1];
                        southbound[number_of_sections_before_intersection - 1] = nullptr;
                        sSTILL = truck;
                    }
                }
            }
            else if (sSTILL > 0) {
                westbound[number_of_sections_before_intersection + 1] = southbound[number_of_sections_before_intersection - 1];
                southbound[number_of_sections_before_intersection - 1] = nullptr;
                sSTILL--;
            }
        }
        // straight (deprioritized)
        else if (southbound[number_of_sections_before_intersection - 1] != nullptr && southbound[number_of_sections_before_intersection - 1]->getVehicleOriginalDirection() == Direction::south) {
            if (sSTILL == 0 && westbound[number_of_sections_before_intersection + 1] == nullptr && !((northbound[number_of_sections_before_intersection] != nullptr && northbound[number_of_sections_before_intersection]->getVehicleOriginalDirection() == Direction::west) || (westbound[number_of_sections_before_intersection] != nullptr && westbound[number_of_sections_before_intersection]->getVehicleOriginalDirection() == Direction::west) || (northbound[number_of_sections_before_intersection - 1] != nullptr && northbound[number_of_sections_before_intersection - 1]->getVehicleOriginalDirection() == Direction::west))) {
                //car
                if (southbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::car) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 4) {
                        southbound[number_of_sections_before_intersection] = southbound[number_of_sections_before_intersection - 1];
                        southbound[number_of_sections_before_intersection - 1] = nullptr;
                        sSTILL = car;
                    }
                }

                //suv
                else if (southbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::suv) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 5) {
                        southbound[number_of_sections_before_intersection] = southbound[number_of_sections_before_intersection - 1];
                        southbound[number_of_sections_before_intersection - 1] = nullptr;
                        sSTILL = suv;
                    }
                }

                //truck
                else if (southbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::truck) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 6) {
                        southbound[number_of_sections_before_intersection] = southbound[number_of_sections_before_intersection - 1];
                        southbound[number_of_sections_before_intersection - 1] = nullptr;
                        sSTILL = truck;
                    }
                }
            }
            else if (sSTILL > 0) {
                southbound[number_of_sections_before_intersection] = southbound[number_of_sections_before_intersection - 1];
                southbound[number_of_sections_before_intersection - 1] = nullptr;
                sSTILL--;
            }
        }
        else {

        }
    }
    
    //eastbound prioritized
    else if (ENpriority == true && NSmove == false) {
        //right turn (prioritized)
        if (eastbound[number_of_sections_before_intersection - 1] != nullptr && eastbound[number_of_sections_before_intersection - 1]->getVehicleOriginalDirection() == Direction::south) {
            if (eSTILL == 0 && southbound[number_of_sections_before_intersection + 1] == nullptr) {
                //car
                if (eastbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::car) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south + green_east_west + yellow_east_west) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 2) {
                        southbound[number_of_sections_before_intersection + 1] = eastbound[number_of_sections_before_intersection - 1];
                        eastbound[number_of_sections_before_intersection - 1] = nullptr;
                        eSTILL = car;
                    }
                }

                //suv
                else if (eastbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::suv) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south + green_east_west + yellow_east_west) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 3) {
                        southbound[number_of_sections_before_intersection + 1] = eastbound[number_of_sections_before_intersection - 1];
                        eastbound[number_of_sections_before_intersection - 1] = nullptr;
                        eSTILL = suv;
                    }
                }

                //truck
                else if (eastbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::truck) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south + green_east_west + yellow_east_west) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 4) {
                        southbound[number_of_sections_before_intersection + 1] = eastbound[number_of_sections_before_intersection - 1];
                        eastbound[number_of_sections_before_intersection - 1] = nullptr;
                        eSTILL = truck;
                    }
                }
            }
            else if (eSTILL > 0) {
                southbound[number_of_sections_before_intersection + 1] = eastbound[number_of_sections_before_intersection - 1];
                eastbound[number_of_sections_before_intersection - 1] = nullptr;
                eSTILL--;
            }
        }
        //straight (prioritized)
        else if (eastbound[number_of_sections_before_intersection - 1] != nullptr && eastbound[number_of_sections_before_intersection - 1]->getVehicleOriginalDirection() == Direction::east) {
            if (eSTILL == 0 && eastbound[number_of_sections_before_intersection] == nullptr) {
                //car
                if (eastbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::car) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south + green_east_west + yellow_east_west) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 4) {
                        eastbound[number_of_sections_before_intersection] = eastbound[number_of_sections_before_intersection - 1];
                        eastbound[number_of_sections_before_intersection - 1] = nullptr;
                        eSTILL = car;
                    }
                }

                //suv
                else if (eastbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::suv) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south + green_east_west + yellow_east_west) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 5) {
                        eastbound[number_of_sections_before_intersection] = eastbound[number_of_sections_before_intersection - 1];
                        eastbound[number_of_sections_before_intersection - 1] = nullptr;
                        eSTILL = suv;
                    }
                }

                //truck
                else if (eastbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::truck) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south + green_east_west + yellow_east_west) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 6) {
                        eastbound[number_of_sections_before_intersection] = eastbound[number_of_sections_before_intersection - 1];
                        eastbound[number_of_sections_before_intersection - 1] = nullptr;
                        eSTILL = truck;
                    }
                }
            }
            else if (eSTILL > 0) {
                eastbound[number_of_sections_before_intersection] = eastbound[number_of_sections_before_intersection - 1];
                eastbound[number_of_sections_before_intersection - 1] = nullptr;
                eSTILL--;
            }
        }
        //left turn (prioritized)
        else if (eastbound[number_of_sections_before_intersection - 1] != nullptr && eastbound[number_of_sections_before_intersection - 1]->getVehicleOriginalDirection() == Direction::north) {
            if (eSTILL == 0 && eastbound[number_of_sections_before_intersection] == nullptr && !(westbound[number_of_sections_before_intersection] != nullptr && westbound[number_of_sections_before_intersection] == westbound[number_of_sections_before_intersection - 1] && westbound[number_of_sections_before_intersection - 1] == westbound[number_of_sections_before_intersection - 2])) {
                //car
                if (eastbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::car) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south + green_east_west + yellow_east_west) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 4) {
                        eastbound[number_of_sections_before_intersection] = eastbound[number_of_sections_before_intersection - 1];
                        eastbound[number_of_sections_before_intersection - 1] = nullptr;
                        eSTILL = car;
                    }
                }

                //suv
                else if (eastbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::suv) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south + green_east_west + yellow_east_west) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 5) {
                        eastbound[number_of_sections_before_intersection] = eastbound[number_of_sections_before_intersection - 1];
                        eastbound[number_of_sections_before_intersection - 1] = nullptr;
                        eSTILL = suv;
                    }
                }

                //truck
                else if (eastbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::truck) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south + green_east_west + yellow_east_west) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 6) {
                        eastbound[number_of_sections_before_intersection] = eastbound[number_of_sections_before_intersection - 1];
                        eastbound[number_of_sections_before_intersection - 1] = nullptr;
                        eSTILL = truck;
                    }
                }
            }
            else if (eSTILL > 0) {
                eastbound[number_of_sections_before_intersection] = eastbound[number_of_sections_before_intersection - 1];
                eastbound[number_of_sections_before_intersection - 1] = nullptr;
                eSTILL--;
            }
        }
        else {

        }
        //right (deprioritized)
        if (westbound[number_of_sections_before_intersection - 1] != nullptr && westbound[number_of_sections_before_intersection - 1]->getVehicleOriginalDirection() == Direction::north) {
            if (wSTILL == 0 && northbound[number_of_sections_before_intersection + 1] == nullptr && !((eastbound[number_of_sections_before_intersection] != nullptr && eastbound[number_of_sections_before_intersection]->getVehicleOriginalDirection() == Direction::north) || (northbound[number_of_sections_before_intersection] != nullptr && northbound[number_of_sections_before_intersection]->getVehicleOriginalDirection() == Direction::north) || (eastbound[number_of_sections_before_intersection - 1] != nullptr && eastbound[number_of_sections_before_intersection - 1]->getVehicleOriginalDirection() == Direction::north))) {
                //car
                if (westbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::car) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south + green_east_west + yellow_east_west) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 2) {
                        northbound[number_of_sections_before_intersection + 1] = westbound[number_of_sections_before_intersection - 1];
                        westbound[number_of_sections_before_intersection - 1] = nullptr;
                        wSTILL = car;
                    }
                }

                //suv
                else if (westbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::suv) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south + green_east_west + yellow_east_west) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 3) {
                        northbound[number_of_sections_before_intersection + 1] = westbound[number_of_sections_before_intersection - 1];
                        westbound[number_of_sections_before_intersection - 1] = nullptr;
                        wSTILL = suv;
                    }
                }

                //truck
                else if (westbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::truck) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south + green_east_west + yellow_east_west) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 4) {
                        northbound[number_of_sections_before_intersection + 1] = westbound[number_of_sections_before_intersection - 1];
                        westbound[number_of_sections_before_intersection - 1] = nullptr;
                        wSTILL = truck;
                    }
                }
            }
            else if (wSTILL > 0) {
                northbound[number_of_sections_before_intersection + 1] = westbound[number_of_sections_before_intersection - 1];
                westbound[number_of_sections_before_intersection - 1] = nullptr;
                wSTILL--;
            }
        }
        // straight (deprioritized)
        else if (westbound[number_of_sections_before_intersection - 1] != nullptr && westbound[number_of_sections_before_intersection - 1]->getVehicleOriginalDirection() == Direction::west) {
            if (wSTILL == 0 && northbound[number_of_sections_before_intersection + 1] == nullptr && !((eastbound[number_of_sections_before_intersection] != nullptr && eastbound[number_of_sections_before_intersection]->getVehicleOriginalDirection() == Direction::north) || (northbound[number_of_sections_before_intersection] != nullptr && northbound[number_of_sections_before_intersection]->getVehicleOriginalDirection() == Direction::north) || (eastbound[number_of_sections_before_intersection - 1] != nullptr && eastbound[number_of_sections_before_intersection - 1]->getVehicleOriginalDirection() == Direction::north))) {
                //car
                if (westbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::car) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south + green_east_west + yellow_east_west) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 4) {
                        westbound[number_of_sections_before_intersection] = westbound[number_of_sections_before_intersection - 1];
                        westbound[number_of_sections_before_intersection - 1] = nullptr;
                        wSTILL = car;
                    }
                }

                //suv
                else if (westbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::suv) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south + green_east_west + yellow_east_west) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 5) {
                        westbound[number_of_sections_before_intersection] = westbound[number_of_sections_before_intersection - 1];
                        westbound[number_of_sections_before_intersection - 1] = nullptr;
                        wSTILL = suv;
                    }
                }

                //truck
                else if (westbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::truck) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south + green_east_west + yellow_east_west) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 6) {
                        westbound[number_of_sections_before_intersection] = westbound[number_of_sections_before_intersection - 1];
                        westbound[number_of_sections_before_intersection - 1] = nullptr;
                        wSTILL = truck;
                    }
                }
            }
            else if (wSTILL > 0) {
                westbound[number_of_sections_before_intersection] = westbound[number_of_sections_before_intersection - 1];
                westbound[number_of_sections_before_intersection - 1] = nullptr;
                wSTILL--;
            }
        }
        else {

        }
    }
    //southbound prioritized
    else if (ENpriority == false && NSmove == true) {
        //right turn (prioritized)
        if (southbound[number_of_sections_before_intersection - 1] != nullptr && southbound[number_of_sections_before_intersection - 1]->getVehicleOriginalDirection() == Direction::west) {
            if (sSTILL == 0 && westbound[number_of_sections_before_intersection + 1] == nullptr) {
                //car
                if (southbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::car) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 2) {
                        westbound[number_of_sections_before_intersection + 1] = southbound[number_of_sections_before_intersection - 1];
                        southbound[number_of_sections_before_intersection - 1] = nullptr;
                        sSTILL = car;
                    }
                }

                //suv
                else if (southbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::suv) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 3) {
                        westbound[number_of_sections_before_intersection + 1] = southbound[number_of_sections_before_intersection - 1];
                        southbound[number_of_sections_before_intersection - 1] = nullptr;
                        sSTILL = suv;
                    }
                }

                //truck
                else if (southbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::truck) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 4) {
                        westbound[number_of_sections_before_intersection + 1] = southbound[number_of_sections_before_intersection - 1];
                        southbound[number_of_sections_before_intersection - 1] = nullptr;
                        sSTILL = truck;
                    }
                }
            }
            else if (sSTILL > 0) {
                westbound[number_of_sections_before_intersection + 1] = southbound[number_of_sections_before_intersection - 1];
                southbound[number_of_sections_before_intersection - 1] = nullptr;
                sSTILL--;
            }
        }
        //straight (prioritized)
        else if (southbound[number_of_sections_before_intersection - 1] != nullptr && southbound[number_of_sections_before_intersection - 1]->getVehicleOriginalDirection() == Direction::south) {
            if (sSTILL == 0 && southbound[number_of_sections_before_intersection] == nullptr) {
                //car
                if (southbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::car) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 4) {
                        southbound[number_of_sections_before_intersection] = southbound[number_of_sections_before_intersection - 1];
                        southbound[number_of_sections_before_intersection - 1] = nullptr;
                        sSTILL = car;
                    }
                }

                //suv
                else if (southbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::suv) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 5) {
                        southbound[number_of_sections_before_intersection] = southbound[number_of_sections_before_intersection - 1];
                        southbound[number_of_sections_before_intersection - 1] = nullptr;
                        sSTILL = suv;
                    }
                }

                //truck
                else if (southbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::truck) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 6) {
                        southbound[number_of_sections_before_intersection] = southbound[number_of_sections_before_intersection - 1];
                        southbound[number_of_sections_before_intersection - 1] = nullptr;
                        sSTILL = truck;
                    }
                }
            }
            else if (sSTILL > 0) {
                southbound[number_of_sections_before_intersection] = southbound[number_of_sections_before_intersection - 1];
                southbound[number_of_sections_before_intersection - 1] = nullptr;
                sSTILL--;
            }
        }
        //left turn (prioritized)
        else if (southbound[number_of_sections_before_intersection - 1] != nullptr && southbound[number_of_sections_before_intersection - 1]->getVehicleOriginalDirection() == Direction::east) {
            if (sSTILL == 0 && southbound[number_of_sections_before_intersection] == nullptr && !(northbound[number_of_sections_before_intersection] != nullptr && northbound[number_of_sections_before_intersection] == northbound[number_of_sections_before_intersection - 1] && northbound[number_of_sections_before_intersection - 1] == northbound[number_of_sections_before_intersection - 2])) {
                //car
                if (southbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::car) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 4) {
                        southbound[number_of_sections_before_intersection] = southbound[number_of_sections_before_intersection - 1];
                        southbound[number_of_sections_before_intersection - 1] = nullptr;
                        sSTILL = car;
                    }
                }

                //suv
                else if (southbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::suv) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 5) {
                        southbound[number_of_sections_before_intersection] = southbound[number_of_sections_before_intersection - 1];
                        southbound[number_of_sections_before_intersection - 1] = nullptr;
                        sSTILL = suv;
                    }
                }

                //truck
                else if (southbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::truck) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 6) {
                        southbound[number_of_sections_before_intersection] = southbound[number_of_sections_before_intersection - 1];
                        southbound[number_of_sections_before_intersection - 1] = nullptr;
                        sSTILL = truck;
                    }
                }
            }
            else if (sSTILL > 0) {
                southbound[number_of_sections_before_intersection] = southbound[number_of_sections_before_intersection - 1];
                southbound[number_of_sections_before_intersection - 1] = nullptr;
                sSTILL--;
            }
        }
        else {

        }
        
        //right (deprioritized)
        if (northbound[number_of_sections_before_intersection - 1] != nullptr && northbound[number_of_sections_before_intersection - 1]->getVehicleOriginalDirection() == Direction::east) {
            if (nSTILL == 0 && eastbound[number_of_sections_before_intersection + 1] == nullptr && !((southbound[number_of_sections_before_intersection] != nullptr && southbound[number_of_sections_before_intersection]->getVehicleOriginalDirection() == Direction::east) || (eastbound[number_of_sections_before_intersection] != nullptr && eastbound[number_of_sections_before_intersection]->getVehicleOriginalDirection() == Direction::east) || (southbound[number_of_sections_before_intersection - 1] != nullptr && southbound[number_of_sections_before_intersection - 1]->getVehicleOriginalDirection() == Direction::east))) {
                //car
                if (northbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::car) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 2) {
                        eastbound[number_of_sections_before_intersection + 1] = northbound[number_of_sections_before_intersection - 1];
                        northbound[number_of_sections_before_intersection - 1] = nullptr;
                        nSTILL = car;
                    }
                }

                //suv
                else if (northbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::suv) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 3) {
                        eastbound[number_of_sections_before_intersection + 1] = northbound[number_of_sections_before_intersection - 1];
                        northbound[number_of_sections_before_intersection - 1] = nullptr;
                        nSTILL = suv;
                    }
                }

                //truck
                else if (northbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::truck) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 4) {
                        eastbound[number_of_sections_before_intersection + 1] = northbound[number_of_sections_before_intersection - 1];
                        northbound[number_of_sections_before_intersection - 1] = nullptr;
                        nSTILL = truck;
                    }
                }
            }
            else if (nSTILL > 0) {
                eastbound[number_of_sections_before_intersection + 1] = northbound[number_of_sections_before_intersection - 1];
                northbound[number_of_sections_before_intersection - 1] = nullptr;
                nSTILL--;
            }
        }
        // straight (deprioritized)
        else if (northbound[number_of_sections_before_intersection - 1] != nullptr && northbound[number_of_sections_before_intersection - 1]->getVehicleOriginalDirection() == Direction::north) {
            if (nSTILL == 0 && eastbound[number_of_sections_before_intersection + 1] == nullptr && !((southbound[number_of_sections_before_intersection] != nullptr && southbound[number_of_sections_before_intersection]->getVehicleOriginalDirection() == Direction::east) || (eastbound[number_of_sections_before_intersection] != nullptr && eastbound[number_of_sections_before_intersection]->getVehicleOriginalDirection() == Direction::east) || (southbound[number_of_sections_before_intersection - 1] != nullptr && southbound[number_of_sections_before_intersection - 1]->getVehicleOriginalDirection() == Direction::east))) {
                //car
                if (northbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::car) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 4) {
                        northbound[number_of_sections_before_intersection] = northbound[number_of_sections_before_intersection - 1];
                        northbound[number_of_sections_before_intersection - 1] = nullptr;
                        nSTILL = car;
                    }
                }

                //suv
                else if (northbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::suv) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 5) {
                        northbound[number_of_sections_before_intersection] = northbound[number_of_sections_before_intersection - 1];
                        northbound[number_of_sections_before_intersection - 1] = nullptr;
                        nSTILL = suv;
                    }
                }

                //truck
                else if (northbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::truck) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 6) {
                        northbound[number_of_sections_before_intersection] = northbound[number_of_sections_before_intersection - 1];
                        northbound[number_of_sections_before_intersection - 1] = nullptr;
                        nSTILL = truck;
                    }
                }
            }
            else if (nSTILL > 0) {
                northbound[number_of_sections_before_intersection] = northbound[number_of_sections_before_intersection - 1];
                northbound[number_of_sections_before_intersection - 1] = nullptr;
                nSTILL--;
            }
        }
        else {

        }
    }
    //westbound prioritized
    else if (ENpriority == false && NSmove == false) {
        //right turn (prioritized)
        if (westbound[number_of_sections_before_intersection - 1] != nullptr && westbound[number_of_sections_before_intersection - 1]->getVehicleOriginalDirection() == Direction::north) {
            if (wSTILL == 0 && northbound[number_of_sections_before_intersection + 1] == nullptr) {
                //car
                if (westbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::car) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south + green_east_west + yellow_east_west) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 2) {
                        northbound[number_of_sections_before_intersection + 1] = westbound[number_of_sections_before_intersection - 1];
                        westbound[number_of_sections_before_intersection - 1] = nullptr;
                        wSTILL = car;
                    }
                }

                //suv
                else if (westbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::suv) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south + green_east_west + yellow_east_west) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 3) {
                        northbound[number_of_sections_before_intersection + 1] = westbound[number_of_sections_before_intersection - 1];
                        westbound[number_of_sections_before_intersection - 1] = nullptr;
                        wSTILL = suv;
                    }
                }

                //truck
                else if (westbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::truck) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south + green_east_west + yellow_east_west) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 4) {
                        northbound[number_of_sections_before_intersection + 1] = westbound[number_of_sections_before_intersection - 1];
                        westbound[number_of_sections_before_intersection - 1] = nullptr;
                        wSTILL = truck;
                    }
                }
            }
            else if (wSTILL > 0) {
                northbound[number_of_sections_before_intersection + 1] = westbound[number_of_sections_before_intersection - 1];
                westbound[number_of_sections_before_intersection - 1] = nullptr;
                wSTILL--;
            }
        }
        //straight (prioritized)
        else if (westbound[number_of_sections_before_intersection - 1] != nullptr && westbound[number_of_sections_before_intersection - 1]->getVehicleOriginalDirection() == Direction::west) {
            if (wSTILL == 0 && westbound[number_of_sections_before_intersection] == nullptr) {
                //car
                if (westbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::car) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south + green_east_west + yellow_east_west) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 4) {
                        westbound[number_of_sections_before_intersection] = westbound[number_of_sections_before_intersection - 1];
                        westbound[number_of_sections_before_intersection - 1] = nullptr;
                        wSTILL = car;
                    }
                }

                //suv
                else if (westbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::suv) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south + green_east_west + yellow_east_west) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 5) {
                        westbound[number_of_sections_before_intersection] = westbound[number_of_sections_before_intersection - 1];
                        westbound[number_of_sections_before_intersection - 1] = nullptr;
                        wSTILL = suv;
                    }
                }

                //truck
                else if (westbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::truck) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south + green_east_west + yellow_east_west) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 6) {
                        westbound[number_of_sections_before_intersection] = westbound[number_of_sections_before_intersection - 1];
                        westbound[number_of_sections_before_intersection - 1] = nullptr;
                        wSTILL = truck;
                    }
                }
            }
            else if (wSTILL > 0) {
                westbound[number_of_sections_before_intersection] = westbound[number_of_sections_before_intersection - 1];
                westbound[number_of_sections_before_intersection - 1] = nullptr;
                wSTILL--;
            }
        }
        //left turn (prioritized)
        else if (westbound[number_of_sections_before_intersection - 1] != nullptr && westbound[number_of_sections_before_intersection - 1]->getVehicleOriginalDirection() == Direction::south) {
            if (wSTILL == 0 && westbound[number_of_sections_before_intersection] == nullptr && !(eastbound[number_of_sections_before_intersection] != nullptr && eastbound[number_of_sections_before_intersection] == eastbound[number_of_sections_before_intersection - 1] && eastbound[number_of_sections_before_intersection - 1] == eastbound[number_of_sections_before_intersection - 2])) {
                //car
                if (westbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::car) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south + green_east_west + yellow_east_west) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 4) {
                        westbound[number_of_sections_before_intersection] = westbound[number_of_sections_before_intersection - 1];
                        westbound[number_of_sections_before_intersection - 1] = nullptr;
                        wSTILL = car;
                    }
                }

                //suv
                else if (westbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::suv) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south + green_east_west + yellow_east_west) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 5) {
                        westbound[number_of_sections_before_intersection] = westbound[number_of_sections_before_intersection - 1];
                        westbound[number_of_sections_before_intersection - 1] = nullptr;
                        wSTILL = suv;
                    }
                }

                //truck
                else if (westbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::truck) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south + green_east_west + yellow_east_west) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 6) {
                        westbound[number_of_sections_before_intersection] = westbound[number_of_sections_before_intersection - 1];
                        westbound[number_of_sections_before_intersection - 1] = nullptr;
                        wSTILL = truck;
                    }
                }
            }
            else if (wSTILL > 0) {
                westbound[number_of_sections_before_intersection] = westbound[number_of_sections_before_intersection - 1];
                westbound[number_of_sections_before_intersection - 1] = nullptr;
                wSTILL--;
            }
        }
        else {

        }
        //right (deprioritized)
        if (eastbound[number_of_sections_before_intersection - 1] != nullptr && eastbound[number_of_sections_before_intersection - 1]->getVehicleOriginalDirection() == Direction::south) {
            if (eSTILL == 0 && southbound[number_of_sections_before_intersection + 1] == nullptr && !((westbound[number_of_sections_before_intersection] != nullptr && westbound[number_of_sections_before_intersection]->getVehicleOriginalDirection() == Direction::south) || (southbound[number_of_sections_before_intersection] != nullptr && southbound[number_of_sections_before_intersection]->getVehicleOriginalDirection() == Direction::south) || (westbound[number_of_sections_before_intersection - 1] != nullptr && westbound[number_of_sections_before_intersection - 1]->getVehicleOriginalDirection() == Direction::south))) {
                //car
                if (eastbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::car) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south + green_east_west + yellow_east_west) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 2) {
                        southbound[number_of_sections_before_intersection + 1] = eastbound[number_of_sections_before_intersection - 1];
                        eastbound[number_of_sections_before_intersection - 1] = nullptr;
                        eSTILL = car;
                    }
                }

                //suv
                else if (eastbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::suv) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south + green_east_west + yellow_east_west) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 3) {
                        southbound[number_of_sections_before_intersection + 1] = eastbound[number_of_sections_before_intersection - 1];
                        eastbound[number_of_sections_before_intersection - 1] = nullptr;
                        eSTILL = suv;
                    }
                }

                //truck
                else if (eastbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::truck) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south + green_east_west + yellow_east_west) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 4) {
                        southbound[number_of_sections_before_intersection + 1] = eastbound[number_of_sections_before_intersection - 1];
                        eastbound[number_of_sections_before_intersection - 1] = nullptr;
                        eSTILL = truck;
                    }
                }
            }
            else if (eSTILL > 0) {
                southbound[number_of_sections_before_intersection + 1] = eastbound[number_of_sections_before_intersection - 1];
                eastbound[number_of_sections_before_intersection - 1] = nullptr;
                eSTILL--;
            }
        }
        // straight (deprioritized)
        else if (eastbound[number_of_sections_before_intersection - 1] != nullptr && eastbound[number_of_sections_before_intersection - 1]->getVehicleOriginalDirection() == Direction::east) {
            if (eSTILL == 0 && southbound[number_of_sections_before_intersection + 1] == nullptr && !((westbound[number_of_sections_before_intersection] != nullptr && westbound[number_of_sections_before_intersection]->getVehicleOriginalDirection() == Direction::south) || (southbound[number_of_sections_before_intersection] != nullptr && southbound[number_of_sections_before_intersection]->getVehicleOriginalDirection() == Direction::south) || (westbound[number_of_sections_before_intersection - 1] != nullptr && westbound[number_of_sections_before_intersection - 1]->getVehicleOriginalDirection() == Direction::south))) {
                //car
                if (eastbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::car) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south + green_east_west + yellow_east_west) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 4) {
                        eastbound[number_of_sections_before_intersection] = eastbound[number_of_sections_before_intersection - 1];
                        eastbound[number_of_sections_before_intersection - 1] = nullptr;
                        eSTILL = car;
                    }
                }

                //suv
                else if (eastbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::suv) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south + green_east_west + yellow_east_west) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 5) {
                        eastbound[number_of_sections_before_intersection] = eastbound[number_of_sections_before_intersection - 1];
                        eastbound[number_of_sections_before_intersection - 1] = nullptr;
                        eSTILL = suv;
                    }
                }

                //truck
                else if (eastbound[number_of_sections_before_intersection - 1]->getVehicleType() == VehicleType::truck) {
                    //calculate whether there's time left
                    if ((green_north_south + yellow_north_south + green_east_west + yellow_east_west) - (i % (green_north_south + yellow_north_south + green_east_west + yellow_east_west)) >= 6) {
                        eastbound[number_of_sections_before_intersection] = eastbound[number_of_sections_before_intersection - 1];
                        eastbound[number_of_sections_before_intersection - 1] = nullptr;
                        eSTILL = truck;
                    }
                }
            }
            else if (eSTILL > 0) {
                eastbound[number_of_sections_before_intersection] = eastbound[number_of_sections_before_intersection - 1];
                eastbound[number_of_sections_before_intersection - 1] = nullptr;
                eSTILL--;
            }
        }
        else {

        }
    }
    
    

    // THIS IS FOR SCOOCHING EVERY CAR BEHIND THE INTERSECTION FORWARD
        //east
        for (int i = number_of_sections_before_intersection - 1; i > 0; i--) {
            if (eastbound[i] == nullptr) {
                e_maderoom = true;
                eastbound[i] = eastbound[i-1];
                eastbound[i-1] = nullptr;
            }
        }
        //west
        for (int i = number_of_sections_before_intersection - 1; i > 0; i--) {
            if (westbound[i] == nullptr) {
                w_maderoom = true;
                westbound[i] = westbound[i-1];
                westbound[i-1] = nullptr;
            }
        }
        //north
        for (int i = number_of_sections_before_intersection - 1; i > 0; i--) {
            if (northbound[i] == nullptr) {
                n_maderoom = true;
                northbound[i] = northbound[i-1];
                northbound[i-1] = nullptr;
            }
        }
        //south
        for (int i = number_of_sections_before_intersection - 1; i > 0; i--) {
            if (southbound[i] == nullptr) {
                s_maderoom = true;
                southbound[i] = southbound[i-1];
                southbound[i-1] = nullptr;
            }
        }

    // THIS IS FOR INITIALIZING THE ENDS OF THE LANES WITH VEHICLES, LEFT TURNS ENABLED
    
        if (eastbound[0] == nullptr && timer_east == 0) {
            prob = rand_double(rng);
            if (prob <= prob_new_vehicle_eastbound) {
                prob = rand_double(rng);
                //cars
                if (prob <= proportion_of_cars) {
                    //vehicle_type = "car";
                    prob = rand_double(rng);
                    if (prob <= proportion_right_turn_cars) {
                        //turn = "right";
                        //construct southbound car at
                        eastbound[0] = new VehicleBase(VehicleType::car, Direction::south);
                    }
                    else if (prob > proportion_right_turn_cars && prob <= proportion_right_turn_cars + proportion_left_turn_cars) {
                        //turn = "left";
                        //construct northbound car
                        eastbound[0] = new VehicleBase(VehicleType::car, Direction::north);
                    }
                    else {
                        //turn = "straight";
                        //construct eastbound car
                        eastbound[0] = new VehicleBase(VehicleType::car, Direction::east);
                    }
                    timer_east = 1;
                }
                else if (prob > proportion_of_cars && prob <= proportion_of_cars + proportion_of_SUVs) {
                    //vehicle_type = "suv";
                    prob = rand_double(rng);
                    if (prob <= proportion_right_turn_SUVs) {
                        //turn = "right";
                        //construct southbound suv
                        eastbound[0] = new VehicleBase(VehicleType::suv, Direction::south);
                    }
                    else if (prob > proportion_right_turn_SUVs && prob <= proportion_right_turn_SUVs + proportion_left_turn_SUVs) {
                        //turn = "left";
                        //construct northbound suv
                        eastbound[0] = new VehicleBase(VehicleType::suv, Direction::north);
                    }
                    else {
                        //turn = "straight";
                        //construct eastbound suv
                        eastbound[0] = new VehicleBase(VehicleType::suv, Direction::east);
                    }
                    timer_east = 2;
                }
                else {
                    //vehicle_type = "truck";
                    prob = rand_double(rng);
                    if (prob <= proportion_right_turn_trucks) {
                        //turn = "right";
                        //construct southbound truck
                        eastbound[0] = new VehicleBase(VehicleType::truck, Direction::south);
                    }
                    else if (prob > proportion_right_turn_trucks && prob <= proportion_right_turn_trucks + proportion_left_turn_trucks) {
                        //turn = "left";
                        //construct northbound truck
                        eastbound[0] = new VehicleBase(VehicleType::truck, Direction::north);
                    }
                    else {
                        //turn = "straight";
                        //construct eastbound truck
                        eastbound[0] = new VehicleBase(VehicleType::truck, Direction::east);
                    }
                    timer_east = 3;
                }
            }
        }
        else if (timer_east > 0 && e_maderoom) {
            eastbound[0] = eastbound[1];
            timer_east--;
        }
        else {
            
        }

        if (westbound[0] == nullptr && timer_west == 0) {
            prob = rand_double(rng);
            if (prob <= prob_new_vehicle_westbound) {
                prob = rand_double(rng);
                //cars
                if (prob <= proportion_of_cars) {
                    //vehicle_type = "car";
                    prob = rand_double(rng);
                    if (prob <= proportion_right_turn_cars) {
                        //turn = "right";
                        //construct northbound car
                        westbound[0] = new VehicleBase(VehicleType::car, Direction::north);
                    }
                    else if (prob > proportion_right_turn_cars && prob <= proportion_right_turn_cars + proportion_left_turn_cars) {
                        //turn = "left";
                        //construct southbound car
                        westbound[0] = new VehicleBase(VehicleType::car, Direction::south);
                    }
                    else {
                        //turn = "straight";
                        //construct westbound car
                        westbound[0] = new VehicleBase(VehicleType::car, Direction::west);
                    }
                    timer_west = 1;
                }
                else if (prob > proportion_of_cars && prob <= proportion_of_cars + proportion_of_SUVs) {
                    //vehicle_type = "suv";
                    prob = rand_double(rng);
                    if (prob <= proportion_right_turn_SUVs) {
                        //turn = "right";
                        //construct northbound SUV
                        westbound[0] = new VehicleBase(VehicleType::suv, Direction::north);
                    }
                    else if (prob > proportion_right_turn_SUVs && prob <= proportion_right_turn_SUVs + proportion_left_turn_SUVs) {
                        //turn = "left";
                        //construct southbound SUV
                        westbound[0] = new VehicleBase(VehicleType::suv, Direction::south);
                    }
                    else {
                        //turn = "straight";
                        //construct westbound suv
                        westbound[0] = new VehicleBase(VehicleType::suv, Direction::west);
                    }
                    timer_west = 2;
                }
                else {
                    //vehicle_type = "truck";
                    prob = rand_double(rng);
                    if (prob <= proportion_right_turn_trucks) {
                        //turn = "right";
                        //construct northbound truck
                        westbound[0] = new VehicleBase(VehicleType::truck, Direction::north);
                    }
                    else if (prob > proportion_right_turn_trucks && prob <= proportion_right_turn_trucks + proportion_left_turn_trucks) {
                        //turn = "left";
                        //construct southbound truck
                        westbound[0] = new VehicleBase(VehicleType::truck, Direction::south);
                    }
                    else {
                        //turn = "straight";
                        //construct westbound truck
                        westbound[0] = new VehicleBase(VehicleType::truck, Direction::west);
                    }
                    timer_west = 3;
                }
            }
            //call vehiclebase constructor using initialized fields and also other things
        }
        else if (timer_west > 0 && w_maderoom) {
            westbound[0] = westbound[1];
            timer_west--;
        }
        else {
            
        }

        if (northbound[0] == nullptr && timer_north == 0) {
            prob = rand_double(rng);
            if (prob <= prob_new_vehicle_northbound) {
                prob = rand_double(rng);
                //cars
                if (prob <= proportion_of_cars) {
                    //vehicle_type = "car";
                    prob = rand_double(rng);
                    if (prob <= proportion_right_turn_cars) {
                        //turn = "right";
                        //construct eastbound car
                        northbound[0] = new VehicleBase(VehicleType::car, Direction::east);
                    }
                    else if (prob > proportion_right_turn_cars && prob <= proportion_right_turn_cars + proportion_left_turn_cars) {
                        //turn = "left";
                        //construct westbound car
                        northbound[0] = new VehicleBase(VehicleType::car, Direction::west);
                    }
                    else {
                        //turn = "straight";
                        //construct northbound car
                        northbound[0] = new VehicleBase(VehicleType::car, Direction::north);
                    }
                    timer_north = 1;
                }
                else if (prob > proportion_of_cars && prob <= proportion_of_cars + proportion_of_SUVs) {
                    //vehicle_type = "suv";
                    prob = rand_double(rng);
                    if (prob <= proportion_right_turn_SUVs) {
                        //turn = "right";
                        //construct eastbound suv
                        northbound[0] = new VehicleBase(VehicleType::suv, Direction::east);
                    }
                    else if (prob > proportion_right_turn_SUVs && prob <= proportion_right_turn_SUVs + proportion_left_turn_SUVs) {
                        //turn = "left";
                        //construct westbound suv
                        northbound[0] = new VehicleBase(VehicleType::suv, Direction::west);
                    }
                    else {
                        //turn = "straight";
                        //construct northbound suv
                        northbound[0] = new VehicleBase(VehicleType::suv, Direction::north);
                    }
                    timer_north = 2;
                }
                else {
                    //vehicle_type = "truck";
                    prob = rand_double(rng);
                    if (prob <= proportion_right_turn_trucks) {
                        //turn = "right";
                        //construct eastbound truck
                        northbound[0] = new VehicleBase(VehicleType::truck, Direction::east);
                    }
                    else if (prob > proportion_right_turn_trucks && prob <= proportion_right_turn_trucks + proportion_left_turn_trucks) {
                        //turn = "left";
                        //construct westbound truck
                        northbound[0] = new VehicleBase(VehicleType::truck, Direction::west);
                    }
                    else {
                        //turn = "straight";
                        //construct northbound truck
                        northbound[0] = new VehicleBase(VehicleType::truck, Direction::north);
                    }
                    timer_north = 3;
                }
            }
            //call vehiclebase constructor using initialized fields and also other things
        }
        else if (timer_north > 0 && n_maderoom) {
            northbound[0] = northbound[1];
            timer_north--;
        }
        else {
            
        }

        if (southbound[0] == nullptr && timer_south == 0) {
            prob = rand_double(rng);
            if (prob <= prob_new_vehicle_southbound) {
                prob = rand_double(rng);
                //cars
                if (prob <= proportion_of_cars) {
                    //vehicle_type = "car";
                    prob = rand_double(rng);
                    if (prob <= proportion_right_turn_cars) {
                        //turn = "right";
                        //construct west
                        southbound[0] = new VehicleBase(VehicleType::car, Direction::west);
                    }
                    else if (prob > proportion_right_turn_cars && prob <= proportion_right_turn_cars + proportion_left_turn_cars) {
                        //turn = "left";
                        //construct east
                        southbound[0] = new VehicleBase(VehicleType::car, Direction::east);
                    }
                    else {
                        //turn = "straight";
                        //construct south
                        southbound[0] = new VehicleBase(VehicleType::car, Direction::south);
                    }
                    timer_south = 1;
                }
                else if (prob > proportion_of_cars && prob <= proportion_of_cars + proportion_of_SUVs) {
                    //vehicle_type = "suv";
                    prob = rand_double(rng);
                    if (prob <= proportion_right_turn_SUVs) {
                        //turn = "right"; west
                        southbound[0] = new VehicleBase(VehicleType::suv, Direction::west);
                    }
                    else if (prob > proportion_right_turn_SUVs && prob <= proportion_right_turn_SUVs + proportion_left_turn_SUVs) {
                        //turn = "left"; east
                        southbound[0] = new VehicleBase(VehicleType::suv, Direction::east);
                    }
                    else {
                        //turn = "straight"; south
                        southbound[0] = new VehicleBase(VehicleType::suv, Direction::south);
                    }
                    timer_south = 2;
                }
                else {
                    //vehicle_type = "truck";
                    prob = rand_double(rng);
                    if (prob <= proportion_right_turn_trucks) {
                        //turn = "right"; west
                        southbound[0] = new VehicleBase(VehicleType::truck, Direction::west);
                    }
                    else if (prob > proportion_right_turn_trucks && prob <= proportion_right_turn_trucks + proportion_left_turn_trucks) {
                        //turn = "left"; east
                        southbound[0] = new VehicleBase(VehicleType::truck, Direction::east);
                    }
                    else {
                        //turn = "straight"; south
                        southbound[0] = new VehicleBase(VehicleType::truck, Direction::south);
                    }
                    timer_south = 3;
                }
            }
            //call vehiclebase constructor using initialized fields and also other things
        }
        else if (timer_south > 0 && s_maderoom) {
            southbound[0] = southbound[1];
            timer_south--;
        }
        else {
            
        }

        // setting the vehicles

        e_maderoom = false;
        w_maderoom = false;
        n_maderoom = false;
        s_maderoom = false;
        
        anim.setVehiclesNorthbound(northbound);
        anim.setVehiclesWestbound(westbound);
        anim.setVehiclesSouthbound(southbound);
        anim.setVehiclesEastbound(eastbound);
        
        anim.draw(i + 1);

        cin.get(dummy);
    }
    return 0;
}