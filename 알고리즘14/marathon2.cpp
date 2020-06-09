#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <list>
#include <tuple>
#include <set>

using namespace std;
# define INF 1e9

ifstream in("marathon.inp");
ofstream out("marathon.out");

typedef struct _Edge {
    int u,v,weight;
} Edge;

bool operator==(Edge e1, Edge e2) {
    return e1.u==e2.u && e1.v==e2.v && e1.weight==e2.weight;
}

class Graph {
  public :
    int V ;
    list < tuple <int, int > >*adj;
    vector < Edge > edge;

    Graph( int V ) {
        this->V = V ;
        adj = new list < tuple <int, int > >[V];
    }

    void addEdge ( int u, int v, int w ) {
        if(v < u) {
            int t = u;
            u = v;
            v = t;
        }
        adj[u].push_back( make_tuple( v, w ));
        adj[v].push_back( make_tuple( u, w ));

        Edge e { u, v, w };
        if(find(edge.begin(),edge.end(),e)==edge.end()) {
            edge.push_back(e);
        }
    }

    void removeEdge ( int u, int v, int w ) {
        adj[u].remove(make_tuple( v, w ));
        adj[v].remove(make_tuple( u, w ));
    }

    int  ShortestPath ( int u, int v ) {
        set< tuple<int, int> > s;
        vector<int> dist(V, INF);
        s.insert(make_tuple(0, u));
        dist[u] = 0;
        while (!s.empty()) {
            tuple<int, int> tmp = *(s.begin());
            s.erase(s.begin());

            int u = get<1>(tmp);
            for (auto i = adj[u].begin(); i != adj[u].end(); ++i) {
                int v = get<0>(*i);
                int weight = get<1>(*i);
                if (dist[v] > dist[u] + weight) {
                    if (dist[v] != INF)
                        s.erase(s.find(make_tuple(dist[v], v)));
                    dist[v] = dist[u] + weight;
                    s.insert(make_tuple(dist[v], v));
                }
            }
        }
        return dist[v] ;
    }

    int FindMinimumCycle () {
        int min_cycle = INF;
        int E = edge.size();
        for ( int i = 0 ; i < E ; i++ ) {
            Edge e = edge[i];
            removeEdge( e.u, e.v, e.weight ) ;
            int distance = ShortestPath( e.u, e.v );
            min_cycle = min( min_cycle, distance + e.weight );
            addEdge( e.u, e.v, e.weight );
        }
        return min_cycle ;
    }
};

int main() {
    int V;
    in >> V;
    Graph g(V);
    int vertex_num;
    for(int i = 0; i < V; ++i) {
        in >> vertex_num;
        int node_num, weight;
        in >> node_num;
        while(node_num!=0) {
            in >> weight;
            g.addEdge(vertex_num-1,node_num-1,weight);
            in >> node_num;
        }
    }
    out << g.FindMinimumCycle();
    return 0;
}
