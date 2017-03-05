/**
 * Ameya Bahirat
 * Fall 2014
 * HW10
 * Creates Book class and creates functions for it. 
 */

#include <iostream>
using namespace std;

class Book
{
	private:
		string author;
		string title;
		
	public:
		Book();
		Book(string author, string title);
		string getAuthor();
		string getTitle();
		void setAuthor(string au);
		void setTitle(string ti);
		string toString();
};
Book::Book()
{
	author = "Unknown";
	title = "Unknown";
}
Book::Book(string author, string title)
{
	setAuthor(author);
	setTitle(title);
}

string Book::getAuthor()
{
	return author;
}
string Book::getTitle()
{
	return title;
}
void Book::setAuthor(string au)
{
	author = au;
}
void Book::setTitle(string ti)
{
	title = ti;
}
string Book::toString()
{
	
	string Book_by_Author = getTitle() + " by " +  getAuthor(); 
	return Book_by_Author;
}

