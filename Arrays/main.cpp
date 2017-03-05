#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct wordOccurence
{
    string word;
    int occurence;
};

int main(int argc, char* argv[])
{
    ifstream infile(argv[1]);
    int displayCounter = atoi(argv[2]);
    wordOccurence wordOccArray[100];
    char * temp;
    char lineArray[1024];

    string avoidWords[] = {"the", "be", "to", "of", "and", "a" , "in" , "that" , "have" , "i" , "it" , "for", "not", "on" , "width" , "he", "as", "you", "do", "at" , "this", "but" , "his" , "by" , "from" , "they" , "we" , "say", "her" , "she", "or" , "an" , "will" , "my" , "one", "all" , "would" , "there" , "their" , "what" , "so" , "up" , "out" , "if" , "about" , "who" , "get" , "which" , "go" , "me"};

    while(infile.getline(lineArray, 1024))
    {

        temp = strtok(lineArray," ");


        while(lineArray != NULL)
        {
            printf ("%s\n",temp);
            temp = strtok(NULL," ");
        }


     }

}


