#include<iostream>
#include<cstdlib> // atoi
#include<vector>
#include<list>
#include <iomanip> // setw
using namespace std;

typedef unsigned int Vertex;
typedef unsigned int Weight;

class Edge 
{
    public:
        Weight weight;
        Edge(): weight(0) {} 
        Edge(Weight _weight): weight(_weight) {} 
};

class GraphAM 
{
    private:
        unsigned int num_vertices;
        unsigned int num_edges;
        Edge **adj;

    public:
        GraphAM(unsigned int);
        ~GraphAM();

        void add_edge(Vertex, Vertex);

        std::list<Vertex> get_adj(Vertex);
        Weight get_weight_edge(Vertex, Vertex);

        void display_matadj_GraphAM(GraphAM&);

        unsigned int get_num_vertices();
        unsigned int get_num_edges();
};

unsigned int GraphAM::get_num_vertices() 
{
	return num_vertices;
}

unsigned int GraphAM::get_num_edges() 
{
	return num_edges;
}

GraphAM::GraphAM(unsigned int _num_vertices): num_vertices(_num_vertices), num_edges(0) 
{
	const unsigned int LINHAS = num_vertices;
	const unsigned int COLUNAS = num_vertices;

	adj = new Edge*[LINHAS];

	for (int i = 0; i < LINHAS; ++i) 
    {
		adj[i] = new Edge[COLUNAS];
	}
} 

GraphAM::~GraphAM() 
{
	const unsigned int LINHAS = num_vertices;

	for (int i = 0; i < LINHAS; ++i) 
    {
		delete[] adj[i];
	}

	delete[] adj;
} 

void GraphAM::add_edge(Vertex u, Vertex v) 
{
	Edge edge{1};
	adj[u][v] = edge;
	adj[v][u] = edge;
	num_edges++;
}

std::list<Vertex> GraphAM::get_adj(Vertex u) 
{
	std::list<Vertex> values;

	for (int v = 0; v < num_vertices; ++v) 
    {
		if (adj[u][v].weight != 0) 
        {
			values.push_back(v);
		}
	}
	return values;
}

Weight GraphAM::get_weight_edge(Vertex u, Vertex v) 
{
	return adj[u][v].weight;
}

void input_GraphAM(GraphAM &g, unsigned int num_edges) 
{
	Vertex u = 0, v = 0;

	for (int i = 0; i < num_edges; ++i) 
    {
		cin >> u >> v;
		g.add_edge(u, v);
	}
}

void display_matadj_GraphAM(GraphAM &g) 
{
    int k = 2; // largura do campo numérico

    for (unsigned int i = 0; i < g.get_num_vertices(); i++) 
    {
            for (unsigned int j = 0; j < g.get_num_vertices(); j++)
                cout << std::setw(k) << g.get_weight_edge(i, j);

            cout << endl;
    }
}

int main() 
{
	unsigned int num_vertices = 0;
	unsigned int num_edges = 0;

	cin >> num_vertices >> num_edges;

	cout << "num_vertices: " << num_vertices << endl;
	cout << "num_edges: " << num_edges << endl;

    GraphAM g{num_vertices};

	input_GraphAM(g, num_edges);

    display_matadj_GraphAM(g);

	return 0;
}