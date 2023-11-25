#include<iostream>
#include<list>
using namespace std;

typedef unsigned int Vertex;

// class ItemVertex {
// public:
// 	unsigned int value;
// 	ItemVertex() {}
// 	ItemVertex(unsigned int value): value(value) {} 
// };

class Graph {
private:
	unsigned int num_vertices;
	unsigned int num_edges;
	list<Vertex> *adj;
public:
	Graph(unsigned int);
	~Graph();
	void add_edge(Vertex, Vertex);
	void remove_edge(Vertex, Vertex);
	list<Vertex> get_adj(Vertex v) { return adj[v]; }
	unsigned int get_num_vertices() { return num_vertices; }
	unsigned int get_num_edges() { return num_edges; }
};

Graph::Graph(unsigned int num_vertices): num_vertices(num_vertices) {
	adj = new list<Vertex>[num_vertices];
}


Graph::~Graph() {
	for (unsigned int u = 0; u < num_vertices; ++u) {
		adj[u].clear();
	}
	delete[] adj;
	adj = nullptr;
	num_vertices = num_edges = 0;
}

void Graph::add_edge(Vertex u, Vertex v) {
	adj[u].push_back(v);	
	
	num_edges++;
}

void Graph:: remove_edge(Vertex u, Vertex v){
	adj[u].remove(v);
	num_edges --;
}


void display_list(list<Vertex> &lst) {
	for (Vertex vertex : lst) {
		cout << vertex << ", ";
	}
	cout << endl;
}


void display_graph(Graph &g) {
	for (int v = 0; v < g.get_num_vertices(); v++) {
		cout << "v[" << v << "]: ";
		list<Vertex> lst = g.get_adj(v);
		display_list( lst );
	}
}


void input_graph(Graph &g, unsigned int num_edges) {
	Vertex u = 0, v = 0;
	for (int i = 0; i < num_edges; ++i) {
		cin >> u >> v;
		g.add_edge(u, v);
	}
}

int main() {
	unsigned int num_vertices = 0;
	unsigned int num_edges = 0;
	unsigned int v1 = 0;
	unsigned int v2 = 0;
	cin >> num_vertices >> num_edges;
	cout << "num_vertices:" << num_vertices << endl;
	cout << "num_edges:" << num_edges << endl;
	Graph g{num_vertices}; //constroi o grafo com o num de vertices
	input_graph(g, num_edges);
	display_graph(g);
	cout<< endl<< "inserir vertices da aresta a ser removida: ";
	cin>> v1>> v2;
	g.remove_edge(v1, v2);
	display_graph(g);

	return 0;
}






