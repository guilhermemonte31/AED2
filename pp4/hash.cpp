#include <iostream>
#include <list>
#include <vector>
#include <math.h>

using namespace std;



////////////////////////////////////////////////////////////////// BOYER MOORE

class BoyerMoore
{
    private:
        string T;
        string P;
        int N;
        int M;
        int salto;

    public:
        BoyerMoore(string, string);
        void Computa_Tabela_Saltos(int *);
        void BoyerMoore_process(int *);
};

BoyerMoore::BoyerMoore(string T_out, string P_out)
{
    T = T_out;
    P = P_out;
    N = T.size();
    M = P.size();
    salto = 0;
}

void BoyerMoore::Computa_Tabela_Saltos(int *R)
{
    for (int i = 0; i < 29; i++)
        R[i] = -1;

    for (int j = 0; j < M; j++)
        R[P[j] - 65] = j;
}

void BoyerMoore::BoyerMoore_process(int *R)
{
    for (int i = 0; i <= N - M; i += salto)
    {
        salto = 0;

        int j = M - 1;

        for (; j >= 0; j--)
        {
            if (P[j] != T[i + j])
            {
                salto = j - R[T[i + j] - 65];
                cout<<salto;
                if (salto < 1)
                    salto = 1;
                
                break;
            }
        }

        if (salto == 0)
        {
            cout << "O padrao se encontra na posicao [" << i << "]" << endl;
            salto = 1;
        }
    }
}




////////////////////////////////////////////////////////////////// HASH TABLE
class HashTable{
    private:
        unsigned int table_size;
        list<pair<char, string>> *table;
        char *letters_vector;
    public:
        HashTable(unsigned int);
        ~HashTable();
        int perfect_hash(string);
        void insert_value(char, string);
        char search_letter(string);
        void show();
        int get_k_value(string);
        string get_decodify(string, int);

};

HashTable::HashTable(unsigned int n){
    table_size = n;
    table = new list<pair<char, string>>[table_size];
    

    insert_value('A', ":::");
    insert_value('B', ".::");
    insert_value('C', ":.:");
    insert_value('D', "::.");
    insert_value('E', ":..");
    insert_value('F', ".:.");
    insert_value('G', "..:");
    insert_value('H', "...");
    insert_value('I', "|::");
    insert_value('J', ":|:");
    insert_value('K', "::|");
    insert_value('L', "|.:");
    insert_value('M', ".|:");
    insert_value('N', ".:|");
    insert_value('O', "|:.");
    insert_value('P', ":|.");
    insert_value('Q', ":.|");
    insert_value('R', "|..");
    insert_value('S', ".|.");
    insert_value('T', "..|");
    insert_value('U', ".||");
    insert_value('V', "|.|");
    insert_value('W', "||.");
    insert_value('X', "-.-");
    insert_value('Y', ".--");
    insert_value('Z', "--.");
    insert_value(' ', "---");
    insert_value('.', "~~~");

    char letter = 'A';
    letters_vector = new char[28];
    for(int i=0; i<26; i++){
        letters_vector[i] = letter;
        letter++;
    }
    letters_vector[26] = ' ';
    letters_vector[27] = '.';
    
}

HashTable::~HashTable(){
    for(unsigned int i=0; i<table_size; i++){
        table[i].clear();
    }
    delete[] table;
    table= nullptr;
    table_size=0;
}

int HashTable::perfect_hash(string key){
    int TAM_ASCII = 256;
    int M = 7; // tamanho da tabela
    int hash = 0;
    for (int i = 0; i < key.length(); i++) {
        hash += static_cast<int>(key[i])*(int)pow(TAM_ASCII, key.length() - i - 1) % M;
    }
    return hash % M;

}

void HashTable::insert_value(char letter, string code){
    int id = perfect_hash(code);
    pair <char, string> test;
    test.first = letter;
    test.second = code;
    table[id].push_back(test);

}

void HashTable::show(){
    for(int i=0; i<7; i++){
        cout<<endl<<"lista "<<i<<endl;
        for(pair<char, string> element: table[i]){
            cout<<"("<<element.first<<", "<<element.second<<")"<< "; ";
        }
        cout<<endl;
    }
}

char HashTable::search_letter(string code){
    int id = perfect_hash(code);
    for(auto it = table[id].begin(); it != table[id].end(); it++){
        if((*it).second == code){
            return (*it).first;
            
        }
    }

}

int HashTable::get_k_value(string code){
    int k=0;
    string message;
    message += code[0];
    message += code[1];
    message += code[2];
    message += code[3];
    message += code[4];
    message += code[5];
    message += code[6];
    message += code[7];
    
    string example = "MENSAGEM";
    if(example == message){
        return k; 
    }
    else{
        while(message[0] != 'M'){
            k -=1;
            message[0]+=k;
        }
        return k;
    }


}

string makes_upper(string word){
    string upper;
    for(int i=0; i<word.size(); i++){
        upper += word[i]-32;
    }
    return upper;
}

string HashTable:: get_decodify(string codify, int k){
    string decodify;
    for(int i=0; i<codify.size(); i++){
        decodify += (codify[i]+k);
    }
    return decodify;
}

int main(){

    //creating hash table
    unsigned int hash_table_size = 7;
    HashTable ht{hash_table_size};

    //getting the coded phrase
    string et_phrase;
    cin>>et_phrase;


    string character, codify;

    for(int i=0; i<et_phrase.size(); i+=3){
        character += et_phrase[i];
        character += et_phrase[i+1];
        character += et_phrase[i+2];
        codify += ht.search_letter(character);
        character = "";
    }

    cout<<"Codify: "<<codify<<endl;


    //getting value of k
    int k = ht.get_k_value(codify);
    cout<<"valor de k sera: "<<k;

    string last = ht.get_decodify(codify, k);
    cout<<endl<<"Mensagem final: "<<last<<endl;

 


    // //catching words to search in et_phrase
    // string word;
    // vector<string> words_vector;
    // string word_upper;

    // while(word != "fim"){
    //     cin>>word;
    //     if(word == "fim"){
    //         break;
    //     }
    //     word_upper = makes_upper(word);
    //     cout<<word_upper;
    //     words_vector.push_back(word);
    // }



    // int R[29];


    // //searching for words in the phrase
    // vector<string>::iterator it;
    // for(it =words_vector.begin(); it != words_vector.end(); it++){
    //     //calls boyer  moore for each inserted word
    // }

}
