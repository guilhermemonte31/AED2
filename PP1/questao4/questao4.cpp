#include<iostream>
#include<cstdlib> // atoi
#include<vector>
#include<list>
#include <iomanip> // setw
#include <limits>
using namespace std;


typedef unsigned int Vertex;
typedef float Weight;
std::numeric_limits<float>:: infinity();
class Edge 
{
    public:
        Weight weight;
        Edge(): weight() {} 
        Edge(Weight _weight): weight(_weight) {} 
};

class WeightedGraphAM 
{
    private:
        unsigned int num_vertices;
        unsigned int num_edges;
        Edge **adj;

    public:
        WeightedGraphAM(unsigned int);
        ~WeightedGraphAM();

        void add_edge(Vertex, Vertex, Weight);
		void remove_edge(Vertex, Vertex);

        std::list<Vertex> get_adj(Vertex);
        Weight get_weight_edge(Vertex, Vertex);

        void display_matadj_WeightedGraphAM(WeightedGraphAM&);

        unsigned int get_num_vertices();
        unsigned int get_num_edges();
};

unsigned int WeightedGraphAM::get_num_vertices() 
{
	return num_vertices;
}

unsigned int WeightedGraphAM::get_num_edges() 
{
	return num_edges;
}

WeightedGraphAM::WeightedGraphAM(unsigned int _num_vertices): num_vertices(_num_vertices), num_edges(0) 
{
	const unsigned int LINHAS = num_vertices;
	const unsigned int COLUNAS = num_vertices;

	adj = new Edge*[LINHAS];

	for (int i = 0; i < LINHAS; ++i) 
    {
		adj[i] = new Edge[COLUNAS];
	}
} 

WeightedGraphAM::~WeightedGraphAM() 
{
	const unsigned int LINHAS = num_vertices;

	for (int i = 0; i < LINHAS; ++i) 
    {
		delete[] adj[i];
	}

	delete[] adj;
} 

void WeightedGraphAM::add_edge(Vertex u, Vertex v, Weight w) 
{
	Edge edge{w};
	adj[u][v] = edge;
	adj[v][u] = edge;
	num_edges++;
}


void WeightedGraphAM:: remove_edge(Vertex u, Vertex v){
	Edge edge{0};
	adj[u][v] = edge;
	adj[v][u] = edge;
	num_edges--;
}

std::list<Vertex> WeightedGraphAM::get_adj(Vertex u) 
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

Weight WeightedGraphAM::get_weight_edge(Vertex u, Vertex v) 
{
	return adj[u][v].weight;
}

void input_WeightedGraphAM(WeightedGraphAM &g, unsigned int num_edges) 
{
	Vertex u = 0, v = 0;
	Weight w=0;

	for (int i = 0; i < num_edges; ++i) 
    {
		cin >> u >> v >> w;
		g.add_edge(u, v, w);
	}
}

void display_matadj_WeightedGraphAM(WeightedGraphAM &g) 
{
    int k = 2;

    for (unsigned int i = 0; i < g.get_num_vertices(); i++) 
    {
            for (unsigned int j = 0; j < g.get_num_vertices(); j++)
                cout << g.get_weight_edge(i, j)<< " ";

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

    WeightedGraphAM g{num_vertices};

	input_WeightedGraphAM(g, num_edges);

    display_matadj_WeightedGraphAM(g);
	unsigned int v1 = 0;
	unsigned int v2 = 0;
	cout<< endl<< "inserir vertices da aresta a ser removida: ";
	cin>> v1>> v2;
	g.remove_edge(v1, v2);
    display_matadj_WeightedGraphAM(g);

	return 0;
}