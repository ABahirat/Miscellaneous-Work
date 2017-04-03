#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdlib.h>

using namespace std;

struct Item
{
    string type;
    bool forSale;
    int price;
};

const int max_chars = 512;
const char* const delim = ",";

Item* itemList[100];
int numItems = 0;
int operations = 0;

bool matchExists(Item* item);
void shift(int index);

int main(int argc, char* argv[])
{
    ifstream infile(argv[1]);
    char* buf;
    string line;
    
    while(getline(infile, line)) {
        operations++;
        char* cline = new char[line.length() + 1];
        strcpy(cline, line.c_str());
        
        Item* item = new Item();
        item->type = strtok(cline, delim);
        item->forSale = strcmp(strtok(0, delim), " for sale") == 0 ? true : false;
        item->price = atoi(strtok(0, delim));
        
        if (!matchExists(item))
            itemList[numItems++] = item;
    }
    
    infile.close();
    
    /****************
     * begin printing output
     ****************/
    
    //print items sold
    
    cout << "#" << endl;
    
    //print items remaining
    for (int i = 0; i < numItems; i++)
    {
        cout << itemList[i]->type << ", ";
        cout << (itemList[i]->forSale ? "for sale" : "wanted") << ", ";
        cout << itemList[i]->price << endl;
    }
    
    cout << "#" << endl;
    
    cout << "operations:" << operations << endl;
    
    return 0;
}

bool matchExists(Item* item)
{
    for (int i = 0; i < numItems; i++)
    {
        operations++;
        //if searching for the same item
        if (strcmp(item->type.c_str(), itemList[i]->type.c_str()) == 0)
        {
            //if it's a buy/sell pair
            if (item->forSale && !itemList[i]->forSale)
            {
                if (item->price <= itemList[i]->price)
                {
                    //print
                    cout << itemList[i]->type << " " << item->price << endl;
                    
                    shift(i);
                    return true;
                }
            }
            else if (!item->forSale && itemList[i]->forSale)
            {
                if (item->price >= itemList[i]->price)
                {
                    //print
                    cout << itemList[i]->type << " " << itemList[i]->price << endl;
                    
                    shift(i);
                    return true;
                }
            }
        }
    }
    
    return false;
}

//index to be removed
void shift(int index)
{
    for (int i = index + 1; i < numItems; i++)
    {
        operations++;
        itemList[i - 1] = itemList[i];
    }
    
    itemList[numItems] = NULL;
    operations++;
    
    numItems--;
}
