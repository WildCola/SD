#include<bits/stdc++.h>

using namespace std;

ifstream f("../teste.in");
ofstream g("../rezultate.out");

int a, n, nmax;

bool test_sort(vector<int> v)
{
    for(int i=1; i<n; ++i)
        if(v[i]<v[i-1])
            return 0;
    return 1;
}

bool eficient(int n)
{
    if(n>100000 && a==1)
        return 0;
    if((n>100000000 || nmax>100000000) && a==2)
        return 0;
    if((n>100000000 || nmax>100000000) && a==3)
        return 0;
    if(n>10000000 && (a==4 || a==5))
        return 0;
    return 1;
}

void generare1(vector<int>& v)
{
    int aux = sqrt(nmax);
    for(int i=1; i<=n; ++i)
    {
        int x,y;
        x = (rand() % aux) + 1;
        y = (rand() % aux) + 1;
        v.push_back(x*y);
    }
}

void generare2(vector<int>& c)
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
}

void bubble(vector<int>& v)
{
    int aux = n;
    int sortat=0;
    while(!sortat)
    {
        sortat = 1;
        for(int i=0; i<aux-1; ++i)
            if(v[i] > v[i+1])
            {
                swap(v[i], v[i+1]);
                sortat = 0;
            }
        --aux;
    }
}

void countsort(vector<int>& v, vector<int> c)
{
    int nrelem = 0;
    for(int i=1; i<=nmax; ++i)
        if(c[i]>0)
            for(int j=1; j<=c[i]; ++j)
            {
                v.push_back(i);
                nrelem++;
            }
}

void radix(vector<int>& v)
{
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
    int nrteste;
    f>>nrteste;

    Menu:
    system("cls");
    cout<<"1. Bubble Sort\n2. Count Sort\n3. Radix Sort\n4. Merge Sort\n5. Quick Sort\n6. Inchide Programul\n\n";

    cin>>a;
    cout<<"\n";
    if(a==6)
        return 0;
    if(a>6)
        goto Menu;

    for(int i = 1; i<=nrteste; ++i)
    {
        f>>n>>nmax;

        int aux = sqrt(nmax);

        g<<"Test "<<i<<":\n";
        cout<<"Test "<<i<<":\n";

        vector<int> v;

        if(eficient(n))
        {
            vector<int> c;
            if(a==2)
                generare2(c);
            else
                generare1(v);

            clock_t start;
            start = clock();
            float durata;

            if(a==1)
            {
                bubble(v);
                cout<<"Quick sort: ";
                g<<"Quick sort: ";
            }

            if(a==2)
            {
                countsort(v, c);
                cout<<"Count sort: ";
                g<<"Count sort: ";
            }

            if(a==3)
            {
                radix(v);
                cout<<"Radix sort: ";
                g<<"Radix sort: ";
            }

            if(a==4)
            {
                MergeSort(v, 0, n-1);
                cout<<"Merge sort: ";
                g<<"Merge sort: ";
            }

            if(a==5)
            {
                quick(v, 0, n-1);
                cout<<"Quick sort: ";
                g<<"Quick sort: ";
            }


            durata = (clock() - start) / (float)CLOCKS_PER_SEC;


            if(test_sort(v))
            {
                cout<<"Sortat Corect, Timp de sortare: "<<durata<<" secunde\n\n";
                g<<"Sortat Corect, Timp de sortare: "<<durata<<" secunde\n";
                for(int i=0; i<n; ++i)
                    g<<v[i]<<" ";
            }
            else
                cout<<"Sortat Incorect\n\n";
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
