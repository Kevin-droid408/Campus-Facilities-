#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <iostream>
#include <vector>
using namespace std;

/*Priority Queue implemented using a binary max-heap*/
template <class T>
class PriorityQueue{
    private:
        vector<T> array;
        int size;
        int capacity;

    public:
        PriorityQueue(int);                              
        void heapify(int);                              
        void buildHeap(const vector<T>&);               
        void insert(T);                                 
        T top();                                        
        T pop();                                        
        void deleteKey(T);                              
        void display() const;                           

};

/*----------implementations----------*/

/*Constructor to initialize the heap with a given capacity*/
template <class T>
PriorityQueue<T>::PriorityQueue(int capacity){
   
    this->size = 0;
    this->capacity = capacity;
    this->array.resize(capacity);
}

/*function to heapify the node at a given index*/
template <class T>
void PriorityQueue<T>::heapify(int i){
  
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if( left < size && array[left] > array[largest])
        largest = left;
    
    if (right < size && array[right] > array[largest])
        largest = right;

    if(largest != i){
        swap(array[i], array[largest]);
        heapify(largest);
    }
}

/*function to build max heap from a given array*/
template <class T>
void PriorityQueue<T>::buildHeap(const vector<T>& arr){

    if(arr.size() > capacity){
        capacity = arr.size();
    }

    array = arr;
    array.resize(capacity);
    size = arr.size();

    for(int i = size / 2 - 1; i >= 0; i--){
        heapify(i);
    }
}

/*function to insert an item into the heap*/
template <class T>
void PriorityQueue<T>::insert(T item){
    
    if(size == capacity){
        //resize the heap
        capacity *= 2;
        array.resize(capacity);
    }

    size++;
    int i = size - 1;
    array[i] = item;
   
    // Fix the max heap property if it is violated
    while (i != 0 && array[(i - 1) / 2] < array[i]) {
        swap(array[i], array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

/*function to get the item of the root node of the max heap*/
template <class T>
T PriorityQueue<T>::top(){
   
    if(size <= 0)            // indicates that the heap is empty
        return T{};
    
    return array[0];
}

/*function to remove and return the maximum item from the heap*/
template <class T>
T PriorityQueue<T>::pop(){
    
    if(size <= 0)
        return T{};
    if(size == 1){
        size--;
        return array[0];
    }
    //store the maximum item and remove it//
    T root = array[0];
    array[0] = array[size - 1];
    size--;
    // Heapify the root node after deletion
    heapify(0);
    return root;
}

/*function to delete a specific key from the heap*/
template <class T>
void PriorityQueue<T>::deleteKey(T key){
    
    //find the index of the key
    int index = -1;
    for(int i = 0; i < size; ++i){
        if(array[i] == key){
            index = i;
            break;
        }
    }

    //if the key is not found, return
    if(index == -1){
        cout << "Key not found!" << endl;
        return; 
    }

    //if the key is found, delete it
    //if it's the last element, simply reduce the size
    if(index == size - 1){
        size--;
        return;
    }

    array[index] = array[size - 1];
    size--;

    if(index > 0 && array[index] > array[(index - 1) / 2]){
       
        // Move the element up if it is larger than its parent
        while(index > 0 && array[index] > array[(index - 1) / 2]){
            swap(array[index], array[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }
    else{
        // Move the element down if necessary
        heapify(index);
    }
}

/*function to display the heap*/
template <class T>
void PriorityQueue<T>::display()const{
    cout << "Max Heap: ";
    for(int i = 0; i < size; i++){
        cout << array[i] << ",";
    }
    cout << endl;
}

#endif