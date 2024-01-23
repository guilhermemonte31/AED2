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
        unsigned int id;
		Weight distance;

		Vertex() {}
		Vertex(unsigned int vertex, unsigned int pi, unsigned int id, Weight distance): vertex(vertex), pi(pi), id(id), distance(distance) {}
};

class VertexWeightPair
{
    public:
        Vertex vertex;
        Weight weight;

        VertexWeightPair(Vertex vertex, Weight weight): vertex(vertex), weight(weight) {}
};

class Brain 
{
    private:
        unsigned int num_vertices;
        unsigned int num_edges;
        list<VertexWeightPair> *adj;

    public:
        Brain(unsigned int);
        ~Brain();

        void add_edge(Vertex, Vertex, Weight);
		void remove_edge(Vertex, Vertex);

        list<VertexWeightPair> get_adj(Vertex v){return adj[v.vertex];}

        unsigned int get_num_vertices() { return num_vertices; }
        unsigned int get_num_edges() { return num_edges; }
};

Brain::Brain(unsigned int _num_vertices): num_vertices(_num_vertices)
{
	adj = new list<VertexWeightPair>[num_vertices + 1];
} 

Brain::~Brain() 
{
	for (unsigned int u = 0; u < num_vertices; ++u) 
    {
		adj[u].clear();
	}

	delete[] adj;

	adj = nullptr;
	num_vertices = num_edges = 0;
} 

void Brain::add_edge(Vertex u, Vertex v, Weight w) 
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


void Brain:: remove_edge(Vertex u, Vertex v)
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

void input_Brain(Brain &g, unsigned int num_edges, Vertex *vertex_list) 
{
	Vertex u{0, 0, 0, inf};
	Vertex v{0, 0, 0, inf};

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

void display_graph(Brain &g)
{
	Vertex v{0, 0, 0, inf};

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
        void Dijkstra_process(Vertex *, unsigned int, MinPQueue<Vertex> &, Brain &);
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

void Dijkstra::Dijkstra_process(Vertex *vertex_list, unsigned int origin_s, MinPQueue<Vertex> &Q, Brain &g)
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

////////////////////////////////////////////////////////////////////////
// NeuronBlock:

class NeuronBlock
{
    private:
        unsigned int num_vertices_nb;
        unsigned int num_edges_nb;
        list<VertexWeightPair> *adj_nb;

    public:
        NeuronBlock(unsigned int);
        ~NeuronBlock();

        void add_edge_nb(Vertex, Vertex, Weight);
		void remove_edge_nb(Vertex, Vertex);

        list<VertexWeightPair> get_adj_nb(Vertex v){return adj_nb[v.vertex];}

        unsigned int get_num_vertices_nb() { return num_vertices_nb; }
        unsigned int get_num_edges_nb() { return num_edges_nb; }
};

NeuronBlock::NeuronBlock(unsigned int num_vertices_nb): num_vertices_nb(num_vertices_nb)
{
	adj_nb = new list<VertexWeightPair>[num_vertices_nb + 1];
    num_vertices_nb = 0;
    num_edges_nb = 0;
}

NeuronBlock::~NeuronBlock() 
{
	for (unsigned int u = 1; u <= num_vertices_nb; ++u) 
    {
		adj_nb[u].clear();
	}

	delete[] adj_nb;

	adj_nb = nullptr;
	num_vertices_nb = num_edges_nb = 0;
} 

void NeuronBlock::add_edge_nb(Vertex u, Vertex v, Weight w) 
{
	bool is_duplicated = false;

	list<VertexWeightPair>::iterator it;

	for(it = adj_nb[u.vertex].begin(); it != adj_nb[u.vertex].end(); it++)
	{
		if(it->vertex.vertex == v.vertex){
			is_duplicated = true;
		}
	}

    for(it = adj_nb[v.vertex].begin(); it != adj_nb[v.vertex].end(); it++)
	{
		if(it->vertex.vertex == u.vertex){
			is_duplicated = true;
		}
	}

	if(!is_duplicated)
	{
		VertexWeightPair item_v{v, w};
        VertexWeightPair item_u{u, w};

		adj_nb[u.vertex].push_back(item_v);	
        adj_nb[v.vertex].push_back(item_u);
		
		num_edges_nb++;
	}
}


void NeuronBlock:: remove_edge_nb(Vertex u, Vertex v)
{
	list<VertexWeightPair>::iterator it_u = adj_nb[u.vertex].begin();
    list<VertexWeightPair>::iterator it_v = adj_nb[v.vertex].begin();

	for(; it_u != adj_nb[u.vertex].end(); it_u++)
	{
		if(it_u->vertex.vertex == v.vertex)
		{
			adj_nb[u.vertex].erase(it_u);	

			break;		
		}
	}

    for(; it_v != adj_nb[v.vertex].end(); it_v++)
	{
		if(it_v->vertex.vertex == u.vertex)
		{
			adj_nb[v.vertex].erase(it_v);

			break;		
		}
	}

    num_edges_nb --;
}

void input_NeuronBlock(NeuronBlock &g, unsigned int num_edges, pair<pair<int,int>,float> *graph)
{
	Vertex u{0, 0, 0, inf};
	Vertex v{0, 0, 0, inf};

	Weight w;

	for (int p = 1; p <= num_edges; p++)
    {
		cin >> u.vertex >> v.vertex >> w;

        pair<pair<int,int>,float> weightedEdge;
        weightedEdge.first.first = u.vertex;
        weightedEdge.first.second = v.vertex;
        weightedEdge.second = w;
        graph[p] = weightedEdge;

		g.add_edge_nb(u, v, w); 
	}
}

void display_list_nb(list<VertexWeightPair> &lst)
{
    for(VertexWeightPair item_vertex: lst)
    {
        cout << "(" << item_vertex.vertex.vertex << ", " << item_vertex.weight << "), ";

		// if (item_vertex.vertex.vertex == 1)
		// 	cout << "vertice 1.pi: " << item_vertex.vertex.pi << " ; vertice 1.distance: " << item_vertex.vertex.distance << endl; 
    }
    cout << endl;
}

void display_graph_nb(NeuronBlock &g)
{
	Vertex v{0, 0, 0, inf};

    for(; v.vertex <= g.get_num_vertices_nb(); v.vertex++)
    {
        cout<< "v[" << v.vertex << "]: ";
        list<VertexWeightPair> lst = g.get_adj_nb(v);
        display_list_nb(lst);
    }
}


////////////////////////////////////////////////////////////////////////
// Kruskal:

class Kruskal
{
    private:
        int *parent_set;

    public:
        Kruskal(unsigned int);
        ~Kruskal();

        void makeSet(int);
        int findSet(int);
        void unionSet(int, int);
        void bubbleSort(NeuronBlock &, pair<pair<int,int>,float> *);
        void Kruskal_process(float *, NeuronBlock &, pair<pair<int,int>,float> *, pair<pair<int,int>,float> *);
};

Kruskal::Kruskal(unsigned int num_vertices_nb)
{
    parent_set = new int[num_vertices_nb + 1];
}

Kruskal::~Kruskal()
{
    delete[] parent_set;
}

void Kruskal::makeSet(int n)
{
    parent_set[n] = n;
}

int Kruskal::findSet(int i)
{
    if(i == parent_set[i])
        return i;
    else
        return findSet(parent_set[i]);
}

void Kruskal::unionSet(int u, int v)
{
    int u_rep = this->findSet(u);
    int v_rep = this->findSet(v);

    this->parent_set[u_rep] = v_rep;
    cout << "parent_set[u]: " << parent_set[u] << endl;
}

void Kruskal::bubbleSort(NeuronBlock &nb, pair<pair<int,int>,float> *graph)
{
    int n = nb.get_num_edges_nb() + 1;

    cout << "Passou n: " << n << endl;
    
    for (int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= (n - i - 1); j++)
        {
            cout << "BUBBLE graph[j].second = "<< graph[j].second << endl;
            if (graph[j].second > graph[j + 1].second)
            {
                pair<pair<int,int>,float> aux = graph[j];
                graph[j] = graph[j + 1];
                graph[j + 1] = aux;
            }
        }
    }
}

void Kruskal::Kruskal_process(float *soma, NeuronBlock &nb, pair<pair<int,int>,float> *graph, pair<pair<int,int>,float> *mst)
{
    for (int o = 1; o <= nb.get_num_vertices_nb(); o++)
        makeSet(o);
    
    bubbleSort(nb, graph);

    for (int i = 1; i <= nb.get_num_edges_nb(); i++)
    {
        cout << graph[i].second << ", ";
    }

    for (int i = 1; i <= nb.get_num_edges_nb(); i++)
    {
        cout << "findSet(graph[i].first.first): " << findSet(graph[i].first.first) << ", findSet(graph[i].first.second)" << findSet(graph[i].first.second) << endl;
        if (findSet(graph[i].first.first) != findSet(graph[i].first.second))
        {
            cout << "FIND graph[i].second = " << graph[i].second << endl;
            mst[i] = graph[i];
            *soma += graph[i].second;
            unionSet(graph[i].first.first, graph[i].first.second);
        }
    }
}

////////////////////////////////////////////////////////////////////////
// Main:

int main() 
{
	unsigned int num_vertices = 0;
	unsigned int num_edges = 0;
	unsigned int origin_s = 0;
	unsigned int end = 0;

	cin >> num_vertices >> num_edges;

	Vertex vertex_list[num_vertices + 1];

	cout << "num_vertices: " << num_vertices << endl;
	cout << "num_edges: " << num_edges << endl;

    Brain g{num_vertices};

	input_Brain(g, num_edges, vertex_list);

    display_graph(g);

	Dijkstra dikstra;

    cout << "Origin/End:" << endl;

	cin >> origin_s >> end;

    MinPQueue<Vertex> Q{num_vertices};

	dikstra.Dijkstra_process(vertex_list, origin_s, Q, g);

	// cout << "Start in Vertex: " << origin_s << ", with distance = " << vertex_list[origin_s].distance << endl;
	// cout << "Example of non-start Vertex: 2" << ", with distance = " << vertex_list[2].distance << endl;

    cout << "Path from end (" << end << ") to start: (" << origin_s << "), with Minimum Weight = " << vertex_list[end].distance << " ; " << endl;

    vertex_list[origin_s].id = 1;

    while (end != origin_s)
    {
        vertex_list[end].id = 1;
        // cout << "Vertex.vertex: " << vertex_list[end].vertex << ", Vertex.pi: " << vertex_list[end].pi << ", Vertex.distance: " << vertex_list[end].distance << endl;
        cout << " -> " << vertex_list[end].pi;

        end = vertex_list[end].pi;
    }

    g.~Brain();

    // NeuronBlocks:

    float soma = 0;
    bool is_sick;

    for (int i = 1; i <= num_vertices; i++)
    {
        cout << "Bloco " << i << ": ";

        unsigned int num_vertices_block, num_edges_block;
        int num_sicks, getsick;

        cin >> num_vertices_block >> num_edges_block;

        cout << endl << "Numero de doentes: ";

        cin >> num_sicks;

        if (num_sicks != 0)
            is_sick = true;

        for(int o = 0; o < num_sicks; o++)
            cin >> getsick;


        NeuronBlock nb{num_vertices_block};

        pair<pair<int,int>,float> graph[num_edges_block + 1];

	    input_NeuronBlock(nb, num_edges_block, graph);

        for (int i = 1; i <= nb.get_num_edges_nb(); i++)
        {
            cout << graph[i].second << ", ";
        }

        display_graph_nb(nb);

        cout << "vertex_list[i].id = " << vertex_list[i].id << ", is_sick = " << is_sick << ", i = " << i << endl;

        if((vertex_list[i].id == 1) && (is_sick))
        {
            cout << endl << "Kruskal: " << endl;

            Kruskal kruskal{num_vertices_block};

            pair<pair<int,int>,float> mst[num_edges_block + 1];

            kruskal.Kruskal_process(&soma, nb, graph, mst);

            cout << endl;
        }

        is_sick = false;
    }

    cout << endl << "Soma: " << soma;

	return 0;
}