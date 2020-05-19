#include <iostream>
#include <fstream>
#include <string.h>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>


#define INF 999999;

using namespace std;

ifstream in("1.inp");
ofstream out("drone.out");

typedef struct _coord{
    int x;
    int y;
} coord;

typedef struct _node{
    int min_dist = 0;
    int** dist;
    int* visited;
    vector<int> path;
    int weight = 0;
} node;

struct compare{
    bool operator()(node& I, node& C){
        return I.min_dist > C.min_dist;
    }
};

priority_queue <node,vector<node>,compare> pq;

int N;

node make_child_node(node& p_node, int v_n, int visit){
    node c_node;
    c_node.min_dist = p_node.min_dist;
    c_node.dist = new int*[v_n];
    for(int i = 0; i < v_n; i++){
        c_node.dist[i] = new int[v_n];
    }

    for(int i = 0; i < v_n; i++){
        for(int j = 0; j < v_n; j++){
            if(p_node.visited[i]){
                c_node.dist[i][j] = INF;
            }
            else if(j == visit){
                c_node.dist[i][j] = INF;
            }
            else{
                c_node.dist[i][j] = p_node.dist[i][j];
            }
            c_node.dist[visit][0] = INF;
        }
    }
    c_node.visited = new int[v_n];
    for(int i = 0; i < v_n; i++){
        c_node.visited[i] = p_node.visited[i];
    }
    c_node.visited[visit] = 1;
    c_node.path.assign(p_node.path.begin(),p_node.path.end());
    c_node.weight = p_node.weight;
    return c_node;
}

int opti_weight(node* n, int v_n){
    int weight = 0;
    for(int i = 0; i < v_n; i++){
        int row_min = *min_element(n->dist[i],n->dist[i]+v_n);
        if(row_min != 999999)
            weight += row_min;
        for(int j = 0; j < v_n; j++){
            if(n->dist[i][j]!=999999){
                n->dist[i][j] -= row_min;
            }
        }
    }
    for(int i = 0; i < v_n; i++){
        int col_min = INF;
        for(int j = 0; j < v_n; j++){
            col_min = n->dist[j][i] < col_min ? n->dist[j][i] : col_min;
        }
        if(col_min != 999999)
            weight += col_min;

        for(int j = 0; j < v_n; j++){
            if(n->dist[j][i]!=999999){
                n->dist[j][i] -= col_min;
            }
        }
    }
    return weight;
}

int main(){
    in >> N;
    int weight[N];
    coord point[N];
    int dist[N][N];
    int h;
    int cur_w = 1;
    for(int i = 0; i < N; ++i){
        in >> h;
        h-=1;
        in >> weight[h] >> point[h].x >> point[h].y;
        cur_w += weight[h];
    }

    node root;
    root.dist = new int*[N];
    for(int i = 0; i < N; i++){
        root.dist[i] = new int[N];
    }
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            dist[i][j] = root.dist[i][j] = abs(point[i].x-point[j].x)+abs(point[i].y-point[j].y);
        }
    }
    for(int i = 0; i <N; i++){
        root.dist[i][i] = INF;
    }
    root.visited = new int[N];
    for(int i = 0; i <N; i++){
        root.visited[i] = 0;
    }
    /*
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            cout << root.dist[i][j] << " ";
        }
        cout <<endl;
    }*/
    root.weight = cur_w;
    root.min_dist = opti_weight(&root,N)*cur_w;
    root.visited[0] = 1;
    root.path.push_back(1);

    for(int k = 1; k < N; k++){
        node child = make_child_node(root,N,k);
        child.weight -= weight[k];
        child.min_dist = 0;
        int temp_w = 0;
        for(int i = 0; i < child.path.size()-1; i++){
            child.min_dist += dist[child.path[i]-1][child.path[i+1]-1] * (cur_w-temp_w);
            temp_w += weight[child.path[i+1]-1];
        }
        child.min_dist += opti_weight(&child,N)*child.weight;
        child.path.push_back(k+1);
        pq.push(child);
    }
    while(!pq.empty()){
        node temp = pq.top();
        pq.pop();
        for(int k = 1; k <N; k++){
            if(temp.visited[k])
                continue;
            node child = make_child_node(temp,N,k);
            child.weight -= weight[k];
            child.min_dist = 0;
            int temp_w = 0;
            for(int i = 0; i < child.path.size()-1; i++){
                child.min_dist += dist[child.path[i]-1][child.path[i+1]-1] * (cur_w-temp_w);
                temp_w += weight[child.path[i+1]-1];
            }
            child.min_dist += opti_weight(&child,N)*child.weight;
            child.path.push_back(k+1);
            pq.push(child);
        }
        if(temp.path.size() == N){
            int res = 0;
            temp.path.push_back(1);
            int temp_w = 0;
            for(int i = 0; i < N+1; i++){
                res += dist[temp.path[i]-1][temp.path[i+1]-1] * (cur_w-temp_w);
                temp_w += weight[temp.path[i+1]-1];
            }
            out << res;
            return 0;
        }
    }
    return 0;
}
