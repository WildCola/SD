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
    if(n>100000000)
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

            for(int x=1; nmax/x>0; x*=10)
            {
                vector<int> c; //vector count
                for(int i=1; i<=n; ++i)
                    c.push_back(0);

                int cifre[10] = {0}; //contor aparitii cifre

                for(int i=0; i<n; ++i)
                    cifre[(v[i]/x) % 10]++; //contorizez aparitia fiecarei cifre de pe pozitia x (x=1 unitati, x=10 zeci etc)
                for(int i=1; i<10; ++i)
                    cifre[i] += cifre[i-1]; //transform array-ul de cifre pentru a arata pozitia pe care asez numerele in vectorul count (ex: daca pe pozitia 4 din array este valoarea 3 si x = 1 atunci numerul cu cifra unitatilor 4 va fi pus pe pozitia 3, adica c[2])
                for(int i=n-1; i>=0; --i)
                {
                    c[cifre[(v[i]/x)%10] - 1] = v[i];
                    cifre[(v[i]/x)%10]--; //mut pozitia pe care pun numerele ce contin aceeasi cifra pe aceeasi pozitie pentru a nu se suprapune
                }
                for(int i=0; i<n; ++i)
                    v[i]=c[i]; //copiez vectorul sortat in cel initial
            }

            durata = (clock() - start) / (float)CLOCKS_PER_SEC;

            if(test_sort(v))
            {
                cout<<"Radix sort: Sortat Corect, Timp de sortare: "<<durata<<" secunde\n\n";
                g<<"Radix sort: Sortat Corect, Timp de sortare: "<<durata<<" secunde\n";
                for(int i=0; i<n; ++i)
                    g<<v[i]<<" ";
            }
            else
                cout<<"Radix sort: Sortat Incorect\n\n";
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
