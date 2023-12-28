#include <iostream>
#include <queue>
#include <vector>

#define SIZE 8

using namespace std;

class Position{
    public:
        pair<int, int> pos;
        int level;
        Position(pair<int, int> p, int w):pos(p), level(w){}
};





class Graph{
    private:
        vector<pair<int, int>> levels;
        vector<vector<int>> weights;
        vector<pair<int, int>> visited;
    public:
        Graph() : weights(SIZE, std::vector<int>(SIZE, -1)), visited(8) {}

        bool verifica_vetor(vector <pair<int, int>>, pair<int, int>);
        void bfs(pair<int, int>, pair<int, int>);
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
void Graph::bfs(pair<int, int> king, pair<int, int>knight){
    queue<Position>queue;
    queue.push(Position(king, 0));
    visited.push_back(king);
    weights[king.first][king.second] = 0;
    

    vector<pair<int, int>> moves = {{1, 2}, {1, -2}, {-1, -2},{-1, 2}, {2, -1}, {2, 1}, {-2, -1}, {-2, 1}};
    
    while(!queue.empty()){
        
        Position test = queue.front();
        queue.pop();
        for(int i=0; i<8; i++){
            
            pair<int, int> toadd((test.pos.first+moves[i].first), (test.pos.second+moves[i].second));
            if(toadd.first >=1 && toadd.first<=8 && toadd.second>=1 && toadd.second <=8 && !(verifica_vetor(visited, toadd))){
                
                visited.push_back(toadd);
                int toadd_level = test.level+1;
                queue.push(Position(toadd, toadd_level));
                weights[toadd.first][toadd.second] = toadd_level;
                cout<<toadd.first<<" "<<toadd.second<<" "<< toadd_level<<endl;
            }
        }
    }
}

void Graph::displayWeights(){
    cout<<"weights:"<<endl;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            cout << weights[i][j] << "\t";
        }
        cout << endl;
    }
}


int main(){
    pair<int, int> pairt(1,1);
    Graph graph;
    graph.bfs(pairt, pairt);
    cout<<endl<<"fim";
}