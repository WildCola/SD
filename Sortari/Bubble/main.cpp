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
    if(n>100000)
        return 0;
    return 1;
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

        g<<"Test "<<i<<":\n";
        cout<<"Test "<<i<<":\n";

        vector<int> v;

        if(eficient(n))
        {
            nmax = sqrt(nmax);
            for(int i=1; i<=n; ++i)
            {
                int x,y;
                x = (rand() % nmax) + 1;
                y = (rand() % nmax) + 1;
                v.push_back(x*y);
            }

            clock_t start;
            start = clock();
            float durata;

            for(int i=0; i<n-1; ++i)
                for(int j=0; j<n-1-i; ++j)
                    if(v[j] > v[j+1])
                        swap(v[j], v[j+1]);

            durata = (clock() - start) / (float)CLOCKS_PER_SEC;

            if(test_sort(v))
            {
                cout<<"Bubble sort: Sortat Corect, Timp de sortare: "<<durata<<" secunde\n\n";
                g<<"Bubble sort: Sortat Corect, Timp de sortare: "<<durata<<" secunde\n";
                for(int i=0; i<n; ++i)
                    g<<v[i]<<" ";
            }
            else
                cout<<"Bubble sort: Sortat Incorect";
            g<<"\n\n";

        }

        else
        {
            g<<"Algoritmul nu este destul de eficient pentru a sorta un sir de numere de aceasta lungime\n\n";
            cout<<"Algoritmul nu este destul de eficient pentru a sorta un sir de numere de aceasta lungime\n\n";
        }

    }

    f.close();
    g.close();
    return 0;
}
