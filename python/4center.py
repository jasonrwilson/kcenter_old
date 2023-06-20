import sys
import numpy as np

def calc_dist(p,d):
    n = len(p)
    for i in range(n):
        for j in range(n):
            d[i][j] = np.linalg.norm(p[i]-p[j])

def centers_cost(d,c1,c2,c3,c4):
    cost = 0
    n = len(p)
    for i in range(n):
        dist_1 = d[i][c1]
        dist_2 = d[i][c2]
        dist_3 = d[i][c3]
        dist_4 = d[i][c4]
        min_dist = dist_1
        if (dist_2 < min_dist):
            min_dist = dist_2
        if (dist_3 < min_dist):
            min_dist = dist_3
        if (dist_4 < min_dist):
            min_dist = dist_4
        if (min_dist > cost):
            cost = min_dist
    return cost

def solve_4center(d,c):
    min_cost = float("inf")
    n = len(d)
    for i in range(0,n-3):
        for j in range(i+1,n-2):
            for k in range(j+1,n-1):
                for l in range(k+1,n):
                    cost = centers_cost(d,i,j,k,l)
                    if (cost < min_cost):
                        min_cost = cost
                        c[0] = i
                        c[1] = j
                        c[2] = k
                        c[3] = l
    return min_cost 

p = np.loadtxt(sys.argv[1],dtype=np.float32)
c = np.zeros(4,dtype='int')
n = len(p)
d = np.zeros((n,n),dtype='float32')
calc_dist(p,d)
min_cost = solve_4center(d,c)
print ('min_cost =',min_cost)
print ('centers =',c[0],c[1],c[2],c[3])
