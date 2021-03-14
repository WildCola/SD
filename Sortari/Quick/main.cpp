#include<bits/stdc++.h>

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





int pivot(int st, int dr, int m, int st1, int dr1)
{
    int a[5];
    a[0]=st;
    a[1]=dr;
    a[2]=m;
    a[3]=st1;
    a[4]=dr1;
    sort(a, a+4);
    return a[3];

}

void quick(vector<int>& v, int st, int dr)
{
    int s=st, d=dr;
    int piv=pivot(v[st],v[dr],v[(st+dr)/2+1],v[st+1], v[dr-1]);
    while(s<=d)
    {
        while(v[s]<piv)
            ++s;
        while(v[d]>piv)
            --d;
        if(s<=d)
        {
            swap(v[s],v[d]);
            ++s;
            --d;
        }
    }
    if(st<d)
        quick(v,st,d);
    if(s<dr)
        quick(v,s,dr);

}



int main()
{
    ifstream f("../teste.in");
    ofstream g("../rezultate.out");

    int nrteste;
    f>>nrteste;

    cout<<"1. Bubble Sort\n2. Count Sort\n3. Radix Sort\n4. Merge Sort\n5. Quick Sort\n6. Inchide Programul\n\n";

    int a;
    cin>>a;

    switch(a)
    {
    case 1:
        system("cls");

        break;
    }

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

            quick(v,0,n-1);

            durata = (clock() - start) / (float)CLOCKS_PER_SEC;

            if(test_sort(v))
            {
                cout<<"Quick sort: Sortat Corect, Timp de sortare: "<<durata<<" secunde\n\n";
                g<<"Quick sort: Sortat Corect, Timp de sortare: "<<durata<<" secunde\n";
                for(int i=0; i<n; ++i)
                    g<<v[i]<<" ";
            }
            else
                cout<<"Quick sort: Sortat Incorect\n\n";
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
