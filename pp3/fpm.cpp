#include<iostream>
#include<vector>

using namespace std;

template <typename T>
class MinPQueue
{
    private:
        unsigned int tam;
        unsigned int tam_heap;
        int *S;

    public:
        MinPQueue(unsigned int);
        ~MinPQueue();

        void Insert(int, int);
        int Minimum() {return S[0]; }
        int Extract_Min();
        // void Increase_Min(int, int);

        int Parent(int);
        int Left(int);
        int Right(int);

        void Min_HeapFy (int);
        void Build_Min_Heap ();
        
        int *get_S() { return S; }
        unsigned int get_tam() { return tam; }
        unsigned int get_tam_heap() { return tam_heap; }
};

template <typename T>
MinPQueue<T>::MinPQueue(unsigned int tam): tam(tam)
{
    S = new int[tam];
    tam_heap = 0;
}

template <typename T>
MinPQueue<T>::~MinPQueue()
{
    delete[] S;

    tam = tam_heap = 0;
}

template <typename T>
void MinPQueue<T>::Insert(int x, int i)
{
    S[i] = x;
    tam_heap++;
}

template <typename T>
int MinPQueue<T>::Extract_Min()
{
    int Min = S[1];

    for (int i = 2; i <= tam; i++)
    {
        S[i - 1] = S[i];
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

    cout << "left: " << l << " right: " << r << " tam_heap: " << tam_heap << endl;

    if ((l <= (tam_heap)) && (S[l] < S[i]))
        smallest = l;

    else smallest = i;

    if ((r <= (tam_heap)) && (S[r] < S[smallest]))
        smallest = r;
    
    if (smallest != i)
    {
        int aux = S[i];
        S[i] = S[smallest];
        S[smallest] = aux;

        cout << "=== S[i]: " << S[i] << " S[smallest]: " << S[smallest] << endl;

        Min_HeapFy(smallest);
    }
}

template <typename T>
void MinPQueue<T>::Build_Min_Heap()
{
    for (int i = tam_heap / 2; i > 0; i--)
    {
        cout << "i: " << i << " tam_heap: " << tam_heap << endl;
        Min_HeapFy(i);
    }
}

template <typename T>
void Display_list (MinPQueue<T> &Q)
{
    cout << "=== Vector: ===" << endl;

    int *lst = Q.get_S();
    int tam_lst = Q.get_tam_heap();

    cout << "Tam_lst: " << tam_lst << "lst[0]: "<< lst[0] << endl;
 
    for (int item = 1; item <= tam_lst; item++)
        cout << lst[item] << ", ";
    
    cout << endl;
}

int main()
{
    unsigned int tam = 0;
    int x, min;

    cin >> tam;

    cout << "tam: " << tam << endl;

    MinPQueue<int> Q{tam};

    for (int i = 1; i <= tam; i++)
    {
        cin >> x;
        Q.Insert(x, i);
        Display_list(Q);
    }

    Q.Build_Min_Heap();
    Display_list(Q);

    for (int i = 0; i < tam; i++)
    {
        min = Q.Extract_Min();

        cout << "Min Extracted: " << min << endl;

        Q.Build_Min_Heap();

        cout << "New Vector after extracted Min: " << endl;

        Display_list(Q);
    }

    // min = Q.Extract_Min();

    // cout << "Min Extracted: " << min << endl;

    // Q.Build_Min_Heap();

    // cout << "New Vector after extracted Min: " << endl;

    // Display_list(Q);

    return 0;
}
