#ifndef COMMUNICATIONNETWORK_H
#define COMMUNICATIONNETWORK_H
#include<string>
struct city{

    std::string name;
    std::string message; //intended to hold one word
    city *next;
    city *previous;

};

class CommunicationNetwork
{
    public:
        CommunicationNetwork(int);
        virtual ~CommunicationNetwork();
        //circular queue methods
        void enqueue(std::string);
        std::string dequeue(); //should send through network, call transmit msg
        void printQueue();
        void buildNetwork();
        void printPath();
        bool queueIsFull(); //send when full
        void transmitMsg(std::string);
        void transmitFinal(std::string, bool);
        char menu();

    protected:
    private:
        city *head;
        city *tail;
        int queueSize;
        int queueHead;
        int queueTail;
        std::string *arrayQueue;
        int queueCount;
};

#endif // COMMUNICATIONNETWORK_H
