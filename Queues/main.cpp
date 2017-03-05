/**Ameya Bahirat
Spring 2015
Assignment 4
**/
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include "CommunicationNetwork.h"

using namespace std;


int main()
{
    string wordsInFile[32];
    ifstream file("messageIn.txt");
    int counter = 0;
    string word;
    char userinput;
    bool built = false;
    //char input[256];
    //char input2[256];
    CommunicationNetwork comm(10);
    while(file >> word)
    {
        wordsInFile[counter] = word;
        counter++;
    }
    counter = 0;

    do
    {
        userinput = comm.menu();
        switch(userinput){
            case '1':
                comm.buildNetwork();
                built = true;
                break;
            case '2':
                comm.printPath(); //prints path
                break;
            case '3':
                if(counter > 32)
                    cout << "No more words to queue." << endl;
                else{
                    comm.enqueue(wordsInFile[counter]);
                    counter++;
                }
                break;
            case '4':
                if(built)
                    comm.DequeueTransmit(comm.dequeue());
                else
                    cout << "Build a network before transmitting a message." << endl;

                break;
            case '5':
                break;
            case '6':
                break;
        }

    }
    while(userinput != '7'); //establishes input '7' as quit
    cout << "Goodbye!" << endl;

    return 0;



}

