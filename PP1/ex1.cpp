#include<iostream>
#include<list>
using namespace std;

typedef unsigned int Vertex;

template <typename T>
class GraphAL 
{
    private:
        unsigned int num_vertices;
        unsigned int num_edges;
        list<T> *adj;
		
    public:
        GraphAL(unsigned int);
        ~GraphAL();

        void add_edge(Vertex, Vertex);
		void remove_edge(Vertex, Vertex);

        list<T> get_adj(Vertex v) { return adj[v]; }

        unsigned int get_num_vertices() { return num_vertices; }
        unsigned int get_num_edges() { return num_edges; }
};

template <typename T>
GraphAL<T>::GraphAL(unsigned int num_vertices): num_vertices(num_vertices) 
{
	adj = new list<Vertex>[num_vertices];
}


template <typename T>
GraphAL<T>::~GraphAL() 
{
	for (unsigned int u = 0; u < num_vertices; ++u) 
    {
		adj[u].clear();
	}

	delete[] adj;

	adj = nullptr;
	num_vertices = num_edges = 0;
}

template <typename T>
void GraphAL<T>::add_edge(Vertex u, Vertex v) 
{
	bool is_duplicated = false;

	for (auto item_vertex : adj[u]) 
    {
		if (v == item_vertex)
			is_duplicated = true;
	}

	for (auto item_vertex : adj[v])
	{
		if (u == item_vertex)
			is_duplicated = true;
	}

	if (!is_duplicated)
	{
		adj[u].push_back(v);	
		adj[v].push_back(u);

		num_edges++;
	}
}

template <typename T>
void GraphAL<T>::remove_edge(Vertex u, Vertex v)
{
	adj[u].remove(v);
	adj[v].remove(u);

	num_edges--;
}

template <typename T>
void display_list(list<T> &lst) 
{
	for (auto item_vertex : lst) 
    {
		cout << item_vertex << ", ";
	}
	cout << endl;
}


template <typename T>
void display_GraphAL(GraphAL<T> &g) 
{
	for (int v = 0; v < g.get_num_vertices(); v++) 
    {
		cout << "v[" << v << "]: ";

		list<T> lst = g.get_adj(v);

		display_list( lst );
	}
}


template <typename T>
void input_GraphAL(GraphAL<T> &g, unsigned int num_edges) 
{
	Vertex u = 0, v = 0;

	for (int i = 0; i < num_edges; ++i) 
    {
		cin >> u >> v;
		g.add_edge(u, v);
	}
}

int main() 
{
	unsigned int num_vertices = 0;
	unsigned int num_edges = 0;

	cin >> num_vertices >> num_edges;

	cout << "num_vertices: " << num_vertices << endl;
	cout << "num_edges: " << num_edges << endl;

	GraphAL<Vertex> g{num_vertices};

	input_GraphAL(g, num_edges);
	display_GraphAL(g);

	return 0;
}