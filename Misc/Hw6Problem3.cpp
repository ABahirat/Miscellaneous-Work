// Ameya Bahirat
// Fall 2014
// Homework 6 Problem 3
// This program takes in a given population and outputs the population after one year after the inclusion of birth, death, and immigration rates. 


#include <iostream>
using namespace std;

int main()


{
	
	int Population = 307357870; //Initial Population
	int time = 365 * 24 * 60 * 60; //Seconds in a year
	
	int birth_rate_inclusion = Population + time/7; // Population after birth rate
	
	int death_rate_inclusion = birth_rate_inclusion - time/13; // Population after death rate
	
	int Immigration_rate = death_rate_inclusion + time/35; //Population after immigration rate
	
	cout << "The population will be " << Immigration_rate << " people" << endl; //Final output

}
