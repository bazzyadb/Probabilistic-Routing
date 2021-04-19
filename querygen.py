tc=1
max_n=20
from random import randint as ri
import random

ip = open('query.txt','w')

def printc(g):
    ip.write(str(g)+'\n')
n=0
m=0

q=random.randint(m//2,m) 
printc(q)
for j in range(q):
    c=ri(1,n);
    q=ri(1,n)
    while c==q:
        q=ri(1,n)
    printc(str(c)+' '+str(q)+' ' +str(ri(100,1000))) #printing queries