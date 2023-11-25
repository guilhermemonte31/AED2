#include <iostream>
#include <list>
#include <vector>
using namespace std;

typedef unsigned int Vertex;
typedef float Weight;


class VertexWeightPair{
    public:
        Vertex vertex;
        Weight weight;
        VertexWeightPair(Vertex vertex, Weight weight): vertex(vertex), weight(weight) {}
};


class WeightedGraphAL{
    private:
        unsigned int num_vertices;
        unsigned int num_edges;
        list<VertexWeightPair> *adj;
    public:
        WeightedGraphAL(unsigned int);
        ~WeightedGraphAL();
        void add_edge(Vertex, Vertex, Weight);
        void remove_edge(Vertex, Vertex);
        list<VertexWeightPair> get_adj(Vertex v){return adj[v];}
        unsigned int get_num_vertices(){return num_vertices;}
        unsigned int get_num_edges(){return num_edges;}
};

WeightedGraphAL:: WeightedGraphAL(unsigned int num_vertices): num_vertices(num_vertices){
    adj = new list<VertexWeightPair>[num_vertices];
}

WeightedGraphAL:: ~WeightedGraphAL(){
    for(unsigned int u=0; u<num_vertices; u++){
        adj[u].clear();
    }
    delete[] adj;
    adj = nullptr;
    num_vertices = num_edges = 0;
}

void WeightedGraphAL:: add_edge(Vertex u, Vertex v, Weight w){
    VertexWeightPair item_v{v, w};
    adj[u].push_back(item_v);
    VertexWeightPair item_u{u, w};
    adj[v].push_back(item_u);
    num_edges++;
}

void WeightedGraphAL:: remove_edge(Vertex u, Vertex v){
    adj[u].remove(v);
    adj[v].remove(u);
    num_edges --;
    // it = find(adj[u].begin(), adj[u].end(), v);
    // // adj[u].erase(std::remove(adj[u].begin(), adj[u].end(), v));
    // // adj[v].erase(std::remove(adj[v].begin(), adj[v].end(), u), adj[v].end());

}

void display_list(list<VertexWeightPair> &lst){
    for(VertexWeightPair item_vertex: lst){
        cout<<"("<<item_vertex.vertex<<", "<<item_vertex.weight<<"), ";
    }
    cout<<endl;
}

void display_graph(WeightedGraphAL &g){
    for(int v=0; v< g.get_num_vertices(); v++){
        cout<< "v["<<v<<"]: ";
        list<VertexWeightPair> lst = g.get_adj(v);
        display_list(lst);
    }
}

void input_graph(WeightedGraphAL &g, unsigned int num_edges){
    Vertex u=0, v=0;
    Weight w;
    for(int i=0; i<num_edges; i++){
        cin>> u>> v >> w;
        g.add_edge(u, v, w);
    }

}

int main(){
    unsigned int num_vertices=0;
    unsigned int num_edges=0;
    cin>> num_vertices>> num_edges;
	cout << "num_vertices:" << num_vertices << endl;
	cout << "num_edges:" << num_edges << endl;
    WeightedGraphAL g{num_vertices};
    input_graph(g, num_edges);
    display_graph(g);
	unsigned int v1 = 0;
	unsigned int v2 = 0;
	cout<< endl<< "inserir vertices da aresta a ser removida: ";
	cin>> v1>> v2;
	g.remove_edge(v1, v2);
    display_graph(g);
}

