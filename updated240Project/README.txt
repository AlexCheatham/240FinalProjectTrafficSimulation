
How to compile/run this code:
To compile and run this code, you will need:
    Animator.cpp
    Animator.h
    Simulator.cpp
    VehicleBase.cpp
    VehicleBase.h
    Makefile
    inputfile.txt
    An integer to be chosen as a seed for a random number generator
All of these files must be in the same directory, as Animator.cpp depends on its header, VehicleBase.cpp depends on its header as well,
and Simulator.cpp depends on Animator.cpp and VehicleBase.cpp. To compile the program, just type "make" into the command line,
and the Makefile will compile the code. On first run it will create an executable called "Simulator," and on subsequent compiles,
will delete the old executable via clean in the Makefile and generate a new executable.

The code takes two command line arguments. The first is the inputfile, specified earlier, and the proper way the inputfile should be
created will be included later in this README. The inputfile has to be a file of strings, with specific variable names. The second
argument is an integer that will be used as a seed for a random number generator. Below is the proper syntax for using the executable:
Usage: ./simulator [input file] [initial seed]
The above syntax is also thrown when someone attempts to run the executable without the proper command line arguments.

The inputfile must be a text file that has strings with specific variable names, followed by ':', followed by whitespace then either
an int or double. Below are the variable names that must be used for the code to run.

These values MUST be integers, and have sample values included to show their usage:
maximum_simulated_time:                 1000
number_of_sections_before_intersection:   10
green_north_south:                        12
yellow_north_south:                        3
green_east_west:                          10
yellow_east_west:                          3

These values MUST be doubles, and have sample values included to show their usage:
prob_new_vehicle_northbound:               0.25
prob_new_vehicle_southbound:               0.1
prob_new_vehicle_eastbound:                0.15
prob_new_vehicle_westbound:                0.15
proportion_of_cars:                        0.6
proportion_of_SUVs:                        0.3
proportion_right_turn_cars:                0.4
proportion_left_turn_cars:                 0.1
proportion_right_turn_SUVs:                0.3
proportion_left_turn_SUVs:                 0.05
proportion_right_turn_trucks:              0.2
proportion_left_turn_trucks:               0.02

Both of the integers and doubles variables must be in the same file, but they can be in any order as long as they follow the style
above. There should be AT LEAST 4 spaces between the ':' that IMMEDIATELY follows the variable name, and the int/double values to
ensure proper behavior of the code. For best usage just directly copy the variables and their values from above into a text file
and edit them to your desired values.

Once the program is compiled and the proper command line arguments have been input, a traffic intersection will appear with
lights and possibly the very front of some vehicles. This is normal and how it should look. To move forward in the simulation,
press the "enter" or "return" key to move forward one unit of time. Press ctrl+C to end the simulation early.