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
    vector<pair<char, char>> movimentos = {{-2, -1}, {-2, 1}, {-1, 2}, {-1, -2}, {1, 2}, {1, -2}, {2, 1}, {2, -1}};

    for(int i=0; i<8; i++){
        char l = abs(linha - movimentos[i].first);
        int c = abs(coluna - movimentos[i].second);
        if(l>='a'||l<='h'||c>=1||c<=8){
            cout<<l<<c;
            cout<<endl;
        }
    }
    
}