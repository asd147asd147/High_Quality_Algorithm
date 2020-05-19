#include <iostream>
#include <fstream>
#include <string.h>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>

#define INF 9999;

using namespace std;

ifstream in("test.inp");
ofstream out("drone.out");

typedef struct _coord{
    int x;
    int y;
} coord;

typedef struct _node{
    int min_dist = 0;
    int cur_dist = 0;
    int bound = 0;
    int weight = 0;
    int** dist;
    int* visited;
    vector<int> path;
} node;
int N;

struct compare1{
    bool operator()(node& I, node& C){
        return I.cur_dist+(I.min_dist-I.bound)*I.weight/4 > C.cur_dist+(C.min_dist-C.bound)*C.weight/4;
    }
};

struct compare2{
    bool operator()(node& I, node& C){
        return I.cur_dist+(I.min_dist-I.bound)*I.weight/6 > C.cur_dist+(C.min_dist-C.bound)*C.weight/6;
    }
};

node make_child_node(node& p_node, int v_n, int visit){
    node c_node;
    c_node.min_dist = p_node.min_dist;
    c_node.bound = p_node.bound;
    c_node.cur_dist = p_node.cur_dist;
    c_node.dist = new int*[v_n];
    for(int i = 0; i < v_n; i++){
        c_node.dist[i] = new int[v_n];
    }
    for(int i = 0; i < v_n; i++){
        if(p_node.visited[i]){
            for(int j = 0; j < v_n; j++){
                c_node.dist[i][j] = INF;
            }
        }
        else{
            copy(p_node.dist[i],p_node.dist[i]+v_n,c_node.dist[i]);
            c_node.dist[i][visit] = INF;
        }
    }
    c_node.dist[visit][0] = INF;
    c_node.visited = new int[v_n];

    copy(p_node.visited,p_node.visited+v_n,c_node.visited);
    c_node.visited[visit] = 1;
    c_node.path.assign(p_node.path.begin(),p_node.path.end());
    c_node.path.push_back(visit+1);
    c_node.weight = p_node.weight;
    return c_node;
}

int opti_weight(node* n, int v_n){
    int weight = 0;
    for(int i = 0; i < v_n; i++){
        int row_min = *min_element(n->dist[i],n->dist[i]+v_n);
        if(row_min != 9999)
            weight += row_min;
        for(int j = 0; j < v_n; j++){
            if(n->dist[i][j]!=9999){
                n->dist[i][j] -= row_min;
            }
        }
    }
    for(int i = 0; i < v_n; i++){
        int col_min = INF;
        for(int j = 0; j < v_n; j++){
            col_min = min(col_min,n->dist[j][i]);
        }
        if(col_min != 9999)
            weight += col_min;

        for(int j = 0; j < v_n; j++){
            if(n->dist[j][i]!=9999){
                n->dist[j][i] -= col_min;
            }
        }
    }
    return weight;
}

int main(){
    in >> N;
    if(N>13){
        priority_queue <node,vector<node>,compare1> pq;
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
        root.visited[0] = 1;
        root.path.push_back(1);
        root.weight = cur_w;
        root.min_dist = opti_weight(&root,N);
        pq.push(root);
        while(!pq.empty()){
            node temp = pq.top();
            pq.pop();
            if(temp.path.size() == N){
                node t = pq.top();
                if(temp.cur_dist+dist[*(temp.path.end()-1)-1][0] < t.cur_dist+(t.min_dist-t.bound)*t.weight){
                    cout << temp.cur_dist+dist[*(temp.path.end()-1)-1][0];
                    return 0;
                }
            }
            for(int i = 1; i < N; ++i){
                if(temp.visited[i])
                    continue;
                node child = make_child_node(temp,N,i);
                child.min_dist += opti_weight(&child,N);
                int path1 = *(child.path.end()-2)-1;
                int path2 = *(child.path.end()-1)-1;
                child.bound += dist[path1][path2];
                child.cur_dist += dist[path1][path2]*child.weight;
                child.weight -= weight[path2];

                pq.push(child);
            }
        }
    }
    else{
        priority_queue <node,vector<node>,compare2> pq;

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
        root.visited[0] = 1;
        root.path.push_back(1);
        root.weight = cur_w;
        root.min_dist = opti_weight(&root,N);
        pq.push(root);
        while(!pq.empty()){
            node temp = pq.top();
            pq.pop();
            if(temp.path.size() == N){
                node t = pq.top();
                if(temp.cur_dist+dist[*(temp.path.end()-1)-1][0] < t.cur_dist+(t.min_dist-t.bound)*t.weight){
                    out << temp.cur_dist+dist[*(temp.path.end()-1)-1][0];
                    return 0;
                }
            }
            for(int i = 1; i < N; ++i){
                if(temp.visited[i])
                    continue;
                node child = make_child_node(temp,N,i);
                child.min_dist += opti_weight(&child,N);
                int path1 = *(child.path.end()-2)-1;
                int path2 = *(child.path.end()-1)-1;
                child.bound += dist[path1][path2];
                child.cur_dist += dist[path1][path2]*child.weight;
                child.weight -= weight[path2];

                pq.push(child);
            }
        }
    }
    return 0;
}
