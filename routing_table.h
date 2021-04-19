#include <map>
#include<iostream>
#include<cassert>
#include<vector>
using namespace std;

#define pii pair<int,int>
#define ff first
#define ss second


class routingTable{
    vector<vector<long double>> rt;
    int n;

    public:
    routingTable(int n)
    {
        this->n = n;
        rt.assign(n,vector<long double>(n,0));
    }

    void print()
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                cout<<j<<":"<<rt[i][j]<<" ";
            }
            cout<<endl;
        }
    }

    void add_entry(int i,int j,int dist)
    {
        assert(!rt[i][j]);
        rt[i][j]=dist;
    }

    void rem_entry(int i,int j)
    {
        rt[i][j]=0;
    }

    int lookup(int i,int j)
    {
        return rt[i][j];
    }

    void clear()
    {
        rt.clear();
    }

    void update()
    {
        //TO BE WORKED ON
        return;
    }
};