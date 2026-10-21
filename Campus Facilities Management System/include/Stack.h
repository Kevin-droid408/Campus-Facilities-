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
        T pop();
        T top();                                // reads the element at the top of the stack without deleting it 
        bool isEmpty() const;
        void display();

        int size();
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
T Stack<T>::pop(){
    if(topNode == nullptr){
        cout << "Stack Underflow" << endl;
        return T{};
    }

    Node<T>* temp = topNode;
    T item = temp->data;

    topNode = topNode->next;

    count--;
    
    delete temp;
    return item;
}

template <class T>
T Stack<T>::top(){
    if(topNode ==  nullptr){
        return T{};
    }
    
    return topNode->data;
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

template <class T>
int Stack<T>::size(){
    return count;
}

#endif