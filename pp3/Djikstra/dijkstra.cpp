#include <iostream>
#include <vector>
#include <list>
#include <limits>

using namespace std;

float inf = numeric_limits<float>::infinity();
typedef float Weight;

class Vertex
{
	public:
		unsigned int vertex;
		unsigned int pi;
		Weight distance;

		Vertex() {}
		Vertex(unsigned int vertex, unsigned int pi, Weight distance): vertex(vertex), pi(pi), distance(distance) {}
};

class VertexWeightPair
{
    public:
        Vertex vertex;
        Weight weight;

        VertexWeightPair(Vertex vertex, Weight weight): vertex(vertex), weight(weight) {}
};

class WeightedGraphAL 
{
    private:
        unsigned int num_vertices;
        unsigned int num_edges;
        list<VertexWeightPair> *adj;

    public:
        WeightedGraphAL(unsigned int);
        ~WeightedGraphAL();

        void add_edge(Vertex, Vertex, Weight);
		void remove_edge(Vertex, Vertex);

        list<VertexWeightPair> get_adj(Vertex v){return adj[v.vertex];}

        unsigned int get_num_vertices() { return num_vertices; }
        unsigned int get_num_edges() { return num_edges; }
};

WeightedGraphAL::WeightedGraphAL(unsigned int _num_vertices): num_vertices(_num_vertices)
{
	adj = new list<VertexWeightPair>[num_vertices + 1];
} 

WeightedGraphAL::~WeightedGraphAL() 
{
	for (unsigned int u = 0; u < num_vertices; ++u) 
    {
		adj[u].clear();
	}

	delete[] adj;

	adj = nullptr;
	num_vertices = num_edges = 0;
} 

void WeightedGraphAL::add_edge(Vertex u, Vertex v, Weight w) 
{
	bool is_duplicated = false;

	list<VertexWeightPair>::iterator it;

	for(it = adj[u.vertex].begin(); it != adj[u.vertex].end(); it++)
	{
		if(it->vertex.vertex == v.vertex){
			is_duplicated = true;
		}
	}

    for(it = adj[v.vertex].begin(); it != adj[v.vertex].end(); it++)
	{
		if(it->vertex.vertex == u.vertex){
			is_duplicated = true;
		}
	}

	if(!is_duplicated)
	{
		VertexWeightPair item_v{v, w};
        VertexWeightPair item_u{u, w};

		adj[u.vertex].push_back(item_v);	
        adj[v.vertex].push_back(item_u);
		
		num_edges++;
	}
}


void WeightedGraphAL:: remove_edge(Vertex u, Vertex v)
{
	list<VertexWeightPair>::iterator it_u = adj[u.vertex].begin();
    list<VertexWeightPair>::iterator it_v = adj[v.vertex].begin();

	for(; it_u != adj[u.vertex].end(); it_u++)
	{
		if(it_u->vertex.vertex == v.vertex)
		{
			adj[u.vertex].erase(it_u);	

			break;		
		}
	}

    for(; it_v != adj[v.vertex].end(); it_v++)
	{
		if(it_v->vertex.vertex == u.vertex)
		{
			adj[v.vertex].erase(it_v);

			break;		
		}
	}

    num_edges --;
}

void input_WeightedGraphAL(WeightedGraphAL &g, unsigned int num_edges, Vertex *vertex_list) 
{
	Vertex u{0, 0, inf};
	Vertex v{0, 0, inf};

	Weight w;

	for (int i = 0; i < num_edges; ++i) 
    {
		cin >> u.vertex >> v.vertex >> w;
		g.add_edge(u, v, w); 

		vertex_list[u.vertex] = u;
		vertex_list[v.vertex] = v;
	}
}

void display_list(list<VertexWeightPair> &lst)
{
    for(VertexWeightPair item_vertex: lst)
    {
        cout << "(" << item_vertex.vertex.vertex << ", " << item_vertex.weight << "), ";

		// if (item_vertex.vertex.vertex == 1)
		// 	cout << "vertice 1.pi: " << item_vertex.vertex.pi << " ; vertice 1.distance: " << item_vertex.vertex.distance << endl; 
    }
    cout << endl;
}

void display_graph(WeightedGraphAL &g)
{
	Vertex v{0, 0, inf};

    for(; v.vertex <= g.get_num_vertices(); v.vertex++)
    {
        cout<< "v[" << v.vertex << "]: ";
        list<VertexWeightPair> lst = g.get_adj(v);
        display_list(lst);
    }
}

////////////////////////////////////////////////////////////////////////
// Minimum Priority Queue:

template <typename T>
class MinPQueue
{
    private:
        unsigned int tam;
        unsigned int tam_heap;
        Vertex *Queue;

    public:
        MinPQueue(unsigned int);
        ~MinPQueue();

        void Insert(Vertex, int);
        Vertex Minimum() {return Queue[0]; }
        Vertex Extract_Min();
        // void Increase_Min(int, int);

        int Parent(int);
        int Left(int);
        int Right(int);

        void Min_HeapFy (int);
        void Build_Min_Heap ();
        
        Vertex *get_Queue() { return Queue; }
        unsigned int get_tam() { return tam; }
        unsigned int get_tam_heap() { return tam_heap; }
};

template <typename T>
MinPQueue<T>::MinPQueue(unsigned int tam): tam(tam)
{
    Queue = new Vertex[tam + 1];
    tam_heap = 0;
}

template <typename T>
MinPQueue<T>::~MinPQueue()
{
    delete[] Queue;

    tam = tam_heap = 0;
}

template <typename T>
void MinPQueue<T>::Insert(Vertex x, int i)
{
    Queue[i] = x;
    tam_heap++;
}

template <typename T>
Vertex MinPQueue<T>::Extract_Min()
{
    Vertex Min = Queue[1];

    for (int i = 2; i <= tam; i++)
    {
        Queue[i - 1] = Queue[i];
    }

    tam_heap--;

    return Min;
}

template <typename T>
int MinPQueue<T>::Parent(int i)
{
    return (i / 2);
}

template <typename T>
int MinPQueue<T>::Left(int i)
{
    return (2 * i);
}

template <typename T>
int MinPQueue<T>::Right(int i)
{
    return ((2 * i) + 1);
}

template <typename T>
void MinPQueue<T>::Min_HeapFy(int i)
{
    int l = Left(i), r = Right(i), smallest;

    // cout << "left: " << l << " right: " << r << " tam_heap: " << tam_heap << endl;

    if ((l <= (tam_heap)) && (Queue[l].vertex < Queue[i].vertex))
        smallest = l;

    else smallest = i;

    if ((r <= (tam_heap)) && (Queue[r].vertex < Queue[smallest].vertex))
        smallest = r;
    
    if (smallest != i)
    {
        Vertex aux = Queue[i];
        Queue[i] = Queue[smallest];
        Queue[smallest] = aux;

        // cout << "=== S[i]: " << Queue[i].vertex << " S[smallest]: " << Queue[smallest].vertex << endl;

        Min_HeapFy(smallest);
    }
}

template <typename T>
void MinPQueue<T>::Build_Min_Heap()
{
    for (int i = tam_heap / 2; i > 0; i--)
    {
        // cout << "i: " << i << " tam_heap: " << tam_heap << endl;
        Min_HeapFy(i);
    }
}

template <typename T>
void Display_list (MinPQueue<T> &Q)
{
    cout << "=== Vector: ===" << endl;

    Vertex *lst = Q.get_Queue();
    int tam_lst = Q.get_tam_heap();

    // cout << "Tam_lst: " << tam_lst << "lst[0]: " << lst[0].vertex << endl;
 
    for (int item = 1; item <= tam_lst; item++)
        cout << lst[item].vertex << ", ";
    
    cout << endl;
}

////////////////////////////////////////////////////////////////////////
// Dijkstra:

class Dijkstra
{
	public:
		void Initialize(Vertex *, unsigned int);
        void Relax(Vertex, Vertex, Weight, Vertex *);
        void Dijkstra_process(Vertex *, unsigned int, MinPQueue<Vertex> &, WeightedGraphAL &);
};

void Dijkstra::Initialize(Vertex *vertex_list, unsigned int origin_s)
{
	vertex_list[origin_s].distance = 0;
}

void Dijkstra::Relax(Vertex u, Vertex v, Weight w, Vertex *vertex_list)
{
    // cout << "Vertex u: " << u.vertex << ", Vertex v: " << v.vertex << ", Weight w: " << w << endl;
    // cout << "Vertex v.distance: " << v.distance << ", Vertex u.distance: " << u.distance <<", Vertex u.distance + w: " << (u.distance + w) << endl;
    // cout << "Teste de Vertex_list[1].distance: " << vertex_list[1].distance << ", E teste de NEW Vertex_list[3].distance: " << vertex_list[3].distance << endl;

    if (vertex_list[v.vertex].distance > (vertex_list[u.vertex].distance + w))
    {
        // cout << endl;
        // cout << "Entrou!" << endl;
        vertex_list[v.vertex].distance = (vertex_list[u.vertex].distance + w);
        vertex_list[v.vertex].pi = vertex_list[u.vertex].vertex;

        // cout << "NEW Vertex v.distance: " << vertex_list[v.vertex].distance << ", NEW Vertex v.pi: " << vertex_list[v.vertex].pi << endl;
        // cout << endl;
    }
}

void Dijkstra::Dijkstra_process(Vertex *vertex_list, unsigned int origin_s, MinPQueue<Vertex> &Q, WeightedGraphAL &g)
{
    int cont = 1;

    Initialize(vertex_list, origin_s);

    Vertex S[g.get_num_vertices() + 1];

    for (int i = 1; i <= g.get_num_vertices(); i++)
        Q.Insert(vertex_list[i], i);

    while (Q.get_tam_heap() != 0)
    {
        Vertex u = Q.Extract_Min();
        Q.Build_Min_Heap();
        // Display_list(Q);

        S[cont] = u;
        cont++;

        list<VertexWeightPair> lst = g.get_adj(u);

        for(VertexWeightPair item_vertex : lst)
        {
            // cout << "item_vertex.vertex: " << item_vertex.vertex.vertex << "item_vertex.weight: " << item_vertex.weight << endl;
            Relax(vertex_list[u.vertex], item_vertex.vertex, item_vertex.weight, vertex_list);
        }
    }
}

int main() 
{
	unsigned int num_vertices = 0;
	unsigned int num_edges = 0;
	unsigned int origin_s = 0;
	unsigned int end = 0;
    Vertex *S;

	cin >> num_vertices >> num_edges;

	Vertex vertex_list[num_vertices + 1];

	cout << "num_vertices: " << num_vertices << endl;
	cout << "num_edges: " << num_edges << endl;

    WeightedGraphAL g{num_vertices};

	input_WeightedGraphAL(g, num_edges, vertex_list);

    display_graph(g);

	Dijkstra dikstra;

	cin >> origin_s >> end;

    MinPQueue<Vertex> Q{num_vertices};

	dikstra.Dijkstra_process(vertex_list, origin_s, Q, g);

	// cout << "Start in Vertex: " << origin_s << ", with distance = " << vertex_list[origin_s].distance << endl;
	// cout << "Example of non-start Vertex: 2" << ", with distance = " << vertex_list[2].distance << endl;

    cout << "Path from end (" << end << ") to start: (" << origin_s << "), with Minimum Weight = " << vertex_list[end].distance << " ; " << end;

    while (end != origin_s)
    {
        // cout << "Vertex.vertex: " << vertex_list[end].vertex << ", Vertex.pi: " << vertex_list[end].pi << ", Vertex.distance: " << vertex_list[end].distance << endl;
        cout << " -> " << vertex_list[end].pi;
        end = vertex_list[end].pi;
    }

	return 0;
}
