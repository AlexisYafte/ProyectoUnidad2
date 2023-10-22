#include "Objct.cpp"
#include <stdio.h>
#include <pthread.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>


using namespace std;



int kbhit(void){
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}

void * roundRobin(void *ob){
    Objct *obj = (Objct *)ob;
    Queue *queue = (Queue *)obj->queue;
    QueueTime *timeQ= (QueueTime *)obj->timeQ;
    Node * proceso = queue->inicio;
    int duration, tam, quantum=50;
    while(true){
        tam = queue->tam;
        for(int i=0; i<tam; i++){
            duration = proceso->counter;
            if(duration<quantum){
                proceso->counter = 0;
                NodeTime * aux = timeQ->searchNode(proceso->priority, proceso->data);
                aux->reduction+=1;
                quantum = quantum-duration;
            }else if(duration>quantum && quantum!=0){
                proceso->counter = duration-quantum;
                Node * node = queue->borrarPosicion(i);
                queue->insertNode(node);
                NodeTime * aux = timeQ->searchNode(proceso->priority, proceso->data);
                aux->reduction+=1;
                quantum = 0;
                pthread_exit(NULL);
                return NULL;
            }else if(duration == quantum && quantum!=0){
                NodeTime * aux = timeQ->searchNode(proceso->priority, proceso->data);
                aux->reduction+=1;
                proceso->counter = 0;
                quantum = 0;
                pthread_exit(NULL);
                return NULL;
            }
            proceso = proceso->link;
        }
        proceso=queue->inicio;
    }
}

void * decrementarContador(void *ob){
    Objct *obj = (Objct *)ob;
    Queue *queue = (Queue *)obj->queue;
    QueueTime *timeQ= (QueueTime *)obj->timeQ;
    Node * aux = queue->inicio;
    while(aux->link != NULL){
        aux->counter-=(1+rand()%(5-1+1));
        NodeTime *auxT = timeQ->searchNode(aux->priority, aux->data);
        auxT->reduction+=1;
        aux = aux->link;
    }
    NodeTime *auxT = timeQ->searchNode(aux->priority, aux->data);
    auxT->reduction+=1;
    aux->counter-=(1+rand()%(5-1+1));
    sleep(1);
    pthread_exit(NULL);
    return NULL;
}



void *fairScheduling(void * ob){
    Objct *obj = (Objct *)ob;
    Queue *queue = (Queue *)obj->queue;
    QueueTime *timeQ= (QueueTime *)obj->timeQ;
    int operations =100;
    int time =operations/queue->tam;
    cout<<"\neL TIEMPO"<<time;
    if (time == 0)
        time=1;
    Node *aux = queue->inicio;
    for(int i=0; i<queue->tam; i++){
        aux->counter = aux->counter-time;
        NodeTime *auxT = timeQ->searchNode(aux->priority, aux->data);
        auxT->reduction+=1;
        if(aux->counter < 0 )
            aux->counter = 0; 
        aux = aux->link;
    }
    queue->zeroToFront();
    return NULL;
}

void * priority(void *ob){
    Objct *obj = (Objct *)ob;
    Queue *queue = (Queue *)obj->queue;
    QueueTime *timeQ= (QueueTime *)obj->timeQ;
    queue->orderBuble();
    int temp =queue->inicio->counter;
    queue->inicio->counter = 0;
    NodeTime *auxT = timeQ->searchNode(queue->inicio->priority,queue->inicio->data);
    auxT->reduction+=1;
    obj->time += temp;
    return NULL;
}


void * popQueue(void *ob){
    Objct *obj = (Objct *)ob;
    Queue *queue = (Queue *)obj->queue;
    QueueTime *timeQ= (QueueTime *)obj->timeQ;
    Node *aux =queue->inicio;
    int elemento;
    while(aux->counter == 0){
        NodeTime *auxT = timeQ->searchNode(aux->priority, aux->data);
        auxT->out+=obj->time;
        elemento = queue->pop();
        cout<<"\nSe elimino el proceso: "<<elemento;
        aux =aux->link;
    }
    sleep(1);
    pthread_exit(NULL);
    return NULL;
}

void * addProces(void *ob){
    Objct *obj = (Objct *)ob;
    Queue *queue = (Queue *)obj->queue;
    QueueTime *timeQ= (QueueTime *)obj->timeQ;
    int p =((1)+rand()%(3-1+1));
    int d =(1+rand()%(50-1+1));
    int c = ((20)+rand()%(100-20+1));
    queue->push(p,d,c);
    timeQ->push(p,d,obj->time,c);
    queue->printQueue();
    sleep(1);
    return NULL;
}
void addFirstProces(Queue *queue, QueueTime *timeQ, int a){
    int p =((1)+rand()%(3-1+1));
    int d =(1+rand()%(50-1+1));
    int c = ((20)+rand()%(100-20+1));
    queue->push(p,d,c);
    timeQ->push(p,d,a,c);
    return;
}

int main(){
    Queue *queue = new Queue();
    QueueTime *timeQ = new QueueTime();
    Objct * ob = new Objct(queue, timeQ);
    int random = ( 10+ rand() % (14 -10+ 1));
    int op, elemento, g, d, dE,r;
    pthread_t generate, deleteE, decremento, randDec;

    for(int i=0; i<random; i++){
        addFirstProces(queue,timeQ,ob->time);
    }
    queue->orderBuble();
    cout<<"COLA DE PRIORIDADES\n\n"<<"\t1) Round Robin\n"<<"\t2) Prioridad\n"<<"\t3) Fair Scheduling\n\tOpcion: ";
    cin<<op;
    
    while (!kbhit())
    {
        if(op==1){
            d = pthread_create(&decremento,NULL, roundRobin, ob);
            ob->time+=50;
        }else if(op==2){
            d = pthread_create(&decremento,NULL, priority, ob);
            break;
        }else if(op==3){
            d = pthread_create(&decremento,NULL, fairScheduling, ob);
            ob->time+=50;
        }
        r = pthread_create(&randDec,NULL, decrementarContador, ob);

        dE = pthread_create(&generate,NULL, popQueue, ob);

        g = pthread_create(&generate,NULL, addProces, ob);
    }
    timeQ->printQueueTime();

    return 0;
};