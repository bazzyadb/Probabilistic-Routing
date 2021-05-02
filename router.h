#include <map>
#include<iostream>
#include<cassert>
#include<vector>
#include<queue>
#include<ctime>
#include<algorithm>
#include<cstdlib>
#include<numeric>
#include<algorithm>
#include "routing_table.h"
#include "packet.h"
using namespace std;

#define pii pair<int,int>
#define ff first
#define ss second
#define int long long




#define inf 1e10

#define detail false
#define initial_weight 10000
#define extreme (int)100000000
#define delta 0.05
#define threshold 0.05
#define omega 2.0
#define update_time 3000
#define upd_size n

class router
{
    #define front top
    int cur_time=0;
    int n;
    int loc;
    router* net;
    vector<vector<int>> Table;//contains probabilistic weights
    int idx;
    typedef pair<int,packet> p;
    //vector<p,vector<p>,greater<p>> Buffer;
    vector<p> Buffer;
    typedef pair<int,pair<int,vector<double>>> q;
    priority_queue<q,vector<q>,greater<q>> Upd;
    map<int,double> edges;
    vector<vector<double>>estimated_costs;
    map<int,int> queue_size;
    map<int,double> load_size;
    map<int,int> convergence_rcd;
    map<int,int> convergence_events;
    int convergence_time=0;
    int routecomp = 0;
    int events=0;
    double load=0;
    int all_events=0;
    public:
    router()
    {

    }
    router(int tot,int id,router ar[])
    {

        this->net = ar;
        this->n = tot;
        this->idx=id;
        Table.assign(n,vector<int>(n,0));
        estimated_costs.assign(n,vector<double>(n,0));
        if(detail) cout<<"CONSTRUCTING ROUTER:"<<idx<<endl;
    }
    void recieve(packet P,int tm)
    {
        if(detail) cout<<"RECIEVED PACKET AT:"<<idx<<"("<<tm<<")\n";
        Buffer.push_back({tm,P});
        sort(Buffer.begin(),Buffer.end(),[](auto a,auto b)->bool{
            return a.first>b.first;
        });
    }
    void addEdge(int to,double weight, int type)
    {
        if(type)
        {
            if(weight>0){
            	edges[to]=weight;
            	estimated_costs[to][to]=weight;
            }
            else{
                edges.erase(to);
                for(int i=0;i<n;i++){
                    Table[i][to]=0;
                }
                estimated_costs[to][to]=0;

            }
            sendupdate();
        }
        else
        {
        	edges[to]=weight;
        	for(int i=0;i<n;i++) Table[i][to] = initial_weight;
        	estimated_costs[to][to]=weight;
        }
    }
    double expected_weight(int dest)
    {
        double ans=0;
        int tot=0;
        for(int i=0;i<n;i++)
        {
            ans+=Table[dest][i]*estimated_costs[dest][i];
            tot+=Table[dest][i];
        }
        assert(tot>0);
        return ans/tot;
    }
    bool iterate(int tm,int &val)
    {
        cur_time=tm;
        queue_size[tm]+=Buffer.size()+Upd.size()*upd_size;
        while(!Upd.empty()&&Upd.front().first<=tm)
        {
            all_events++;
            auto cur = Upd.front();
            Upd.pop();
            update(cur.second.first,cur.second.second);
            break;
        }
        while(!Buffer.empty()&&Buffer.back().first<=tm)
        {
            all_events++;
            process_packet();
            break;
        }
        val = convergence_time;
        if(detail) cout<<"ITERATION OF ROUTER "<<idx<<" AT:"<<tm<<" IS COMPLETED"<<queue_size[tm]<<endl;
        //assert(tm>0);
        //load_size[tm] = events/(double)tm;
        return queue_size[tm];
    }

    void decreament(int &val)
    {
        double k = val;
        k*=delta;
        val-=k;
    }

    void process_packet()
    {

        packet cur =Buffer.back().second;
        Buffer.pop_back();
        if(cur.pkt_dest()==idx) return;
        int tot = accumulate(Table[cur.pkt_dest()].begin(),Table[cur.pkt_dest()].end(),0);
        int r = rand()%tot;
        tot = r+1;
        for(int nxt=1;nxt<n;nxt++)
        {
            if(tot<Table[cur.pkt_dest()][nxt]&&edges.count(nxt))
            {
                net[nxt].recieve(cur,cur_time+edges[nxt]);
                if(detail)cout<<"SENDING PACKET TO "<<nxt<<" FROM "<<idx<<endl;
                decreament(Table[cur.pkt_dest()][nxt]);
                return;
            }
            tot-=Table[cur.pkt_dest()][nxt];
        }

    }
    void recieveupdate(int from,vector<double> v,int t)
    {
        if(detail) cout<<"RECIEVED UPDATE FROM:"<<from<<" AT "<<idx<<endl;
        Upd.push({t,{from,v}});
        return;
    }
    void update(int from,vector<double> info)
    {
        convergence_rcd[cur_time] = convergence_time;
        convergence_events[events+1] = cur_time;
        convergence_time=cur_time;
        routecomp=cur_time;
        events++;
        if(detail)cout<<"UPDATING FOR "<<from<<" AT:"<<idx<<endl;

        if(detail)cout<<"BEFORE UPDATE AT :"<<idx<<endl;
        if(detail)for(int i=0;i<n;i++)
        {
            cout<<i<<":"<<expected_weight(i)<<endl;
        }


        for(auto &i: info) i+=edges[from];
        for(int i=0;i<n;i++)
        {
            estimated_costs[i][from]=info[i];
        }

        bool change=0;
        for(int i=0;i<n;i++)
        {
            double d = expected_weight(i);
            for(int j=0;j<n;j++)
            {
                if(!edges.count(j)) continue;
                if(detail)cout<<Table[i][j]<<":";
                double temp = (d-estimated_costs[i][j]);
                if(temp<0) temp = -temp;

                Table[i][j]+=Table[i][j]*(d-estimated_costs[i][j])/omega;
                Table[i][j]=max(Table[i][j],0ll);
                Table[i][j]=min(Table[i][j],extreme);
                if(detail)cout<<Table[i][j]<<"\n";
                if(Table[i][j]&&(temp) > (int)(threshold*omega))
                {
                    if(detail)cout<<temp<<"_++_)_"<<threshold*omega<<endl;
                    change = true;
                }
            }
        }
        if(detail)cout<<"AFTER UPDATE AT :"<<idx<<endl;
        if(detail)for(int i=0;i<n;i++)
        {
            cout<<i<<":"<<expected_weight(i)<<endl;
        }
        if(detail)if(change)
        {
            cout<<"SENDING|||||%%%%%%$$$$$$$";
            auto k = this->sendupdate();
        }
    }
    int sendupdate()
    {
        vector<double> updated_est;
        for(int i=0;i<n;i++)
        {
            updated_est.push_back(expected_weight(i));
        }
        updated_est[idx]=0;
        for(auto i: edges)
        {
            net[i.first].recieveupdate(idx,updated_est,cur_time+i.second);
        }

        return 0;
    }

    void info(double &ld,map<int,double> &m,double &ct,map<int,int> &m2,map<int,vector<int>> &convbyevent,map<int,double> &load__)
    {
        if(ct<convergence_time) ct = convergence_time;
        if(detail)cout<<"INFORMATION ABOUT ROUTER: "<<idx<<endl;
        if(detail)cout<<"LOAD: "<<events<<endl;
        if(detail)cout<<"QUEUE SIZE:\n";
        ld+=events;
        for(auto i: queue_size)
        {
            if(detail)cout<<i.first<<" "<<i.second<<endl;
            m[i.first]+=i.second;
        }
        for(auto i: convergence_rcd)
        {
            m2[i.second]=max(i.first,m2[i.second]);//i.second is the route computation delay
        }
        for(auto i: convergence_events)
        {
            convbyevent[i.first].push_back(i.second);// i.first is the event
        }

        for(auto i: load_size)
        {
            load__[i.first]+=i.second;
        }
    }
};

// n ,m
// edge discription (i,j,weight)
// number q
// src, dest, packets(100s)
