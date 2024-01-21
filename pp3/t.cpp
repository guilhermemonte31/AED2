
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;

class Block{
    private://          v1 v2 peso
        vector<pair<pair<int,int>,float>> graph;
        vector<pair<pair<int,int>,float>> mst;
        unsigned int numVertices;
        unsigned int numEdges;
        int *parent;
        unsigned int id;
    public:
        Block(unsigned int,unsigned  int);
        ~Block();
        void addEdge(int, int, float);
        void makeSet(int);
        int findSet(int);
        void unionSet(int, int);
        void kruskal(float *);
        void print();
        void bubbleSort(vector<pair<pair<int,int>,float>>);
        void setID(int id);
        int getID(){return id;}
        unsigned int get_num_edges(){return numVertices;}
        void set_num_vertices(unsigned int v);
};


void Block::setID(int num_id){
    id = num_id;
}

void Block:: set_num_vertices(unsigned int n){
    numVertices = n;
}

Block::Block(unsigned  int _num_vertices, unsigned int num_id):numVertices(_num_vertices), id(num_id){
    parent = new int[numVertices];
}

Block::~Block(){
    graph.clear();
    mst.clear();

}

void Block::addEdge(int u, int v, float weight){
    pair<pair<int,int>,float> weightedEdge;
    weightedEdge.first.first = u;
    weightedEdge.first.second = v;
    weightedEdge.second = weight;
    graph.push_back(weightedEdge);
    numEdges++;
}

void Block::makeSet(int n){
    parent[n] = n;
}

int Block::findSet(int i){
    if(i == parent[i]){
        return i;
    }else{
        return findSet(parent[i]);
    }
}

void Block:: unionSet(int u, int v){
    parent[u] = parent[v];
}


void Block:: bubbleSort(vector<pair<pair<int,int>,float>> graph){
    pair<pair<int,int>,float> temp;
    int n = graph.size();

    for(int i=0; i<n; i++){
        for(int j=0; j< (n-i-1); j++){
            if(graph[j].second > graph[j+1].second){
                swap(graph[j], graph[j+1]);
            }
        }
    }
    
}


void Block::kruskal(float *soma){
    for(int o=0; o<numVertices; o++){
        makeSet(o);
    }
    bubbleSort(graph);
    for(int i=0; i<graph.size(); i++){
        if(findSet(graph[i].first.first) != findSet(graph[i].first.second)){
            mst.push_back(graph[i]);
            *soma += graph[i].second;
            unionSet(graph[i].first.first, graph[i].first.second);
        }
    }
    

}

void Block::print(){
    for (int i = 0; i < mst.size(); i++) {
        cout << mst[i].first.first << " " << mst[i].first.second << " "<< mst[i].second<<endl;
    }
}

void inputBlock(Block &g,int num_edges){
    g.set_num_vertices(num_edges);
    cout<<"teste "<<num_edges<<" teste2 "<<g.get_num_edges()<<endl;
    int u=0, v=0;
    float w=0;
    for(int i=0; i<num_edges; i++){
        cin>>u>>v>>w;
        g.addEdge(u, v, w);
    }
}


// O CEREBRO

class BlockWeightPair{
    public:
        Block block;
        float weight;
        BlockWeightPair(Block block, float weight): weight(weight), block(block){}
};

class Brain{
    private:
        unsigned int num_vertices;
        unsigned int num_edges;
        list<BlockWeightPair> *adj;
        vector<Block> block_vector;
    public:
        Brain(unsigned  int);
        void add_edge(Block, Block, float);
        unsigned int get_num_edges(){return num_edges;}
        unsigned int get_num_vertices(){return num_vertices;}
        vector<Block> get_vector_block(){return block_vector;}
        void insert_block_vector(Block);
};

Brain::Brain( unsigned int _num_vertices): num_vertices(_num_vertices){
    adj = new list<BlockWeightPair>[num_vertices];
    
}

void Brain::add_edge(Block b1, Block b2, float w){
	bool is_duplicated = false;

	BlockWeightPair item_b2{b2, w};
    adj[b1.getID()].push_back(item_b2);
	
}
void Brain:: insert_block_vector(Block block){
    bool is_in_vec = false;
    for(int i=0; i<block_vector.size(); i++){
        if(block.getID() == block_vector[i].getID()){
            is_in_vec = true;
        }
    }
    if(is_in_vec == false){
        block_vector.push_back(block);
        
    }
}


void input_brain(Brain &brain, int num_edges){

    Block b1{0, NULL};
    Block b2{0, NULL};
    float w=0;
    int IDbloco1, IDbloco2;
    for(int i=0; i<num_edges; i++){
        cin>>IDbloco1>>IDbloco2>>w;
        b1.setID(IDbloco1);
        b2.setID(IDbloco2);
        brain.insert_block_vector( b1);
        brain.insert_block_vector(b2);
        brain.add_edge(b1,b2,w);
    }
}



// O MAIN
int main() {
    float soma=0;
    // int num_vertices=0, num_edges=0, sicks=0;
    // cin>>num_vertices>>num_edges;
    // // cin>>sicks;
    // cout<<"Num_vertices: "<< num_vertices<< endl<<"Num_edges: "<<num_edges<<endl;
    // Block g{num_vertices, NULL};
    // inputBlock(g, num_edges);
    // g.kruskal(&soma);
    // g.print();
    // cout<<"Soma: "<<soma<<endl;

    cout<<"BRAIN"<<endl;
    unsigned int num_vertices_brain=0, num_edges_brain=0;
    cin>>num_vertices_brain>>num_edges_brain;
    cout<<"Num_vertices: "<< num_vertices_brain<< endl<<"Num_edges: "<<num_edges_brain<<endl;
    Brain brain{num_vertices_brain};
    input_brain(brain, num_edges_brain);

    int begin, end;
    cin>>begin>>end;
    cout<<"Inicio: "<<begin<<" End: "<<end<<endl;

    for(unsigned int i=0; i<num_vertices_brain; i++){
        unsigned int num_vertices_block, num_edges_block;
        int sicks;
        cin>>num_vertices_block>>num_edges_block;
        cin>>sicks;
        //pegar as arestas do bloco i

        inputBlock(brain.get_vector_block()[i], num_edges_block);
        cout<<"vertices "<<brain.get_vector_block()[i].get_num_edges()<<" "<<brain.get_vector_block()[i].getID()<<endl;
        
    }
    cout<<"Soma: "<<soma;
}