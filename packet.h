#include <map>
#include<iostream>
#include<cassert>
#include<vector>
using namespace std;

#define pii pair<int,int>
#define ff first
#define ss second


class packet
{
    int src;
    int dest;
    int hop;
    int seq_num;
    public:
    bool operator<(const packet&p)
    {
        return this->src>p.src;
    }
    packet(int a,int b)
    {
        src=a;
        dest=b;
    }
    int pkt_src(){return src;}
    int pkt_dest(){return dest;}
    int pkt_snum(){return seq_num;}

    int offset_;
    int offset(){return offset_;}
    // ACCESS
};