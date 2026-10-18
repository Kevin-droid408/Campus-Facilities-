#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"
#include <iostream>
using namespace std;

/*Queue represented using a circular array*/
template <class T>
class Queue{
    private:
        Node<T>* rear;
        int count;
    public:
        Queue();                            //default constructor
        ~Queue();                           //destructor constructor

        void enqueue(T);
        void dequeue();
        bool peek();
        bool peeklast();
        bool isEmpty() const;
        bool isFull();
        void display();

};

//implementations

template <class T>
Queue<T>::Queue(){
    rear = nullptr;
    count = 0;
}

template <class T>
Queue<T>::~Queue(){
    while(!isEmpty()){
        dequeue();
    }
}

template <class T>
void Queue<T>::enqueue(T item){
    Node<T>* newNode = new Node<T>(item);
    if(isEmpty()){
        cout << "Queue is Empty!"<< endl;
        rear = newNode;
        rear->next = rear;
    }
    else{
        newNode->next = rear->next;
        rear->next = newNode;
        rear = newNode;
    }
    count++;
}

template <class T>
void Queue<T>::dequeue(){
    if(isEmpty()){
        cout << "Queue is Empty!" << endl;
        return;
    }
    Node<T>* front = rear->next;
    T item = front->data;

    if (front == rear){
        //when only one node is left
        delete front;
        rear = nullptr;
    }
    else{
        rear->next = front->next;
        delete front;
    }
    count--;
    cout << item << endl;                   // the item that has been removed
}

template <class T>
bool Queue<T>::peek(){
    if(isEmpty()){
        cout << "Queue is Empty!" << endl;
        return false;
    }
    return rear->next->data;
    return true;
}

template <class T>
bool Queue<T>::peeklast(){
    if(isEmpty()){
        cout << "Queue is Empty!" << endl;
        return false;
    }
    return rear->data;
    return true;
}

template <class T>
bool Queue<T>::isEmpty() const{
    return rear == nullptr;
}

template <class T>
bool Queue<T>::isFull(){
    return false;
}

template <class T>
void Queue<T>::display(){
    if(isEmpty()){
        cout << "Queue is Empty!" << endl;
        return;
    }

    Node<T>* current = rear->next;                      //we start at the front of the queue
    cout << "Queue (Front to Rear): ";

    int elementsPrinted = 0;
    while(elementsPrinted < count){
        cout << current->data << " ";
        current = current->next;
        elementsPrinted++;
    }
}

#endif
