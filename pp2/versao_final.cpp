#include <iostream>
#include <list>
#include <vector>

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




class Position{
    public:
        pair<int, int> pos;
        int level;
        Position(pair<int, int> p, int w):pos(p), level(w){}
};

class Graph{
    private:
        vector<pair<int, int>> visited;
    public:

        bool verifica_vetor(vector <pair<int, int>>, pair<int, int>);
        int bfs(pair<int, int>, pair<int, int>);
        void displayWeights();
};

bool Graph:: verifica_vetor(vector <pair<int, int>> v, pair<int, int> element){
    typename vector<pair<int, int>>::iterator it;
    for(it = v.begin(); it!=v.end(); it++){
        if(*it == element){
            return true;
        }else{
            return false;
        }
    }
}
int Graph::bfs(pair<int, int> king, pair<int, int>knight){
    Queue_class<Position> queue;
    queue.insert_element(Position(king, 0));
    visited.push_back(king);
    int toadd_level=0;
    bool founded = false;
    

    vector<pair<int, int>> moves = {{1, 2}, {1, -2}, {-1, -2},{-1, 2}, {2, -1}, {2, 1}, {-2, -1}, {-2, 1}};
    
    while(!(founded)){
        Position test = queue.remove_element();
        //queue.pop();
        for(int i=0; i<8; i++){
            
            pair<int, int> toadd((test.pos.first+moves[i].first), (test.pos.second+moves[i].second));
            if(toadd.first >=1 && toadd.first<=8 && toadd.second>=1 && toadd.second <=8 && !(verifica_vetor(visited, toadd))){

                visited.push_back(toadd);
                toadd_level = test.level+1;
                queue.insert_element(Position(toadd, toadd_level));
                if(toadd == knight){
                    return toadd_level;
                }
            }
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
    int t;
    Graph graph;

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

        vector<pair<int, int>> cavalos;
        cavalos.push_back(cav1);
        cavalos.push_back(cav2);
        cavalos.push_back(cav3);
        cavalos.push_back(cav4);
        vector<int> founded;
        for(int i=0; i<4; i++){
            int t = (graph.bfs(king, cavalos[i]))-1;
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