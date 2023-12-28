#include <iostream>
#include <vector>
#include <list>
#include <queue>

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
// int mult_bfs(pair<char, int> king, vector<pair<char, int>> cavalos){
//     int level =0;
//     vector<pair<char, int>> visited;
//     int found = 0;
    
//     for(int i=0; i<4; i++){
//         if(cavalos[i] == king){
//             found ++;
//         }
//     }
//     if(found > 0) return found;
//     if(knight.first == king.first && knight.second == king.second) return 0;

//     Queue_class<pair<char, int>> queue;
//     list<pair<char, int>> lista = queue.get_list();
    

//     queue.insert_element(knight);
//     visited.push_back(knight);
//     while(!(queue.is_empty())){
//         int size = queue.list_size();
//         level ++;
//         while(size !=0){

//             pair<char, int> current = queue.remove_element();

//             vector<pair<int, int>> moves = {{1, 2}, {1, -2}, {-1, -2},{-1, 2}, {2, -1}, {2, 1}, {-2, -1}, {-2, 1}};
//             for(int i=0; i<8; i++){
//                 pair<char, int> test(char(current.first+moves[i].first), (current.second + moves[i].second));
//                 if(test == king) return level;
//                 if(test.first >='a' && test.first<='h' && test.second>=1 && test.second <=8 && !(verifica_vetor(visited, test))){
//                     visited.push_back(test);
//                     queue.insert_element(test);
//                 }
//             }
//             size--;
//         }
//     }
//     return level;
// }
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
    for(int u=0; u<n; u++){

        string c1, c2, c3, c4, k;
        cin>>c1>>c2>>c3>>c4>>k;
        pair<char, int>cav1 (c1[0], (int(c1[1])-48));
        pair<char, int>cav2 (c2[0], (int(c2[1])-48));
        pair<char, int>cav3 (c3[0], (int(c3[1])-48));
        pair<char, int>cav4 (c4[0], (int(c4[1])-48));
        pair<char, int>king (k[0], (int(k[1])-48));

        vector<pair<char, int>> cavalos;
        cavalos.push_back(cav1);
        cavalos.push_back(cav2);
        cavalos.push_back(cav3);
        cavalos.push_back(cav4);

        vector<int> founded;
        for(int i=0; i<4; i++){
            int t = bfs(cavalos[i], king)-1;
            founded.push_back(t);
        }
        bubble_sort(founded);
        int minimum = founded[0];
        cout<<minimum<<" ";
        for(int i=1; i<4; i++){
            if(founded[i] == minimum){
                cout<<founded[i]<<" ";
            }
        }
        cout<<endl;
    }

}