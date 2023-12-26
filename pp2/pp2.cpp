#include <iostream>
#include <stdlib.h>
#include <vector>
#include <list>
#include <iomanip>

using namespace std;


template <typename T>
class Queue_class{
    private:
        list <T> lst;
    public:
        void insert_element(T element);
        void remove_element(T element);
        void show();
};

template <typename T>
void Queue_class<T>:: insert_element(T element){
    typename list<T>:: iterator it = lst.begin();
    while(it != lst.end() && *it<element){
        it++;
    }
    lst.insert(it, element);
}

template <typename T>
void Queue_class<T>:: remove_element(T element){
    lst.remove(element);
}

template <typename T>
void Queue_class<T>:: show(){
    typename list<T>:: iterator it;
    for(it = lst.begin(); it!= lst.end(); it++){
        cout<< *it<< " ";
    }
}


class Graph{
    public:
        string pos;
        list <string> *adj;
    private:
        Graph(string);


}
Graph::  Graph(string pos){
    this->pos = pos;
    adj = new list<string>[4];
}

int main(){
    Queue_class <int> queue;
    queue.insert_element(11);
    queue.insert_element(3);
    queue.insert_element(7);
    queue.insert_element(15);
    queue.insert_element(5);
    queue.show();
    queue.remove_element(5);
    queue.show();
}
