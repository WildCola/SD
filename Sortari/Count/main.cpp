#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <math.h>
#include <ctime>


using namespace std;

int n, nmax, nrelem;

bool test_sort(vector<int> v)
{
    for(int i=1; i<nrelem; ++i)
        if(v[i]<v[i-1])
            return 0;
    return 1;
}

bool eficient(int n)
{
    if(n>100000000 || nmax>100000000)
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
        vector<int> c;

        if(eficient(n))
        {
            for(int i=0; i<=nmax; ++i)
                c.push_back(0);
            int aux = sqrt(nmax);
            for(int i=1; i<=n; ++i)
            {
                int x,y;
                x = (rand() % aux) + 1;
                y = (rand() % aux) + 1;
                c[x*y]++;
            }

            clock_t start;
            start = clock();
            float durata;

            nrelem = 0;
            for(int i=1; i<=nmax; ++i)
                if(c[i]>0)
                    for(int j=1; j<=c[i]; ++j)
                    {
                        v.push_back(i);
                        nrelem++;
                    }


            durata = (clock() - start) / (float)CLOCKS_PER_SEC;

            if(test_sort(v))
            {
                cout<<"Count sort: Sortat Corect, Timp de sortare: "<<durata<<" secunde\n\n";
                g<<"Count sort: Sortat Corect, Timp de sortare: "<<durata<<" secunde\n";
                for(int i=0; i<nrelem; ++i)
                    g<<v[i]<<" ";
            }
            else
                cout<<"Count sort: Sortat Incorect\n\n";
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
