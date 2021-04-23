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
    
    map<int,int> ctbyrcd_2;
    for(int i=0;;i++)
    {

        if(i%update_time==0) for(int j=0;j<n;j++) network[j].sendupdate();
        bool rem = false;
        int val = 0;
        for(int j=0;j<n;j++)
        {
            rem |= network[j].iterate(i,val);
            ctbyrcd_2[i]=max(ctbyrcd_2[i],val);
        }
        rc=i;
        if(!rem) break;
        if(!detail)
        {
            cout<<"ITERATION at: "<<i<<" complete\n";
        }
    }
    cout<<"\n\n\n\n#######################################\n\n\n";

    double load=0;
    double ct=0;
    map<int,double> qs;
    map<int,int> ctbyrcd;
    map<int,vector<int>> ctbyevnt;
    map<int,double> load_size;
    for(int i=0;i<n;i++)
    {
        network[i].info(load,qs,ct,ctbyrcd,ctbyevnt,load_size);
    }

    cout<<"SIMULATION END\nRESULTS:\n";
    cout<<"CONVERGENCE TIME: "<<ct;
    cout<<"\nLOAD: "<<load/(n*rc/100)<<"%\n";
    cout<<"QUEUE SIZE/TIME: ";
    for(auto j:qs)
    {
        cout<<j.ss<<",";
    }
    cout<<endl;

}
 
int32_t main()
{
    srand(time(0));
    fastIO();
    w(t)
    {
        solve();
        cout<<endl;
    }
    return 0;
}