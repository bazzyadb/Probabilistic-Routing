#include<iostream>
#include<ctime>
#include"router.h"
using namespace std;

 
#define ff              first
#define ss              second
#define int             long long
#define pb              push_back
#define pii             pair<int,int>
#define vi              vector<int>
#define mii             map<int,int>
#define pqb             priority_queue<int>
#define pqs             priority_queue<int,vi,greater<int> >
#define setbits(x)      __builtin_popcountll(x)
#define zrobits(x)      __builtin_ctzll(x)
#define mod             1000000007
#define ps(x,y)         cout<<setprecision(y)<<x
#define mk(arr,n,type)  type *arr=new type[n];
#define w(x)            int x; cin>>x; while(x--)
#define pw(b,p)         pow(b,p) + 0.1
#define endl            "\n"



void fastIO()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
}

void solve()
{
    int n,m;
    cin>>n>>m;

    router network[1000];
    for(int i=0;i<n;i++) network[i]= (router(n,i,network));

    for(int i=0;i<m;i++)
    {
        int a,b;
        double c;
        cin>>a>>b>>c;
        a--;b--;
        network[a].addEdge(b,c);
        network[b].addEdge(a,c);
    }

    int q;
    cin>>q;
    for(int i=0;i<q;i++)
    {
        int src,dest,dur,strt;
        cin>>src>>dest>>dur>>strt;
        src--;dest--;

        while(dur--) network[src].recieve(packet(src,dest),strt);
    }
    double rc=0;
    
        if(true) for(int j=0;j<n;j++) network[j].sendupdate();
    for(int i=0;;i++)
    {


        bool rem = false;
        for(int j=0;j<n;j++)
        {
            rem |= network[j].iterate(i);
        }
        rc=i;
        if(!rem) break;
    }


    double load=0;
    double ct=0;
    map<int,double> qs;
    for(int i=0;i<n;i++)
    {
        network[i].info(load,qs,ct);
    }

    cout<<"SIMULATION END\nRESULTS:\n";
    cout<<"CONVERGENCE TIME: "<<ct;
    cout<<"\nLOAD: "<<load/(n*rc/100)<<"%\n";
    cout<<"QUEUE SIZE/TIME: ";
    for(auto j:qs)
    {
        cout<<j.ss<<",";
    }
}
 
int32_t main()
{
    fastIO();
    w(t)
    {
        solve();
        cout<<endl;
    }
    return 0;
}