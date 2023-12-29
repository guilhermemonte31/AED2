#include <iostream>
#include <list>
#include <vector>

using namespace std;



template <typename T>
class Queue_class{
    public:
        list <T> lst;
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




class Position{
    public:
        pair<int, int> pos;
        int level;
        Position(pair<int, int> p, int w):pos(p), level(w){}
};

class Graph{
    private:
        vector<pair<int, int>> visited;
        Queue_class<Position> queue;
        list<Position> chess;
    public:
        Graph(pair<int, int>);
        bool verifica_vetor(vector <pair<int, int>>, pair<int, int>);
        int search(pair<int, int>);
};

bool Graph:: verifica_vetor(vector <pair<int, int>> v, pair<int, int> element){
    typename vector<pair<int, int>>::iterator it;
    for(it = v.begin(); it!=v.end(); it++){
        if(*it == element){
            return true;
        }
    }
    return false;
}
Graph::Graph(pair<int, int> king){
    queue.insert_element(Position(king, 0));
    chess.push_back(Position(king, 0));
    visited.push_back(king);
    vector<pair<int, int>> moves = {{1, 2}, {1, -2}, {-1, -2},{-1, 2}, {2, -1}, {2, 1}, {-2, -1}, {-2, 1}};
    int i=0;
    while(!(queue.is_empty())){
        Position atual = queue.remove_element();
        for(int i=0; i<8; i++){
            pair<int, int> toadd((atual.pos.first+moves[i].first), (atual.pos.second+moves[i].second));
            if(toadd.first >=1 && toadd.first<=8 && toadd.second>=1 && toadd.second <=8 && !(verifica_vetor(visited, toadd))){
                visited.push_back(toadd);
                chess.push_back(Position(toadd, (atual.level+1)));
                queue.insert_element(Position(toadd, (atual.level+1)));
            }
        }
        
    }
}

int Graph::search(pair<int, int> knight){
    list<Position>::iterator it;
    for(it=chess.begin(); it!= chess.end(); it++){
        if((*it).pos == knight){
            return (*it).level;
        }
    }
}



void bubble_sort(vector<int> &v){
    for(int i=0; i<(v.size()-1); i++){
        for(int j=0; j<(v.size()-i-1); j++){
            if(v[j] > v[j+1]){
                int aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
            }
        }
    }

}
int main(){
    int n;
    cin>>n;
    vector<int> answer;
    for(int u=0; u<n; u++){
        string c1, c2, c3, c4, k;
        cin>>c1>>c2>>c3>>c4>>k;
        pair<int, int>cav1 (int(c1[0]-96), (int(c1[1])-48));
        pair<int, int>cav2 (int(c2[0]-96), (int(c2[1])-48));
        pair<int, int>cav3 (int(c3[0]-96), (int(c3[1])-48));
        pair<int, int>cav4 (int(c4[0]-96), (int(c4[1])-48));
        pair<int, int>king (int(k[0]-96), (int(k[1])-48));
        Graph graph{king};

        vector<pair<int, int>> cavalos;
        cavalos.push_back(cav1);
        cavalos.push_back(cav2);
        cavalos.push_back(cav3);
        cavalos.push_back(cav4);
        vector<int> founded;
        for(int i=0; i<4; i++){
            int t = (graph.search(cavalos[i]))-1;
            founded.push_back(t);
        }    
        bubble_sort(founded);  
        int minimum = founded[0];
        answer.push_back(founded[0]);
        for(int i=1; i<4; i++){
            if(founded[i] == minimum){
                answer.push_back(founded[i]);
            }
        }
    }
    for(int i=0; i<answer.size(); i++){
        cout<<answer[i];
    }
}
