#include <iostream>
#include <vector>
#include <list>

using namespace std;

typedef unsigned int Vertex;
typedef float Weight;

class VertexWeightPair
{
    public:
        Vertex vertex;
        Weight weight;
        VertexWeightPair(Vertex vertex, Weight weight): vertex(vertex), weight(weight) {}
};

class WeightedDigraphAL 
{
    private:
        unsigned int num_vertices;
        unsigned int num_edges;
        list<VertexWeightPair> *adj;

    public:
        WeightedDigraphAL(unsigned int);
        ~WeightedDigraphAL();

        void add_edge(Vertex, Vertex, Weight);
		void remove_edge(Vertex, Vertex);

        list<VertexWeightPair> get_adj(Vertex v){return adj[v];}

        unsigned int get_num_vertices() { return num_vertices; }
        unsigned int get_num_edges() { return num_edges; }
};

WeightedDigraphAL::WeightedDigraphAL(unsigned int _num_vertices): num_vertices(_num_vertices)
{
	adj = new list<VertexWeightPair>[num_vertices];
} 

WeightedDigraphAL::~WeightedDigraphAL() 
{
	for (unsigned int u = 0; u < num_vertices; ++u) 
    {
		adj[u].clear();
	}

	delete[] adj;

	adj = nullptr;
	num_vertices = num_edges = 0;
} 

void WeightedDigraphAL::add_edge(Vertex u, Vertex v, Weight w) 
{
	bool is_duplicated = false;

	list<VertexWeightPair>::iterator it;

	for(it = adj[u].begin(); it!= adj[u].end(); it++)
	{
		if(it->vertex == v){
			is_duplicated = true;
		}
	}
	if(!is_duplicated)
	{
		VertexWeightPair item_v{v, w};

		adj[u].push_back(item_v);	
		
		num_edges++;
	}
}


void WeightedDigraphAL:: remove_edge(Vertex u, Vertex v)
{
	list<VertexWeightPair>::iterator it_u = adj[u].begin();

	for(; it_u != adj[u].end(); it_u++)
	{
		if(it_u->vertex == v)
		{
			adj[u].erase(it_u);	

			num_edges --;
			break;		
		}
	}

}

void input_WeightedDigraphAL(WeightedDigraphAL &g, unsigned int num_edges) 
{
	Vertex u = 0, v = 0;
	Weight w;

	for (int i = 0; i < num_edges; ++i) 
    {
		cin >> u >> v >> w;
		g.add_edge(u, v, w); 
	}
}

void display_list(list<VertexWeightPair> &lst)
{
    for(VertexWeightPair item_vertex: lst)
    {
        cout << "(" << item_vertex.vertex << ", " << item_vertex.weight << "), ";
    }
    cout<<endl;
}

void display_graph(WeightedDigraphAL &g)
{
    for(int v=0; v< g.get_num_vertices(); v++)
    {
        cout<< "v[" << v << "]: ";
        list<VertexWeightPair> lst = g.get_adj(v);
        display_list(lst);
    }
}

int main() 
{
	unsigned int num_vertices = 0;
	unsigned int num_edges = 0;

	cin >> num_vertices >> num_edges;

	cout << "num_vertices: " << num_vertices << endl;
	cout << "num_edges: " << num_edges << endl;

    WeightedDigraphAL g{num_vertices};

	input_WeightedDigraphAL(g, num_edges);

    display_graph(g);

	return 0;
}