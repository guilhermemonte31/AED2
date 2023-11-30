#include<iostream>
#include<cstdlib> // atoi
#include<vector>
#include<list>
#include <iomanip> // setw
#include <limits>
using namespace std;

float inf = numeric_limits<float>::infinity();
typedef unsigned int Vertex;
typedef float Weight;



class WeightedDigraphAM 
{
    private:
        unsigned int num_vertices;
        unsigned int num_edges;
        Weight **adj;

    public:
        WeightedDigraphAM(unsigned int);
        ~WeightedDigraphAM();

        void add_edge(Vertex, Vertex, Weight);
		void remove_edge(Vertex, Vertex);

        std::list<Vertex> get_adj(Vertex);
        Weight get_weight_edge(Vertex, Vertex);

        void display_matadj_WeightedDigraphAM(WeightedDigraphAM&);

        unsigned int get_num_vertices();
        unsigned int get_num_edges();
};

unsigned int WeightedDigraphAM::get_num_vertices() 
{
	return num_vertices;
}

unsigned int WeightedDigraphAM::get_num_edges() 
{
	return num_edges;
}

WeightedDigraphAM::WeightedDigraphAM(unsigned int _num_vertices): num_vertices(_num_vertices), num_edges(0) 
{
	const unsigned int LINHAS = num_vertices;
	const unsigned int COLUNAS = num_vertices;

	adj = new Weight*[LINHAS];

	for (int i = 0; i < LINHAS; ++i) 
    {
		adj[i] = new Weight[COLUNAS];
	}

	for(int i=0; i<LINHAS; i++){
		for( int j=0; j< COLUNAS; j++){
			adj[i][j] = inf;
		}
	}
} 

WeightedDigraphAM::~WeightedDigraphAM() 
{
	const unsigned int LINHAS = num_vertices;

	for (int i = 0; i < LINHAS; ++i) 
    {
		delete[] adj[i];
	}

	delete[] adj;
} 

void WeightedDigraphAM::add_edge(Vertex u, Vertex v, Weight w) 
{
	Weight edge{w};
	if( adj[u][v] == inf){
		adj[u][v] = edge;
		num_edges++;
	}

}


void WeightedDigraphAM:: remove_edge(Vertex u, Vertex v){
	Weight edge{inf};
	if(adj[u][v] != inf){
		adj[u][v] = edge;
		num_edges--;
	}

}

std::list<Vertex> WeightedDigraphAM::get_adj(Vertex u) 
{
	std::list<Vertex> values;

	for (int v = 0; v < num_vertices; ++v) 
    {
		if (adj[u][v] != 0) 
        {
			values.push_back(v);
		}
	}
	return values;
}

Weight WeightedDigraphAM::get_weight_edge(Vertex u, Vertex v) 
{
	return adj[u][v];
}

void input_WeightedDigraphAM(WeightedDigraphAM &g, unsigned int num_edges) 
{
	Vertex u = 0, v = 0;
	Weight w=inf;

	for (int i = 0; i < num_edges; ++i) 
    {
		cin >> u >> v >> w;
		g.add_edge(u, v, w); 
	}
}

void display_matadj_WeightedDigraphAM(WeightedDigraphAM &g) 
{

    for (unsigned int i = 0; i < g.get_num_vertices(); i++) 
    {
            for (unsigned int j = 0; j < g.get_num_vertices(); j++)
                cout << g.get_weight_edge(i, j)<< "   ";


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

    WeightedDigraphAM g{num_vertices};

	input_WeightedDigraphAM(g, num_edges);

    display_matadj_WeightedDigraphAM(g);
	unsigned int v1 = 0;
	unsigned int v2 = 0;
	cout<< endl<< "inserir vertices da aresta a ser removida: ";
	cin>> v1>> v2;
	g.remove_edge(v1, v2);
    display_matadj_WeightedDigraphAM(g);

	return 0;
}