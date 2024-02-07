#include <iostream>
#include <list>
#include <vector>
#include <math.h>

using namespace std;


class HashTable{
    private:
        unsigned int table_size;
        list<pair<char, string>> *table;
    public:
        HashTable(unsigned int);
        ~HashTable();
        int perfect_hash(string);
        void insert_value(char, string);
        void show();

};

HashTable::HashTable(unsigned int n){
    table_size = n;
    table = new list<pair<char, string>>[table_size];
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
    cout<<"teste "<<letter<<" "<<id<<endl;
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

void create_cryptography(HashTable *ht){


    ht->insert_value('A', ":::");
    ht->insert_value('B', ".::");
    ht->insert_value('C', ":.:");
    ht->insert_value('D', "::.");
    ht->insert_value('E', ":..");
    ht->insert_value('F', ".:.");
    ht->insert_value('G', "..:");
    ht->insert_value('H', "...");
    ht->insert_value('I', "|::");
    ht->insert_value('J', ":|:");
    ht->insert_value('K', "::|");
    ht->insert_value('L', "|.:");
    ht->insert_value('M', ".|:");
    ht->insert_value('N', ".:|");
    ht->insert_value('O', "|:.");
    ht->insert_value('P', ":|.");
    ht->insert_value('Q', ":.|");
    ht->insert_value('R', "|..");
    ht->insert_value('S', ".|.");
    ht->insert_value('T', "..|");
    ht->insert_value('U', ".||");
    ht->insert_value('V', "|.|");
    ht->insert_value('W', "||.");
    ht->insert_value('X', "-.-");
    ht->insert_value('Y', ".--");
    ht->insert_value('Z', "--.");
    ht->insert_value(' ', "---");
    ht->insert_value('.', "~~");
}


int main(){

    unsigned int hash_table_size = 7;
    HashTable ht{hash_table_size};
    create_cryptography(&ht);
    //ht.show();
}