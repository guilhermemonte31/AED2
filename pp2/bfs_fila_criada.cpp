#include <iostream>
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
        T remove_element();
        void show();
        list<T> get_list(){return lst;}
        int list_size(){return lst.size();}
        bool is_empty();
};

template <typename T>
void Queue_class<T>:: insert_element(T element){
    lst.push_back(element);
}

template <typename T>
T Queue_class<T>:: remove_element(){
    T first = lst.front();
    lst.pop_front();
    return first;
}

template <typename T>
void Queue_class<T>:: show(){
    typename list<T>:: iterator it;
    for(it = lst.begin(); it!= lst.end(); it++){
        cout<< *it<< " ";
    }
}


template <typename T>
bool Queue_class<T>:: is_empty(){
    if (lst.empty()) return true;
    else return false;
}


template <typename T>
bool verifica_vetor(vector <T> v, T element){
    typename vector<T>::iterator it;
    for(it = v.begin(); it!=v.end(); it++){
        if(*it == element){
            return true;
        }else{
            return false;
        }
    }
}


int bfs(pair<char, int> knight, pair<char, int> king){
    int level =0;
    vector<pair<char, int>> visited;
    
    if(knight.first == king.first && knight.second == king.second) return 0;

    Queue_class<pair<char, int>> queue;
    list<pair<char, int>> lista = queue.get_list();
    

    queue.insert_element(knight);
    visited.push_back(knight);
    while(!(queue.is_empty())){
        int size = queue.list_size();
        level ++;
        while(size !=0){

            pair<char, int> current = queue.remove_element();

            vector<pair<int, int>> moves = {{1, 2}, {1, -2}, {-1, -2},{-1, 2}, {2, -1}, {2, 1}, {-2, -1}, {-2, 1}};
            for(int i=0; i<8; i++){
                pair<char, int> test(char(current.first+moves[i].first), (current.second + moves[i].second));
                if(test == king) return level;
                if(test.first >='a' && test.first<='h' && test.second>=1 && test.second <=8 && !(verifica_vetor(visited, test))){
                    visited.push_back(test);
                    queue.insert_element(test);
                }
            }
            size--;
        }

    }
    return level;

    
}


int main(){

    pair<char, int> knight('c',7);
    pair<char, int> king('e', 4);
    int i = bfs(knight, king);
    cout<<"passos: "<<i;



}
