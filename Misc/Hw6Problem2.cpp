// Ameya Bahirat
// Fall 2014
// Homework 6 Problem 2
// This program takes an command line argument given in seconds and breaks it down into hours minutes and seconds


#include <iostream>
#include <string> //Allows us to use stoi
using namespace std;

int main( int argc, char * argv[]) // Allows us to use command line arguments
{

	double hours = 0;
	double minutes = 0;
	double seconds = 0;
	double total_seconds = stoi(argv[1]); //takes CLA and converts it into an integer variable



while (total_seconds > 0)
{
	if (total_seconds > 3600){ //Takes out number of seconds in an hour to obtain hours
		hours ++;
		total_seconds -= 3600;}
	else if (total_seconds > 60){ //Takes out number of seconds in a minute ot obtain minutes
		minutes ++;
		total_seconds -= 60;}
	else {                        // Takes everything else and applies it to seconds
		seconds = total_seconds;
		total_seconds = 0;}
		
}

cout << "The time is " << hours << " hours, " << minutes << " minutes, " << "and " << seconds << " seconds" << endl; //Final output
		
			
	
	
}
