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

class DiGraphAL {
private:
	unsigned int num_vertices;
	unsigned int num_edges;
	list<Vertex> *adj;
public:
	DiGraphAL(unsigned int);
	~DiGraphAL();
	void add_edge(Vertex, Vertex);
	void remove_edge(Vertex, Vertex);
	list<Vertex> get_adj(Vertex v) { return adj[v]; }
	unsigned int get_num_vertices() { return num_vertices; }
	unsigned int get_num_edges() { return num_edges; }
};

DiGraphAL::DiGraphAL(unsigned int num_vertices): num_vertices(num_vertices) {
	adj = new list<Vertex>[num_vertices];
}


DiGraphAL::~DiGraphAL() {
	for (unsigned int u = 0; u < num_vertices; ++u) {
		adj[u].clear();
	}
	delete[] adj;
	adj = nullptr;
	num_vertices = num_edges = 0;
}

void DiGraphAL::add_edge(Vertex u, Vertex v) {
	bool is_duplicated = false;
	list<Vertex>::iterator it;
	for(it = adj[u].begin(); it!= adj[u].end(); it++){
		if(*it == v){
			is_duplicated = true;
		}
	}
	if(!is_duplicated){
		adj[u].push_back(v);	
		
		num_edges++;
	}


}

void DiGraphAL:: remove_edge(Vertex u, Vertex v){
	for(list<Vertex>::iterator it = adj[u].begin(); it!= adj[u].end(); it++){
		if(*it == v){
			adj[u].remove(v);
			num_edges --;
			break;		
		}
	}

}


void display_list(list<Vertex> &lst) {
	for (Vertex vertex : lst) {
		cout << vertex << ", ";
	}
	cout << endl;
}


void display_graph(DiGraphAL &g) {
	for (int v = 0; v < g.get_num_vertices(); v++) {
		cout << "v[" << v << "]: ";
		list<Vertex> lst = g.get_adj(v);
		display_list( lst );
	}
}


void input_graph(DiGraphAL &g, unsigned int num_edges) {
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
	DiGraphAL g{num_vertices}; 
	input_graph(g, num_edges);
	display_graph(g);
	cout<< endl<< "inserir vertices da aresta a ser removida: ";
	cin>> v1>> v2;
	g.remove_edge(v1, v2);
	display_graph(g);

	return 0;
}






