// Ameya Bahirat
// Fall 2014
// Homework 6 Problem 1
// This program takes in a series of input values and applies a calculation using them to get a passer rating


#include <iostream>
#include <iomanip> //Allows us to use setprecision
using namespace std;

int main()

{
double pass_attempts, pass_completions, passing_yards, touchdowns, interceptions; //Defines all numbers as integer

cout << "Enter # of pass attempts " << endl; //Series of inputs are converted to integer variables
cin >> pass_attempts;
cout << "Enter # of pass completions " << endl;
cin >> pass_completions;
cout << "Enter total passing yards " << endl;
cin >> passing_yards;
cout << "Enter # of touchdowns " << endl;
cin >> touchdowns;
cout << "Enter # of interceptions " << endl;
cin >> interceptions;

double C = (pass_completions/pass_attempts - 0.30)*5; //Application of equations
double Y = (passing_yards/pass_attempts - 3) *0.25;
double T = touchdowns/pass_attempts * 20; 
double I = 2.375 - (interceptions/pass_attempts * 25);

double PasserRating = (C + Y + I + T)/6 * 100;

cout << fixed <<  setprecision(1) << "The passer rating is: " << PasserRating << endl; //Final output

}
