#include<iostream>

#include<cstdlib>

using namespace std;

struct node{
    int info;
    struct node *next;
};

class Queue{
    private:
        node *rear;
        node *front;
    public:
        Queue();
        ~Queue(){
        	delete rear;
        	delete front;
		}
        void enqueue();
        void dequeue();
        void display();
};

Queue::Queue(){
    rear = NULL;
    front = NULL;
}

void Queue::enqueue(){
    int data;
    node *temp = new node;
    cout<<"Enter the data to enqueue: ";
    cin>>data;
    temp->info = data;
    temp->next = NULL;
    if(front == NULL){
        front = temp;
    }else{
        rear->next = temp;
    }
    rear = temp;
}

void Queue::dequeue(){
    node* temp = new node;
    if(front == NULL){
        cout<<"\nQueue is Emtpty\n";
    }else{
        temp = front;
        front = front->next;
        cout<<"The data Dequeued is "<<temp->info;
        // moet hier expliciet verwijderd worden omdat het een raw pointer is, dus ptr ergens opslaan (in temp)
        delete temp;
    }
}

void Queue::display(){
    node *loper = new node;
    loper = front;
    if(front == NULL){
        cout<<"\nNothing to Display\n";
    }else{
        while(loper!=NULL){
            cout<<loper->info<<"\t";
            loper = loper->next;
        }
    }
}

int main(){
    Queue queue;
    int choice;
    while(true){
        cout<<"1.Enqueue\n2. Dequeue\n3. Display\n 4.Quit";
        cout<<"\nEnter your choice: ";
        cin>>choice;
        switch(choice){
            case 1:
                queue.enqueue();
                break;
            case 2:
                queue.dequeue();
                break;
            case 3:
                queue.display();
                break;
            case 4:
                exit(0);
                break;
            default:
                cout<<"\nInvalid Input. Try again! \n";
                break;
        }
    }
    return 0;
}
