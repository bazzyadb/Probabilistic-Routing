tc=1
max_n=10
from random import randint as ri
import random

ip = open('filename.txt','w')
def printc(g):
    ip.write(str(g)+'\n')
printc(tc)#printing testcases
for j in range(tc):
    n=ri(3,max_n)
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
    for j in range(n,m+1): 
        p=ri(1,n);q=ri(1,n)
        while (p,q) in edge_map or (q,p) in edge_map or p==q:
            p=ri(1,n);q=ri(1,n) 
        if ri(0,1): 
            edges.append([p,q])
        else:
            edges.append([q,p])
        
        edge_map[(p,q)]=1;edge_map[(q,p)]=1
    
    random.shuffle(edges)
    printc(str(n)+' '+str(m))
    for i in edges:
        printc(str(i[0])+' '+str(i[1])+' '+str(ri(1,50))) #printing edges 
    q=random.randint(1,50) 
    printc(q)
    prev = 3
    for j in range(q):
        c=ri(1,n)
        q=ri(1,n)
        while c==q:
            q=ri(1,n)
        prev = ri(prev+1,prev+10)
        printc(str(c)+' '+str(q)+' ' +str(ri(1,100))+f' {prev}') #printing queries