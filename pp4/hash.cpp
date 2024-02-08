#include <iostream>
#include <list>
#include <vector>
#include <math.h>

using namespace std;

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
    if(code == "~~~"){
        return 0;
    }

    char get_letter = search_letter(code);
    int i;
    for(i=0;i<28; i++){
        if(get_letter == letters_vector[i]){
            break;
        }
    }
    return (27-i);
}



int main(){

    //creating hash table
    unsigned int hash_table_size = 7;
    HashTable ht{hash_table_size};

    string et_phrase;
    cin>>et_phrase;

    string last_code;
    int et_phrase_size = et_phrase.size();
    last_code += et_phrase[et_phrase_size-3];
    last_code += et_phrase[et_phrase_size-2];
    last_code += et_phrase[et_phrase_size-1];
    cout<<last_code;
    int k = ht.get_k_value(last_code);
    cout<<"valor de k sera: "<<k;




    // //catching words to search in et_phrase
    // string word;
    // vector<string> words_vector;

    // while(word != "fim"){
    //     cin>>word;
    //     if(word == "fim"){
    //         break;
    //     }
    //     words_vector.push_back(word);
    // }

    // vector<string>::iterator it;
    // for(it =words_vector.begin(); it != words_vector.end(); it++){
    //     //calls boyer  moore for each inserted word
    // }


}
