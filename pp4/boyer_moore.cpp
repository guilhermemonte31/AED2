#include <iostream>
#include <vector>
#include <list>

using namespace std;

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
        R[P[j] - 97] = j;
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
                salto = j - R[T[i + j] - 97];

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


int main()
{
    string T_out = "abcdefgopahijkopaopadefgh";
    string P_out = "defg";

    int R[29];

    BoyerMoore bm{T_out, P_out};

    bm.Computa_Tabela_Saltos(R);

    bm.BoyerMoore_process(R);

    return 0;
}