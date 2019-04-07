//
//  main.cpp
//  Lab4
//
//  Created by Иван Медведев on 05/04/2019.
//  Copyright © 2019 Medvedev. All rights reserved.
//

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <chrono>

using namespace std;

// Алгоритм Прима

void algorithmP() {
    
    int n = 7;//количество вершин
    float **a = new float*[n], **a1 = new float*[n];//матрицы весов графа и его остова
    float *used = new float[n]; //Массив использованных вершин
    short i, j;
    int count = 0;
    float s1 = 0;//вес остова
    
    for(int i=0;i<n;i++) {
        a[i] = new float[n];
        a1[i] = new float[n];
    }
    
    
// For 6
//    a[0][0] = 0;
//    a[0][1] = 7;
//    a[0][2] = 3;
//    a[0][3] = 8;
//    a[0][4] = 10;
//    a[0][5] = 9;
//    a[1][0] = 7;
//    a[1][1] = 0;
//    a[1][2] = 6;
//    a[1][3] = 0;
//    a[1][4] = 11;
//    a[1][5] = 0;
//    a[2][0] = 3;
//    a[2][1] = 6;
//    a[2][2] = 0;
//    a[2][3] = 5;
//    a[2][4] = 2;
//    a[2][5] = 15;
//    a[3][0] = 8;
//    a[3][1] = 0;
//    a[3][2] = 5;
//    a[3][3] = 0;
//    a[3][4] = 14;
//    a[3][5] = 0;
//    a[4][0] = 10;
//    a[4][1] = 11;
//    a[4][2] = 2;
//    a[4][3] = 14;
//    a[4][4] = 0;
//    a[4][5] = 0;
//    a[5][0] = 9;
//    a[5][1] = 0;
//    a[5][2] = 15;
//    a[5][3] = 0;
//    a[5][4] = 0;
//    a[5][5] = 0;
    
// For 7
    a[0][0] = 0;
    a[0][1] = 7;
    a[0][2] = 3;
    a[0][3] = 8;
    a[0][4] = 10;
    a[0][5] = 9;
    a[0][6] = 0;
    a[1][0] = 7;
    a[1][1] = 0;
    a[1][2] = 6;
    a[1][3] = 0;
    a[1][4] = 11;
    a[1][5] = 0;
    a[1][6] = 5;
    a[2][0] = 3;
    a[2][1] = 6;
    a[2][2] = 0;
    a[2][3] = 5;
    a[2][4] = 2;
    a[2][5] = 15;
    a[2][6] = 0;
    a[3][0] = 8;
    a[3][1] = 0;
    a[3][2] = 5;
    a[3][3] = 0;
    a[3][4] = 14;
    a[3][5] = 0;
    a[3][6] = 2;
    a[4][0] = 10;
    a[4][1] = 11;
    a[4][2] = 2;
    a[4][3] = 14;
    a[4][4] = 0;
    a[4][5] = 0;
    a[4][6] = 1;
    a[5][0] = 9;
    a[5][1] = 0;
    a[5][2] = 15;
    a[5][3] = 0;
    a[5][4] = 0;
    a[5][5] = 0;
    a[5][6] = 0;
    a[6][0] = 0;
    a[6][1] = 5;
    a[6][2] = 0;
    a[6][3] = 2;
    a[6][4] = 1;
    a[6][5] = 0;
    a[6][6] = 0;
    
    for (i = 0; i < n; i++)
    {
        used[i] = 0;
        for (j = 0; j < n; j++)
            a1[i][j] = 0;
    }
    
    used[0] = 1;
    
    while (count < n - 1)
    {
        float min = 100000;
        for (i = 0; i < n; i++)
        {
            if (used[i] != 0)
            {
                for (j = 0; j < n; j++)
                {
                    if ((a[i][j] < min) && (a[i][j] != 0) && (used[j]) == 0)
                        
                        min = a[i][j];
                    
                }
                
            }
        }
            
            for (int k = 0; k < n; k++)
            {
                
                for (j = 0; j < n; j++)
                {
                    
                    if ((a[k][j] == min) && (used[j] == 0))
                    {
                        used[j] = 1;
                        a1[k][j] = a1[j][k] = min;
                        s1 = s1 + a1[j][k];
                        k = n;
                        count = count + 1;
                        break;
                    }
                }
            }
        }
        cout << "Вес остова = " << s1 << endl;
    }

// Алгоритм Прима

// Алгоритм Крускала

typedef  pair<int, int> iPair;

// Structure to represent a graph
struct Graph
{
    int V, E;
    vector< pair<int, iPair> > edges;
    
    // Constructor
    Graph(int V, int E)
    {
        this->V = V;
        this->E = E;
    }
    
    // Utility function to add an edge
    void addEdge(int u, int v, int w)
    {
        edges.push_back({w, {u, v}});
    }
    
    // Function to find MST using Kruskal's
    // MST algorithm
    int kruskalMST();
};

// To represent Disjoint Sets
struct DisjointSets
{
    int *parent, *rnk;
    int n;
    
    // Constructor.
    DisjointSets(int n)
    {
        // Allocate memory
        this->n = n;
        parent = new int[n+1];
        rnk = new int[n+1];
        
        // Initially, all vertices are in
        // different sets and have rank 0.
        for (int i = 0; i <= n; i++)
        {
            rnk[i] = 0;
            
            //every element is parent of itself
            parent[i] = i;
        }
    }
    
    // Find the parent of a node 'u'
    // Path Compression
    int find(int u)
    {
        /* Make the parent of the nodes in the path
         from u--> parent[u] point to parent[u] */
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }
    
    // Union by rank
    void merge(int x, int y)
    {
        x = find(x), y = find(y);
        
        /* Make tree with smaller height
         a subtree of the other tree  */
        if (rnk[x] > rnk[y])
            parent[y] = x;
        else // If rnk[x] <= rnk[y]
            parent[x] = y;
        
        if (rnk[x] == rnk[y])
            rnk[y]++;
    }
};

/* Functions returns weight of the MST*/

int Graph::kruskalMST()
{
    int mst_wt = 0; // Initialize result
    
    // Sort edges in increasing order on basis of cost
    sort(edges.begin(), edges.end());
    
    // Create disjoint sets
    DisjointSets ds(V);
    
    // Iterate through all sorted edges
    vector< pair<int, iPair> >::iterator it;
    for (it=edges.begin(); it!=edges.end(); it++)
    {
        int u = it->second.first;
        int v = it->second.second;
        
        int set_u = ds.find(u);
        int set_v = ds.find(v);
        
        // Check if the selected edge is creating
        // a cycle or not (Cycle is created if u
        // and v belong to same set)
        if (set_u != set_v)
        {
            // Current edge will be in the MST
            // so print it
            cout << u << " - " << v << endl;
            
            // Update MST weight
            mst_wt += it->first;
            
            // Merge two sets
            ds.merge(set_u, set_v);
        }
    }
    
    return mst_wt;
}

// Алгоритм Крускала

int main(int argc, const char * argv[]) {
    
    srand((unsigned int)time(0));
    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::microseconds microseconds;
    
    Clock::time_point start;
    Clock::time_point end;
    microseconds ms;
    
    double result1=0, result2=0;
    
    start = Clock::now();
    algorithmP();
    end = Clock::now();
    ms = std::chrono::duration_cast<microseconds>(end - start);
    result1 = (double)ms.count()/1000000;
    
//    int V=3, E=3; //for 3
//    int V=4, E=6; //for 4
//    int V=5, E=8; //for 5
//    int V=6, E=11; //for 6
    int V=7, E=14;
    Graph g(V,E);
    
//    g.addEdge(1, 2, 7); // for 3
//    g.addEdge(2, 3, 9);
//    g.addEdge(1, 3, 5);
    
//    g.addEdge(1, 2, 4);// for 4
//    g.addEdge(1, 3, 2);
//    g.addEdge(1, 4, 5);
//    g.addEdge(2, 3, 3);
//    g.addEdge(2, 4, 6);
//    g.addEdge(3, 4, 1);
    
//    g.addEdge(1, 3, 3);// for 5
//    g.addEdge(1, 2, 7);
//    g.addEdge(1, 4, 8);
//    g.addEdge(2, 3, 6);
//    g.addEdge(2, 5, 11);
//    g.addEdge(3, 4, 5);
//    g.addEdge(3, 5, 2);
//    g.addEdge(4, 5, 14);
    
//    g.addEdge(1, 2, 7);//for 6
//    g.addEdge(2, 5, 11);
//    g.addEdge(4, 5, 14);
//    g.addEdge(3, 4, 5);
//    g.addEdge(3, 6, 15);
//    g.addEdge(1, 3, 3);
//    g.addEdge(1, 4, 8);
//    g.addEdge(2, 3, 6);
//    g.addEdge(3, 5, 2);
//    g.addEdge(1, 5, 10);
//    g.addEdge(1, 6, 9);
    
    g.addEdge(1, 6, 9);
    g.addEdge(3, 6, 15);
    g.addEdge(3, 4, 5);
    g.addEdge(4, 5, 14);
    g.addEdge(2, 5, 11);
    g.addEdge(1, 2, 7);
    g.addEdge(1, 3, 3);
    g.addEdge(1, 4, 8);
    g.addEdge(2, 3, 6);
    g.addEdge(1, 5, 10);
    g.addEdge(3, 5, 2);
    g.addEdge(2, 7, 5);
    g.addEdge(4, 7, 2);
    g.addEdge(5, 7, 1);
    
    
    start = Clock::now();
    cout << g.kruskalMST() << endl;
    end = Clock::now();
    ms = std::chrono::duration_cast<microseconds>(end - start);
    result2 = (double)ms.count()/1000000;
    
    cout << "Алгоритм Прима: " << fixed << result1 << endl;
    cout << "Алгоритм Крускала: " << fixed << result2 << endl;
    return 0;
}
