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

class DigraphAM 
{
    private:
        unsigned int num_vertices;
        unsigned int num_edges;
        Edge **adj;

    public:
        DigraphAM(unsigned int);
        ~DigraphAM();

        void add_edge(Vertex, Vertex);
        void remove_edge(Vertex, Vertex);

        std::list<Vertex> get_adj(Vertex);
        Weight get_weight_edge(Vertex, Vertex);

        void display_matadj_DigraphAM(DigraphAM&);

        unsigned int get_num_vertices(){return num_vertices;}
        unsigned int get_num_edges(){return num_edges;}
};

DigraphAM::DigraphAM(unsigned int _num_vertices): num_vertices(_num_vertices), num_edges(0) 
{
	const unsigned int LINHAS = num_vertices;
	const unsigned int COLUNAS = num_vertices;

	adj = new Edge*[LINHAS];

	for (int i = 0; i < LINHAS; ++i) 
    {
		adj[i] = new Edge[COLUNAS];
	}
} 

DigraphAM::~DigraphAM() 
{
	const unsigned int LINHAS = num_vertices;

	for (int i = 0; i < LINHAS; ++i) 
    {
		delete[] adj[i];
	}

	delete[] adj;
} 

void DigraphAM::add_edge(Vertex u, Vertex v) 
{
	bool is_duplicated = false;
	Edge edge{1};
	if(adj[u][v].weight == 0){	
		adj[u][v] = edge;
		num_edges++;
	}else is_duplicated = true;

	if(is_duplicated) cout<<"Duplicado."<<endl;
}

void DigraphAM:: remove_edge(Vertex u, Vertex v){
    Edge edge{0};
	if(adj[u][v].weight != 0){
    	adj[u][v] = edge;
	    num_edges--;

	}
	else cout<<"Aresta inexistente" <<endl;
    // adj[u][v] = edge;
    // num_edges--;
}

std::list<Vertex> DigraphAM::get_adj(Vertex u) 
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

Weight DigraphAM::get_weight_edge(Vertex u, Vertex v) 
{
	return adj[u][v].weight;
}

void input_DigraphAM(DigraphAM &g, unsigned int num_edges) 
{
	Vertex u = 0, v = 0;

	for (int i = 0; i < num_edges; ++i) 
    {
		cin >> u >> v;
		g.add_edge(u, v);
	}
}

void display_matadj_DigraphAM(DigraphAM &g) 
{
    int k = 2;

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

    DigraphAM g{num_vertices};

	input_DigraphAM(g, num_edges);

	unsigned int v1 = 0;
	unsigned int v2 = 0;
    display_matadj_DigraphAM(g);
	cout<< endl<< "inserir vertices da aresta a ser removida: ";
	cin>> v1>> v2;
	g.remove_edge(v1, v2);
	display_matadj_DigraphAM(g);

	return 0;
}