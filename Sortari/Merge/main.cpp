#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <math.h>
#include <ctime>

using namespace std;

int n, nmax;

bool test_sort(vector<int> v)
{
    for(int i=1; i<n; ++i)
        if(v[i]<v[i-1])
            return 0;
    return 1;
}

bool eficient(int n)
{
    if(n>10000000)
        return 0;
    return 1;
}

void Merge(vector<int>& v, int m, int st, int dr)
{
    vector<int> vst, vdr;
    for(int i = 0; i <= m-st; ++i)
        vst.push_back(v[st+i]);

    for(int i = 0; i < dr-m; ++i)
        vdr.push_back(v[m+1+i]);

    int i=0, j=0, k=st;

    while(i <= m-st && j < dr-m)
    {
        if(vst[i] <= vdr[j])
        {
            v[k] = vst[i];
            ++i;
        }
        else
        {
            v[k] = vdr[j];
            ++j;
        }
        ++k;
    }

    while(i <= m-st)
    {
        v[k] = vst[i];
        ++k;
        ++i;
    }
    while(j < dr-m)
    {
        v[k] = vdr[j];
        ++k;
        ++j;
    }
}

void MergeSort(vector<int>& v, int st, int dr)
{
    if(st>=dr)
        return;

    int m = (dr+st)/2;

    MergeSort(v, st, m);
    MergeSort(v, m+1, dr);

    Merge(v, m, st, dr);
}

int main()
{
    ifstream f("../teste.in");
    ofstream g("../rezultate.out");

    int nrteste;
    f>>nrteste;

    for(int i = 1; i<=nrteste; ++i)
    {
        f>>n>>nmax;

        int aux = sqrt(nmax);

        g<<"Test "<<i<<":\n";
        cout<<"Test "<<i<<":\n";

        vector<int> v;

        if(eficient(n))
        {
            for(int i=1; i<=n; ++i)
            {
                int x,y;
                x = (rand() % aux) + 1;
                y = (rand() % aux) + 1;
                v.push_back(x*y);
            }

            clock_t start;
            start = clock();
            float durata;

            MergeSort(v, 0, n-1);

            durata = (clock() - start) / (float)CLOCKS_PER_SEC;

            if(test_sort(v))
            {
                cout<<"Merge sort: Sortat Corect, Timp de sortare: "<<durata<<" secunde\n\n";
                g<<"Merge sort: Sortat Corect, Timp de sortare: "<<durata<<" secunde\n";
                for(int i=0; i<n; ++i)
                    g<<v[i]<<" ";
            }
            else
                cout<<"Merge sort: Sortat Incorect\n\n";
            g<<"\n\n";

        }

        else
        {
            g<<"Algoritmul nu este destul de eficient pentru a sorta un sir de numere de aceasta lungime\n\n";
            cout<<"Algoritmul nu este destul de eficient pentru a sorta un sir de numere de aceasta lungime\n\n";
        }

    }
    return 0;
}
