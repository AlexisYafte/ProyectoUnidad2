#include "Node.cpp"
#include <iostream>
using std::cout;
using std::endl;
using std::end;

class Queue{
    public:
        Node * inicio;
        int tam;
    
        Queue(){
            inicio = 0;
            tam=0;
        }

        void push(int p, int d, int c){
            Node * newNode = new Node(p, d, c);
            if(inicio == 0){
                inicio = newNode;
            }else{
                Node  * aux = inicio;
                while(aux->link != NULL){
                    aux = aux->link;             
                }
                aux->link=newNode;
            } 
            this->tam++;
        }

        int pop(){
            int data;
            Node * old = inicio;
            data = old->data;
            if(old->link == NULL){
                inicio = NULL;
            }else{
                inicio = old->link;
            }
            this->tam--;
            return data;
        }

        void orderBuble(){
            Node *aux = this->inicio;
            Node *ant = this->inicio;
            int hola = 2;
            int p, d,c;
            for(int i=0; i<tam; i++){
                for(int j=0; j<tam; j++){
                    if(aux->priority < ant->priority){
                        p=aux->priority;
                        d=aux->data;
                        c =aux->counter;
                        aux->priority = ant->priority;
                        aux->data = ant->data;
                        aux->counter = ant->counter;
                        ant->priority = p;
                        ant->data = d;
                        ant->counter = c;
                    }
                    ant = ant->link;
                }
                ant = inicio;
                aux = aux->link;
            }
        }

        void printQueue(){
            Node * aux = inicio;
            cout<<"\n\nCola\nPrioridad: ";
            for(int i=0; i<tam; i++){
                cout<<"|   "<<aux->priority<<" | ";
                aux = aux->link;
            }
            aux = inicio;
            cout<<"\nDato:      ";
            for(int i=0; i<tam; i++){
                if(aux->data <10)
                    cout<<"|   "<<aux->data<<" | ";
                else
                    cout<<"|  "<<aux->data<<" | ";
                aux = aux->link;
            }
            aux = inicio;
            cout<<"\nConrador:  ";
            for(int i=0; i<tam; i++){
                if(aux->counter <10)
                    cout<<"|   "<<aux->counter<<" | ";
                else if(aux->counter<100)
                    cout<<"|  "<<aux->counter<<" | ";
                else    
                    cout<<"| "<<aux->counter<<" | ";
                aux = aux->link;
            }
           
        }






        Node * borrarPosicion(int pos){
            Node * aux  = this->inicio;
            Node * ant = aux;      
            int i=0;
            if(pos == 0 && this->inicio->link == NULL)
                this->inicio = NULL;
            while(i!= pos && aux->link != NULL){
                ant = aux;
                aux = aux->link;
                i+=1;
            }
            if(pos == 0 )
                this->inicio = aux->link;      
            else if(i==pos)           
                ant->link = aux->link; 
            tam-=1;
            return aux;
        }
        
        void insertNode(Node * newNode){
            if(inicio == 0){
                inicio = newNode;
            }else{
                Node  * aux = inicio;
                while(aux->link != NULL){
                    aux = aux->link;             
                }
                aux->link=newNode;
            } 
            newNode->link = NULL;
            this->tam++;
        }

        Node *  popNode(){
            Node * old = inicio;
            if(old->link == NULL){
                inicio = NULL;
            }else{
                inicio = old->link;
            }
            this->tam--;
            return old;
        }

        

        int totalTime(){
            int time=0;
            Node * aux = inicio;
            while(aux->link != NULL){
                time = time + aux->counter;
                aux = aux->link;
            }
            time = time + aux->counter;
            return time;
        }
       
        void zeroToFront(){
            Node *aux = this->inicio;
            Node *ant = this->inicio;
            int hola = 2;
            int p, d,c;
            for(int i=0; i<tam; i++){
                for(int j=0; j<tam; j++){
                    if(aux->counter < ant->counter){
                        p=aux->priority;
                        d=aux->data;
                        c =aux->counter;
                        aux->priority = ant->priority;
                        aux->data = ant->data;
                        aux->counter = ant->counter;
                        ant->priority = p;
                        ant->data = d;
                        ant->counter = c;
                    }
                    ant = ant->link;
                }
                ant = inicio;
                aux = aux->link;
            }
        }
       
        int firstPriority(){
            return this->inicio->priority;
        }
};