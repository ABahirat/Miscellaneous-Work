/**
 * @author E.S.Boese
 * Modifier: Ameya Bahirat
 * @version Fall 2014
 * HW 10
 * Takes in User.cpp and Book.cpp and applies them to the function of the code. 
 */

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

#include "Book.cpp"	 // This is NOT how it should be done but for now we will do it this way
#include "User.cpp"	 // This is NOT how it should be done but for now we will do it this way

using namespace std;

class Library 
{
  public:
	Library(string book_list_file, string user_list_file); 
	void readInBookList(string filename);  
	void readUserFile(string filename); 
	void printUsers(); 
	void printAverageBookRatings(); 
	
  private: 
	vector<Book> bookList; 
	vector<User> userList;
};


Library::Library(string bookFilename, string userFilename)
{
	readInBookList(bookFilename);
	readUserFile(userFilename);
}

void Library::printUsers()
{
	for (int i=0; i<userList.size(); i++)
	{
		cout << userList.at(i).toString() << endl;
	}
}


void Library::readInBookList(string filename)
{
	ifstream infile;
	infile.open(filename.c_str());
	string line;
	int count = 0;
	
	if (infile.is_open())
	{
		cout << "Reading in book list from file: " << filename << endl;
		while ( getline (infile, line) )
		{
			int comma_pos = line.find(",");
					
			string author = line.substr(0, comma_pos);
			string title = line.substr(comma_pos+1); 			

			// TODO: create new Book object
			Book B(author, title);
			
			// TODO: add Book object to vector
			bookList.push_back(B);			
			count++;
		}
		cout << count << " books read in. Closing book list file." << endl;
		infile.close();
	}
}

void Library::readUserFile(string filename)
{
	ifstream infile;
	infile.open(filename.c_str());
	
	if (infile.is_open())
	{
		cout << "Reading in user list from file: " << filename << endl;
		int count = 0;
		while (infile)
		{
			string author, ratings;
			getline(infile, author);
			
			if (author != "")
			{
				getline(infile, ratings);
				
				// TODO: Create new User object
				User U(author, ratings);
				// TODO: Add new User object to vector
				userList.push_back(U);
				count++;
			}
		}
		cout << count << " users read in. Closing user file." << endl;
		infile.close();
	}
}

void Library::printAverageBookRatings()
{
	cout << fixed << setprecision(2);
	cout << showpoint;
	int sum = 0;
	int count = 0;
	int bookRating = 0;
	for (int i = 0; i<bookList.size(); i++)
	{
		sum = 0;
		count = 0;
		for (int k = 0; k < userList.size(); k++)
		{
			bookRating = userList[k].getRatingAt(i);
			if (bookRating)
			{
				count++;
				sum += bookRating;
			}
		}
		double average = static_cast<double>(sum)/count;
		if (!count)
		{
			average = 0;
		}
		cout << average << " " << bookList[i].toString() << endl;
	}
}
	// TODO:
	// Loop through the book list vector
	//	 Loop through user list
	//		get the rating from each user for this book
	//		if the rating isn't zero, add it to the sum and increment a count of ratings
	//	 Print the average for this book





