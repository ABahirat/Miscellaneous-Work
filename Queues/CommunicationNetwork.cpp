#include <iostream>
#include "CommunicationNetwork.h"

CommunicationNetwork::CommunicationNetwork(int qs) {
        queueSize = qs;
        arrayQueue = new std::string[queueSize];
        queueHead = 0;
        queueTail = 0;
        queueCount = 0;
}
CommunicationNetwork::~CommunicationNetwork() {
}


char CommunicationNetwork::menu()
{
    char userinput;

    std::cout << "======Main Menu=====" << std::endl;
    std::cout << "1. Build Network" << std::endl;
    std::cout << "2. Print Network Path" << std::endl;
    std::cout << "3. Enqueue" << std::endl;
    std::cout << "4. Dequeue" << std::endl;
    std::cout << "5. Print Queue" << std::endl;
    std::cout << "6. Send Entire Message" << std::endl;
    std::cout << "7. Quit" << std::endl;

    std::cin >> userinput;
    return userinput;
}
void CommunicationNetwork::enqueue(std::string word)
{
    if(!queueIsFull())
    {
        arrayQueue[queueTail] = word;
        queueCount++;

        if(queueTail == queueSize-1)
        {
            queueTail = 0;
        }
        else{
            queueTail++;
        }
        std::cout<<"E: "<<word<<std::endl;
        std::cout<<"H: "<<queueHead<<std::endl;
        std::cout<<"T: "<<queueTail<<std::endl;
    }
    else
        std::cout << "Queue is full" << std::endl;

}
std::string CommunicationNetwork::dequeue()
{
    std::string word;
    if(!queueIsFull() && queueHead == queueTail)
        std::cout << "Queue is empty." << std::endl;
    else{
        word = arrayQueue[queueHead];
        arrayQueue[queueHead] = "";
        if(queueHead != queueSize-1)
            queueHead++;
        else
            queueHead = 0;
        queueCount--;
        std::cout<<"H: "<<queueHead<<std::endl;
        std::cout<<"T: "<<queueTail<<std::endl;
    }

    return word;
}
void CommunicationNetwork::printQueue()
{
    int counter = queueHead;
    bool check = false;
    if(queueIsFull())
        check = true;
    while((check && counter == queueTail) || counter != queueTail)
    {

        std::cout << counter << ": " << arrayQueue[counter] << std::endl;
        if(counter != queueSize-1)
        {
            counter++;
        }
        else
            counter = 0;
        check = false;
    }
}
void CommunicationNetwork::buildNetwork()
{
    city *x = new city;
    head = x;
    x->previous = NULL;
    std::string cities[10] = {"Los Angeles", "Phoenix" , "Denver" , "Dallas" , "St. Louis" , "Chicago", "Atlanta" , "Washington, D.C." , "New York" , "Boston"};

    for(int i = 0; i < 10; i++)
    {
        city *next = new city;
        x->name = cities[i];
        x->next = next;
        next->previous = x;
        next->next = NULL;
        x = x->next;
    }
    printPath();
    tail = x;

}
void CommunicationNetwork::printPath()
{
    std::cout << "===CURRENT PATH===" << std::endl;
    city *x = new city;
    x = head;
    while(x->next != NULL)
    {
        std::cout << x->name << " -> ";
        x = x->next;
    }
    std::cout << "NULL" << std::endl;
    std::cout << "==================" << std::endl;
}
bool CommunicationNetwork::queueIsFull() //send when full
{
    if(queueCount == queueSize)
        return true;
    return false;
}
void CommunicationNetwork::transmitMsg(std::string word)
{
    if (word != ""){
        city *x = new city;
        x = head;
        x->message = word;

        while(x->next != NULL)
        {
            std::cout << x->name << " received " << x->message << std::endl;
            if(x->next != NULL)
            {
                x->next->message = x->message;
            }
            x->message = "";
            x = x->next;
        }
        while(x->previous != NULL)
        {
            x = x->previous;
            if(x->previous !=NULL)
            {
                x->message = x->next->message;
            }
            x->next->message = "";
            if(x->previous != NULL)
                std::cout << x->previous->name << " received " << x->message << std::endl;
        }
    }
}
void CommunicationNetwork::transmitFinal(std::string word, bool endOfArray)
{
    if(endOfArray)
    {
        enqueue(word);
    }
    if(queueIsFull() || endOfArray)
    {
        transmitMsg(dequeue());
        while(queueTail != queueHead)
        {
            transmitMsg(dequeue());
        }
    }
    if(!endOfArray)
    enqueue(word);
}
