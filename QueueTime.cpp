#include "NodeTime.cpp"
#include <iostream>
using std::cout;
using std::endl;
using std::end;

class QueueTime{
    public:
        NodeTime * inicio;
        int tam;
    
        QueueTime(){
            inicio = 0;
            tam=0;
        }

        void push(int i, int j, int a, int c){
            NodeTime * newNode = new NodeTime(i, j, a, c);
            if(inicio == 0){
                inicio = newNode;
            }else{
                NodeTime  * aux = inicio;
                while(aux->link != NULL){
                    aux = aux->link;             
                }
                aux->link=newNode;
            } 
            this->tam++;
        }

        NodeTime * searchNode(int p, int j){
            NodeTime * aux =inicio;
            for(int i=0; i<tam; i++){
                if(aux->id == p && aux->id2==j)
                    return aux;
                aux = aux->link;
            }
            return aux;
        }

        void printQueueTime(){
            NodeTime * aux =inicio;
            cout<<"\n\nTiempos\n\n";
            for(int i=0; i<tam; i++){
                cout<<aux->id<<"  "<<aux->id2<<"  "<<aux->arrival<<"  "<<aux->out<<"  "<<aux->reduction<<"  "<<aux->counter<<"\n";
                aux = aux->link;
            }
            return;
        }
};