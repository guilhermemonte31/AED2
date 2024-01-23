
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;



class Block{
    private://          v1 v2 peso
        vector<pair<pair<int,int>,float>> graph;
        vector<pair<pair<int,int>,float>> mst;
        int num_vertices_block;
        int num_edges_block;
        int *parent;
        int id_block;
        list<pair<int, float>> *adj;
    public:
        Block( int,  int);
        ~Block();
        void add_edge_block(int, int, float);
        void add_to_adj(int, int, float);

        void makeSet(int);
        int findSet(int);
        void unionSet(int, int);
        void kruskal(float *);
        void bubbleSort(vector<pair<pair<int,int>,float>>);

        void setID_block(int id);
        int getID_block(){return id_block;}
        void set_num_edges_block(int e);
        int get_num_edges_block(){return num_edges_block;}
        void set_num_vertices_block( int v);
        int get_num_vertices_block(){return num_vertices_block;}
        
        

        void print();
        void print_adjs();
};


void Block::setID_block(int num_id){
    id_block = num_id;
}

void Block:: set_num_vertices_block( int n){
    num_vertices_block = n;
}
void Block:: set_num_edges_block( int n){
    num_edges_block = n;
}


Block::Block(  int _num_vertices,  int num_id):num_vertices_block(_num_vertices), id_block(num_id){
    parent = new int[num_vertices_block];
    num_edges_block=0;
    adj = new list<pair<int, float>> [num_vertices_block];
}

Block::~Block(){
    graph.clear();
    mst.clear();

}

void Block::add_edge_block(int u, int v, float weight){
    cout<<"teste6"<<endl;
    pair<pair<int,int>,float> weightedEdge;
    weightedEdge.first.first = u;
    weightedEdge.first.second = v;
    weightedEdge.second = weight;
    graph.push_back(weightedEdge);
    cout<<"teste7"<<endl;
    add_to_adj(u, v, weight);
    //num_edges_block++;

}

void Block:: add_to_adj(int u, int v, float w){
    cout<<"teste8"<<endl;
    pair<int, float> item_u;
    item_u.first = u;
    item_u.second = w;

    pair<int, float> item_v;
    item_v.first = v;
    item_v.second = w;
    cout<<"teste10"<<endl;

    bool is_duplicated = false;
    cout<<"testando adjs "<< adj[u].size()<<" "<<adj[v].size()<<endl;
    for(list<pair<int, float>>::iterator it = adj[u].begin(); it != adj[u].end(); ++it){
        if(it->first == v){
            is_duplicated = true;
        }
    }
    cout<<"teste11"<<endl;
    for(list<pair<int, float>>::iterator it = adj[v].begin(); it != adj[v].end(); ++it){
        if(it->first == u){
            is_duplicated = true;
        }
    }
    cout<<"teste12"<<endl;
    if(!is_duplicated){
        adj[u].push_back(item_v);
        adj[v].push_back(item_u);
        num_edges_block++;
    }
    adj[u].push_back(item_v);
    adj[v].push_back(item_u);
    num_edges_block++;
    cout<<"teste9"<<endl;

}
void Block:: print_adjs(){
    for(int i=0; i<num_vertices_block; i++){
        cout<<i<<": ";
        for(pair<int, float> t: adj[i]){
            cout<<"("<<t.first<<", "<<t.second<<"), ";
        }
        cout<<endl;
    }
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
    for(int o=0; o<num_vertices_block; o++){
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
    cout<<"teste3"<<endl;
    g.set_num_edges_block(num_edges);
    cout<<"teste4"<<endl;
    int u=0, v=0;
    float w=0;
    for(int i=0; i<num_edges; i++){
        cin>>u>>v>>w;
        g.add_edge_block(u-1, v-1, w);
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
         int num_vertices_brain;
         int num_edges_brain;
        list<BlockWeightPair> *adj_brain;
        vector<Block> block_vector;
    public:
        Brain(int);
        ~Brain();
        void add_edge_brain(Block, Block, float);
        void insert_block_vector(Block);

        vector<Block> get_block_vector(){return block_vector;}
        int get_num_edges_brain(){return num_edges_brain;}
        void set_num_edges_brain(int num_edges);
        void set_num_vertices_brain(int num_vertices);
        int get_num_vertices_brain(){return num_vertices_brain;}
};

Brain::Brain(int num_vertices):num_vertices_brain(num_vertices){
    adj_brain = new list<BlockWeightPair>[num_vertices_brain];
    num_edges_brain =0;

}

Brain:: ~Brain(){
    for(int i=0; i<num_vertices_brain; i++){
        adj_brain[i].clear();
    }
    delete[] adj_brain;
    block_vector.clear();
}

void Brain:: add_edge_brain(Block b1, Block b2, float weight){
    BlockWeightPair item_b2{b2, weight};
    BlockWeightPair item_b1{b1, weight};
    
    adj_brain[b1.getID_block()].push_back(item_b2);
    adj_brain[b2.getID_block()].push_back(item_b1);
    num_edges_brain++;

}

void Brain::insert_block_vector(Block block){
    bool is_in_vector = false;
    for(int i=0; i<block_vector.size(); i++){
        if(block.getID_block() == block_vector[i].getID_block()){
            is_in_vector = true;
        }
    }
    if(is_in_vector == false){
        block_vector.push_back(block);
        
    }
}

void input_brain(Brain &brain, int num_edges_brain){
    Block b1{0, -1}; //quant de vertices e o id
    Block b2{0, -1};
    float weight;
    int id_b1, id_b2;
    for(int i=0; i<num_edges_brain; i++){
        cin>>id_b1>>id_b2>>weight;
        b1.setID_block(id_b1-1);
        b2.setID_block(id_b2-1);
        brain.add_edge_brain(b1,b2,weight);

        brain.insert_block_vector(b1);
        brain.insert_block_vector(b2);
        // cout<<endl<<"Id do bloco b1 depois: "<<b1.getID_block()<<endl;
    }
    
}

void display_list(vector<Block> &vec){
    for(Block item: vec){
        cout<<"("<<item.getID_block()<<"), ";
    }
    cout<<endl;
}

void display(Brain &brain){
    cout<<"Display"<<endl<<"teste"<<brain.get_num_edges_brain();
    for(int i=0; i<brain.get_num_edges_brain(); i++){
        cout<<i<<": ";
        vector<Block> vect = brain.get_block_vector();
        display_list(vect);
    }
}


// O MAIN
int main() {
    float soma=0;


    cout<<"BRAIN"<<endl;
    int num_vertices_brain, num_edges_brain;
    cin>>num_vertices_brain>>num_edges_brain;
    cout<<"Num_vertices: "<< num_vertices_brain<< endl<<"Num_edges: "<<num_edges_brain<<endl;
    Brain brain{num_vertices_brain};
    input_brain(brain, num_edges_brain);


    vector<Block> teste = brain.get_block_vector();
    vector<int> issick;



    for(int i=0; i<teste.size(); i++){
        cout<<"Bloco "<<i<<": ";
        int vertices_block, edges_block, num_sicks;
        cin>>vertices_block>>edges_block;
        cout<<endl<<"Numero de doentes: ";
        cin>>num_sicks;
        int getsick;
        for(int o=0; o<num_sicks; o++){
            cin>>getsick;
        }
        issick.push_back(num_sicks);
        teste[i].set_num_vertices_block(vertices_block);
        cout<<"teste1"<<endl;
        inputBlock(teste[i], edges_block);
        cout<<"teste2"<<endl;
        
    }

    for(int i=0; i<teste.size(); i++){
        if(issick[i] != 0){
            cout<<endl<<"Kruskal: "<<endl;
            teste[i].kruskal(&soma);
            teste[i].print();
            cout<<endl;
        }

    }
    cout<<endl<<"Soma: "<<soma;


}