#ifndef STACK_H
#define STACK_H

#include "Node.h"
#include <iostream>
using namespace std;

template <class T>
class Stack{
    private:
        Node<T>* topNode;
        int count;
    public:
        Stack();
        ~Stack();                               // destructor

        void push(T);
        bool pop();
        T top();                                // reads the element at the top of the stack without deleting it 
        bool isEmpty() const;
        void display();
};

// class implementations
template <class T>
Stack<T>::Stack(){
    topNode = nullptr;
    count = 0;
}

template <class T>
Stack<T>::~Stack(){
    while(!isEmpty()){                         // runs until all the elements of stack are deleted
        pop();                                
    }
}

template <class T>
void Stack<T>::push(T item){
    Node<T>* newNode = new Node<T>(item);

    newNode->next = topNode;
    topNode = newNode;

    count++;
}

template <class T>
bool Stack<T>::pop(){
    if(topNode == nullptr){
        return false;
    }

    Node<T>* temp = topNode;
    topNode = topNode->next;

    delete temp;
    count--;

    return true;
}

template <class T>
T Stack<T>::top(){
    if(topNode ==  nullptr){
        return T{};
    }
    Node<T>* current = topNode;
    while(current->next != nullptr){
        current = current->next;
    }
    return current->data;

}
template <class T>
bool Stack<T>::isEmpty() const{
    return topNode == nullptr;
}

template <class T>
void Stack<T>::display(){
    if(isEmpty()){
        cout << "Stack is Empty!" << endl;
        return;
    }
    Node<T>* current = topNode;
    while(current != nullptr){
        cout << current->data << endl;
        current = current->next;
    }
}

#endif