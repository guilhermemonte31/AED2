#include <iostream>
#include <stdlib.h>
#include <vector>
#include <list>
#include <iomanip>
#include <string>

using namespace std;
int main(){
    string pos = "a1";
    char linha = pos[0];
    int coluna = pos[1] - 48;
    pair<char, char> inicio(linha, coluna);
    vector<pair<char, int>> movimentos = {{char(linha-2), (coluna-1)}, {char(linha-2), (coluna+1)}, {char(linha-1), (coluna+2)}, {char(linha-1), (coluna-2)}, {char(linha+1), (coluna+2)}, {char(linha+1), (coluna-2)}, {char(linha+2), (coluna+1)}, {char(linha+2), (coluna-1)}};

    for(int i=0; i<8; i++){
        if(movimentos[i].first >= 'a' && movimentos[i].first<='h'&& movimentos[i].second>=1 && movimentos[i].second<=8){
           cout<<movimentos[i].first<<movimentos[i].second;
            cout<<endl;
        }  
        
    }




    
}
