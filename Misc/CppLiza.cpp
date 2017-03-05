//Ameya Bahirat
//Fall 2014
//Assignemnt #8
//Takes in a file, splits the information into a 2 columned array and matches input with set output via the array




#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main(int argc, char * argv[])
{
	ifstream responses(argv[1]);
	string responseArray[100][2]; // Establishes Array as 100 rows 2 columns. 
	string userinput;
	string line;
	int row = 0;
	bool found = false;
	
	
	while(getline(responses, line)) //splits every line
	{
		int index = line.find("@"); // Separates statements between @
		responseArray[row][0] = line.substr(0,index); //Cycles through colum before @ and makes it the first colum of responseArray
		responseArray[row][1] = line.substr(index+1); //Cycles through column after @ and makes it the second colum of responseArray
		row++;
	}
	responses.close(); //Closes the file
	cout << "What question do you have about C++" << endl; //initial starting question
	
	do
	{
		cin >> userinput; // Turns input into variable userinput
		for( int i = 0; i<row; i++)
		{
			
			if (userinput == responseArray[i][0]) //Goes through each option in the first column and looks for a match
			{
				found = true;
				cout << responseArray[i][1] << endl; //When it finds the match, prints the corresponding definition
			}
		}
		if  (userinput != "quit" &&  found == false) //Gives error message if incorrect word. Found == false allows it to just print sorry statement. 
		{
			cout << "Sorry, I don't know. What else can we talk about?" << endl;
			
		}
		found = false; //found is changed back to false so the loops can go through correclty. 
	
	
	}while(userinput != "quit"); //Allows user to quit by typing quit
	return 0;
	
}
