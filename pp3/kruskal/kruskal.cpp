#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Graph{
    private://          v1 v2 peso
        vector<pair<pair<int,int>,float>> graph;
        vector<pair<pair<int,int>,float>> mst;
        int numVertices;
        int *parent;
    public:
        Graph(int);
        ~Graph();
        void addEdge(int, int, float);
        void makeSet(int);
        int findSet(int);
        void unionSet(int, int);
        void kruskal();
        void print();
        void bubbleSort(vector<pair<pair<int,int>,float>>);
};

Graph::Graph(int n){
    numVertices= n;
    parent = new int[numVertices];


}

Graph::~Graph(){
    graph.clear();
    mst.clear();

}

void Graph::addEdge(int u, int v, float weight){
    pair<pair<int,int>,float> weightedEdge;
    weightedEdge.first.first = u;
    weightedEdge.first.second = v;
    weightedEdge.second = weight;
    graph.push_back(weightedEdge);
}

void Graph::makeSet(int n){
    parent[n] = n;
}

int Graph::findSet(int i){
    if(i == parent[i]){
        return i;
    }else{
        return findSet(parent[i]);
    }
}

void Graph:: unionSet(int u, int v){
    parent[u] = parent[v];
}


void Graph:: bubbleSort(vector<pair<pair<int,int>,float>> graph){
    pair<pair<int,int>,float> temp;
    int n = graph.size();

    for(int i=0; i<n; i++){
        for(int j=0; j< (n-i-1); j++){
            if(graph[j].second > graph[j+1].second){
                swap(graph[j], graph[j+1]);
            }
        }
    }
}


void Graph::kruskal(){
    for(int o=0; o<numVertices; o++){
        makeSet(o);
    }
    bubbleSort(graph);
    for(int i=0; i<graph.size(); i++){
        if(findSet(graph[i].first.first) != findSet(graph[i].first.second)){
            mst.push_back(graph[i]);
            unionSet(graph[i].first.first, graph[i].first.second);
        }
    }

}

void Graph::print(){
    for (int i = 0; i < mst.size(); i++) {
        cout << mst[i].first.first << " " << mst[i].first.second << " "<< mst[i].second<<endl;
    }
}

int main() {
  Graph g(9);
  g.addEdge(0,1,4);
  g.addEdge(1,2,8);
  g.addEdge(2,3,7);
  g.addEdge(3,4,9);
  g.addEdge(4,5,10);
  g.addEdge(3,5,14);
  g.addEdge(2,5,4);
  g.addEdge(5,6,2);
  g.addEdge(6,8,6);
  g.addEdge(6,7,1);
  g.addEdge(7,0,8);
  g.addEdge(7,1,11);
  g.addEdge(7,8,7);
  g.addEdge(8,2,2);
  g.kruskal();
  //g.print();
}
