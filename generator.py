# your code goes here
tc=50
#max_n=10
from random import randint as ri
import random

ip = open('filename.txt','w')
def printc(g):
    ip.write(str(g)+'\n')

printc(tc)#printing testcases
n=ri(40,50)
m=ri(n-1,(n*n-n)//2) 
v=[j+1 for j in range(n)]
random.shuffle(v) 
edges=[]
edge_map={}
nodes=[v.pop()] 

while (len(v)):
    k=v.pop()
    c=nodes[ri(0,len(nodes)-1)]
    if ri(0,1): 
        edges.append([c,k])
    else:
        edges.append([k,c])
    nodes.append(k)
    random.shuffle(nodes)
    edge_map[(c,k)]=1;edge_map[(k,c)]=1
extra={}
for j in range(n,m+1): 
    p=ri(1,n);q=ri(1,n)
    while (p,q) in edge_map or (q,p) in edge_map or p==q:
        p=ri(1,n);q=ri(1,n) 
    if ri(0,1): 
        edges.append([p,q])
    else:
        edges.append([q,p])
        
    edge_map[(p,q)]=1;edge_map[(q,p)]=1
    extra[(p,q)]=1;extra[(q,p)]=1
    
random.shuffle(edges)
weight=[ri(1,50) for j in range(m)]
from copy import deepcopy
for j in range(tc):
    printc(str(n)+' '+str(m)) 
    g=0
    for i in edges:
        printc(str(i[0])+' '+str(i[1])+' '+str(weight[g]));g+=1 
    q=random.randint(1,15) 
    printc(q)
    em=deepcopy(extra)
    t=0
    for j in range(q):
        qt=ri(0,2) 
        t=ri(t+1,t+10)
        if qt == 0:
      
            c=ri(1,n)
            qy=ri(1,n)
            while c==qy:
                qy=ri(1,n)
            printc(str(t)+' '+str(qt)+' '+str(c)+' '+str(qy)+' ' +str(ri(1,100)))
        
        else:
            y=random.choice(em.keys()) 
            c,qy=y[0],y[1]
            #em[(c,qy)]=1;em[(qy,c)]=1
            printc(str(t)+' '+str(1)+' '+str(c)+' '+str(qy)+' ' +str(ri(1,100)))
        
    printc('~')