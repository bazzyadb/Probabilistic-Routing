#include <iostream>
#include <ctime>
#include"router.h"
using namespace std;

#define ff first
#define ss second
#define int long long
#define pb push_back
#define pii pair<int, int>
#define vi vector<int>
#define mii map<int, int>
#define pqb priority_queue<int>
#define pqs priority_queue<int, vi, greater < int>>
#define setbits(x) __builtin_popcountll(x)
#define zrobits(x) __builtin_ctzll(x)
#define mod 1000000007
#define ps(x, y) cout << setprecision(y) << x
#define mk(arr, n, type) type *arr = new type[n];


#define pw(b, p) pow(b, p) + 0.1
#define endl "\n"
vector<int> qss,cct,rcf,ld;
void fastIO()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
}

void solve()
{
	int n, m;
	cin >> n >> m;

	router network[1000];
	for (int i = 0; i < n; i++) network[i] = (router(n, i, network));

	for (int i = 0; i < m; i++)
	{
		int a, b;
		double c;
		cin >> a >> b >> c;
		a--;
		b--;
		network[a].addEdge(b, c, 0);
		network[b].addEdge(a, c, 0);
	}

	int q;
	cin >> q;
	map<int,vector<int>> we;
	for (int i = 0; i < q; i++)
	{
		int time, query_type;
		cin >> time >> query_type;

		if (query_type == 0)
		{
			int src, dest, dur;
			cin >> src >> dest >> dur;
			src--;
			dest--;

			while (dur--) network[src].recieve(packet(src, dest), time);
		}
		else if (query_type == 1)
		{
		     int a,b,c;
			cin >> a >> b >> c;
			a--;
			b--;
			we[time]={a,b,c,1};

		}


	}
	double rc = 0;
    qss.push_back(we.size());
	map<int, int> ctbyrcd_2;
	int rcd;
	for (int i = 0;; i++)
	{

		if(we.find(i)!=we.end()){
            network[we[i][0]].addEdge(we[i][1],we[i][2],we[i][3]);
            network[we[i][1]].addEdge(we[i][0],we[i][2],we[i][3]);
		}
		if (i % update_time == 0)
			for (int j = 0; j < n; j++) network[j].sendupdate();
		bool rem = false;
		int val = 0;
		for (int j = 0; j < n; j++)
		{
			rem |= network[j].iterate(i, val);
			ctbyrcd_2[i] = max(ctbyrcd_2[i], val);
		}
		rc = i;
		if (!rem){rcd=i; break;}
		/*if (!detail)
		{
			cout << "ITERATION at: " << i << " complete\n";
		}*/
	}
	rcf.push_back(rcd);
	cout << "\n\n\n\n#######################################\n\n\n";

	double load = 0;
	double ct = 0;
	map<int, double> qs;
	map<int, int> ctbyrcd;
	map<int, vector < int>> ctbyevnt;
	map<int, double> load_size;
	for (int i = 0; i < n; i++)
	{
		network[i].info(load, qs, ct, ctbyrcd, ctbyevnt, load_size);
	}

	//cout << "SIMULATION END\nRESULTS:\n";
	//cout << "CONVERGENCE TIME: " << ct;
	//cout<<"Route Computation Delay"<<rcd;
    assert(rc>0);
    cct.push_back(ct);
    ld.push_back(load/(n*rc/100));
	//cout << "\nLOAD: " << load / (n *rc / 100) << "%\n";
	//cout << "QUEUE SIZE/TIME: ";
	/*for (auto j: qs)
	{
		cout << j.ss << ",";
	}
	cout << endl;*/

}

int32_t main()
{
	srand(time(0));
	fastIO();
	freopen("jj.txt","r",stdin);
	freopen("oop.txt","w",stdout);
	int t;cin>>t;

	while(t--)
	{
		solve();
		cout << t<<endl;
		string kk;
		cin>>kk;
	}
	cout<<"#Convergence"<<endl;
	for(int i:cct){
        cout<<i<<", ";
	}
	cout<<endl;
	cout<<"#load"<<endl;
	for(int i:ld){
        cout<<i<<", ";
	}
	cout<<endl;
	cout<<"#query size"<<endl;
	for(int i:qss){
        cout<<i<<", ";
	}
	cout<<endl;
	cout<<"#delay"<<endl;
	for(int i:rcf){
        cout<<i<<", ";
	}
	cout<<endl;

	return 0;
}

