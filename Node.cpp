#include <iostream>

class Node{
    public:
        Node * link;
        int data;
        int counter;
        int priority;

        friend class Queue;
    
        Node(int p, int d, int c){
            data = d;
            link = 0;
            priority = p;
            counter = c;
        }
};