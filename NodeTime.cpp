#include <iostream>

class NodeTime{
    public:
        NodeTime * link;
        int id;
        int id2;
        int reduction;
        int arrival;
        int out;
        int counter;

        friend class Queue;
    
        NodeTime(int i, int j, int a, int c){
            id = i;
            link = 0;
            id2 = j;
            arrival = a;
            reduction =0;
            counter =c;
            out=0;
        }
};