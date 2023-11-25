#include<iostream>
#include<list>
using namespace std;

typedef unsigned int Vertex;

class ItemVertex {
public:
	unsigned int value;
	ItemVertex() {}
	ItemVertex(unsigned int value): value(value) {} 
};

template <typename T>
class Graph {
private:
	unsigned int num_vertices;
	unsigned int num_edges;
	list<T> *adj;
public:
	Graph(unsigned int);
	~Graph();
	void add_edge(Vertex, Vertex);
	void remove_edge(Vertex, Vertex);
	list<T> get_adj(Vertex v) { return adj[v]; }
	unsigned int get_num_vertices() { return num_vertices; }
	unsigned int get_num_edges() { return num_edges; }
};

template <typename T>
Graph<T>::Graph(unsigned int num_vertices): num_vertices(num_vertices) {
	adj = new list<ItemVertex>[num_vertices];
}


template <typename T>
Graph<T>::~Graph() {
	for (unsigned int u = 0; u < num_vertices; ++u) {
		adj[u].clear();
	}
	delete[] adj;
	adj = nullptr;
	num_vertices = num_edges = 0;
	cout << "\nbye graph\n";
}

template <typename T>
void Graph<T>::add_edge(Vertex u, Vertex v) {
	ItemVertex item_v{v};
	adj[u].push_back(item_v);	
	ItemVertex item_u{u};
	adj[v].push_back(item_u);	
	num_edges++;
}

template <typename T>
void Graph<T>:: remove_edge(Vertex u, Vertex v){
	
}




template <typename T>
void display_list(list<T> &lst) {
	for (auto item_vertex : lst) {
		cout << item_vertex.value << ", ";
	}
	cout << endl;
}


template <typename T>
void display_graph(Graph<T> &g) {
	for (int v = 0; v < g.get_num_vertices(); v++) {
		cout << "v[" << v << "]: ";
		list<T> lst = g.get_adj(v);
		display_list( lst );
	}
}


template <typename T>
void input_graph(Graph<T> &g, unsigned int num_edges) {
	Vertex u = 0, v = 0;
	for (int i = 0; i < num_edges; ++i) {
		cin >> u >> v;
		g.add_edge(u, v);
	}
}

int main() {
	unsigned int num_vertices = 0;
	unsigned int num_edges = 0;
	cin >> num_vertices >> num_edges;
	cout << "num_vertices:" << num_vertices << endl;
	cout << "num_edges:" << num_edges << endl;
	Graph<ItemVertex> g{num_vertices}; //constroi o grafo com o num de vertices
	input_graph(g, num_edges);
	display_graph(g);

	return 0;
}






