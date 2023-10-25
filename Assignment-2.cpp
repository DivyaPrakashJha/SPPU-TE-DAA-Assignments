// Problem Statement

// Write a program to implement Bellman-Ford Algorithm using Dynamic Programming and verify the time complexity

// Bellman Ford Algorithm

// It is a single source shortest path algorithm

// It is applicable only on directed graphs
// If we have to apply this algo on an undirected graph, we have to convert it into a directed graph i.e a-b become a->b and a<-b

// It helps us to detect negative cycles

#include<bits/stdc++.h>

using namespace std;

#define inf 1e9

int main(){
    int n, m;
    cin>>n>>m;

    vector<pair<pair<int, int>, int>>edges; // {{u, v}, w}

    for(int i = 0, u, v, w; i < m; i++){
        cin>>u>>v>>w;

        edges.push_back({{u, v}, w});
    }

    vector<int>dist(n, inf);

    // n -> number of nodes
    // Relax all the edges n-1 times sequentially
    // Relax : if (dist[u] + wt < dist[v]) dist[v] = dist[u] + wt;

    // Since in a graph of N nodes, in worst case it will take n-1 edges to reach from the first to the last
    // thereby we iterate for N-1 iterations

    int src = 0;
    dist[src] = 0;

    for(int i = 0; i < n-1 ; i++){
        for(auto it : edges){
            int u = it.first.first;
            int v = it.first.second;
            int w = it.second;

            if (dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
            }
        }
    }

    for(int i = 0; i < n; i++){
        cout<<dist[i]<<" ";
    }

    // In order to detect whether a negative cycle exists or not, 
    // relax all the edge one more time (nth time) and if the shortest distance for any node reduces then we can say that a negative cycle exists. 
    // In short if we relax the edges N times, and there is any change in the shortest distance of any node 
    // between the N-1th and Nth relaxation than a negative cycle exists, otherwise not exist.

    // Relaxing the edges nth time
    for(auto it : edges){
        for(auto it : edges){
            int u = it.first.first;
            int v = it.first.second;
            int w = it.second;

            if (dist[u] + w < dist[v]){
                cout<<"\nNegative Cycle Exists";
                return 0;
            }
        }
    }

    cout<<"\nNegative Cycle doesn't exist";
}

// T.C. - O(V*E)
// S.C. - O(V+E)

// Sample Test Cases

// 6 7
// 0 1 5
// 1 5 -3
// 1 2 -2
// 2 4 3
// 3 2 6
// 5 3 1
// 3 4 -2

// 6 7
// 0 1 5
// 1 5 -3
// 2 1 -2
// 2 4 3
// 3 2 1
// 5 3 1
// 3 4 -2

// Output

// 0 5 3 3 1 2 
// Negative Cycle doesn't exist

// 0 2 1 0 -2 -1 
// Negative Cycle Exists