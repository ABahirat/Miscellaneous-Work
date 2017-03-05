/**Ameya Bahirat
 * Fall 2014
 * HW 10
 * Creates functions for class User
 */

#include <iostream>
#include <vector>
using namespace std;

class User
{
    private:
        string id;
        vector<int> ratings;
    public:
        User();
        User(string userid, string userratings);
        string getId();
        int getRatingAt(int index);
        void addRating (int rating);
        int getNumRatings();
        string toString();
        void printRatings();
        
};

User::User()
{
    id = "Unknown";
    ratings.push_back(0);
}
User::User(string userid, string userratings)
{
    id = userid;
    bool negative = false;
    for (int i = 0; i < userratings.length(); i++)
    {
		switch(userratings[i])
		{
			case '-':
				negative = true;
				break;
			case ' ':
				break;
			case '0':
				addRating(0);
				break;
			case '1':
				if (negative)
				addRating(-1);
				else 
				addRating(1);
				negative = false;
				break;
			case '3':
				if (negative)
				addRating(-3);
				else 
				addRating(3);
				negative = false;
				break;
			case '5':
				if (negative)
				addRating(-5);
				else
				addRating(5);
				negative = false;
				break;
			}
	 }	
}
string User::getId()
{
    return id;
}
int User::getRatingAt(int index)
{
    return ratings[index];
}
void User::addRating(int rating)
{
    ratings.push_back(rating);
}
int User::getNumRatings()
{
	int num_ratings;
    num_ratings = ratings.size();
    return num_ratings;
}
string User::toString()
{
	
    string user_id = "User [user_id=" + id + "]";
    return user_id;
}
void User::printRatings()
{
	for (int i = 0; i < ratings.size(); i++)
	{
		if ( i != ratings.size() - 1)
		cout << ratings[i] << " ";
		else 
		cout << ratings[i];
	}
}
