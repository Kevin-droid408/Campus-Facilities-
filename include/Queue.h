#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"
#include <iostream>
using namespace std;

/*Queue represented using a circular linked list*/
template <class T>
class Queue{
    private:
        Node<T>* rear;
        int count;
    public:
        Queue();                            //default constructor
        ~Queue();                           //destructor constructor

        void enqueue(T);
        bool dequeue();
        T peek() const;
        T peeklast() const;
        bool isEmpty() const;
        bool isFull() const;
        void display() const;

};

/*----------implementations----------*/

/*constructor to initialize the Queue*/
template <class T>
Queue<T>::Queue(){
    rear = nullptr;
    count = 0;
}

/*destructor to deallocate memory*/
template <class T>
Queue<T>::~Queue() {
    while (!isEmpty()) {
        Node<T>* front = rear->next;

        if (front == rear) {
            rear = nullptr;
        } else {
            rear->next = front->next;
        }

        delete front;
        count--;
    }
}

/*function that adds an element at the rear*/
template <class T>
void Queue<T>::enqueue(T item){
    Node<T>* newNode = new Node<T>(item);
    if(isEmpty()){
        
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

/*function that removes the front element*/
template <class T>
bool Queue<T>::dequeue(){
    if(isEmpty()){
        cout << "Queue is Empty!" << endl;
        return false;
    }
    Node<T>* front = rear->next;

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
    return true;                                    // the item that has been removed
}

/*function that returns the first element in the queue*/
template <class T>
T Queue<T>::peek() const{
    if(isEmpty()){
        cout << "Queue is Empty!" << endl;
        return T{};
    }
    return rear->next->data;                //traverses to the front and returns the data in that node
}

/*function that returns the last element*/
template <class T>
T Queue<T>::peeklast() const{
    if(isEmpty()){
        cout << "Queue is Empty!" << endl;
        return T{};
    }
    return rear->data;
}

/*function that determines whether the queue is empty or not*/
template <class T>
bool Queue<T>::isEmpty() const{
    return rear == nullptr;
}

/*function that tests if the queue is full*/
template <class T>
bool Queue<T>::isFull() const{
    return false;
}

/*displays element of the queue*/
template <class T>
void Queue<T>::display() const{
    if(isEmpty()){
        cout << "Queue is Empty!" << endl;
        return;
    }

    Node<T>* current = rear->next;                      //we start at the front of the queue
    cout << "Queue (Front to Rear): ";

    int elementsPrinted = 0;                            // tracks the number of printed elements
    while(elementsPrinted < count){
        cout << current->data << " ";
        current = current->next;
        elementsPrinted++;
    }
    cout << endl;                                   //ends output with a new line
}

#endif
