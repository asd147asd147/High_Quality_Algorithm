#include <iostream>
#include <fstream>
#include <algorithm>
#include <string.h>
#include <queue>
#include <utility>

using namespace std;

ifstream in("lock.inp");
ofstream out("lock.out");

int maze[31][31];
int visit[31][31];
int N,M;
pair<int,int> S, T;
queue<pair<int,int>> path;
queue<vector<pair<int,int>>> memo;
vector<pair<int,int>> res;

void input_data() {
    in >> N >> M;
    char temp;
    vector<pair<int,int>> t;
    for(int i = N; i >= 1; i--) {
        for(int j = 1; j <= M; ++j) {
            in >> temp;
            switch(temp) {
            case '#':
                maze[i][j] = 0;
                break;
            case '_':
                maze[i][j] = 1;
                break;
            case 'S':
                maze[i][j] = 2;
                S = make_pair(i,j);
                path.push(S);
                t.push_back(S);
                memo.push(t);
                break;
            case 'T':
                maze[i][j] = 3;
                T = make_pair(i,j);
                break;
            }
        }
    }
}

void find_path(){
    while(!path.empty()){
        if(path.front() == T)
            return;
        int i = path.front().first;
        int j = path.front().second;
        if(visit[i][j] == 1){
            path.pop();
            memo.pop();
            continue;
        }
        vector<pair<int,int>> t;
        t = memo.front();
        t.push_back(make_pair(0,0));
        visit[i][j] = 1;
        if(maze[i+1][j]!=0 && visit[i+1][j] == 0){
            path.push(make_pair(i+1,j));
            *(t.end()-1) = make_pair(i+1,j);
            memo.push(t);
        }
        if(maze[i][j+1]!=0 && visit[i][j+1] == 0){
            path.push(make_pair(i,j+1));
            *(t.end()-1) = make_pair(i,j+1);
            memo.push(t);
        }
        if(maze[i-1][j]!=0 && visit[i-1][j] == 0){
            path.push(make_pair(i-1,j));
            *(t.end()-1) = make_pair(i-1,j);
            memo.push(t);
        }
        if(maze[i][j-1]!=0 && visit[i][j-1] == 0){
            path.push(make_pair(i,j-1));
            *(t.end()-1) = make_pair(i,j-1);
            memo.push(t);
        }
        path.pop();
        memo.pop();
    }
}

void init_visit(){
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= M; ++j){
            visit[i][j] = 0;
        }
    }
}

int check_cut(){
    queue<pair<int,int>> p;
    p.push(S);
    while(!p.empty()){
        if(p.front() == T)
            return 0;

        int i = p.front().first;
        int j = p.front().second;
        if(visit[i][j] == 1){
            p.pop();
            continue;
        }
        visit[i][j] = 1;
        if(maze[i+1][j]!=0 && visit[i+1][j] == 0){
            p.push(make_pair(i+1,j));
        }
        if(maze[i][j+1]!=0 && visit[i][j+1] == 0){
            p.push(make_pair(i,j+1));
        }
        if(maze[i-1][j]!=0 && visit[i-1][j] == 0){
            p.push(make_pair(i-1,j));
        }
        if(maze[i][j-1]!=0 && visit[i][j-1] == 0){
            p.push(make_pair(i,j-1));
        }
        p.pop();
    }
    return 1;
}

void find_cut(){
    vector<pair<int,int>> short_path;
    short_path = memo.front();
    int sz = short_path.size();
    if(sz == 0)
        return;
    for(int i = 1; i < sz-1; ++i){
        init_visit();
        maze[short_path[i].first][short_path[i].second] = 0;
        if(check_cut()){
            res.push_back(short_path[i]);
        }
        maze[short_path[i].first][short_path[i].second] = 1;
    }
}

bool cmp(const pair<int,int>& t1, const pair<int,int>& t2){
    if(t2.second < t1.second){
        return 0;
    }
    else if(t2.second == t1.second){
        if(t2.first < t1.first){
            return 0;
        }
    }
    return 1;
}

void output_data(){
    if(res.size() == 0){
        out << 0;
        return;
    }
    out << res.size() << endl;
    sort(res.begin(),res.end(),cmp);
    for(int i = 0; i < res.size(); ++i){
        out << res[i].second <<" "<<res[i].first << endl;
    }
}

int main() {
    input_data();
    find_path();
    find_cut();
    output_data();
//    for(int i = 0; i <= N+1; ++i) {
//        for(int j = 0; j <= M+1; ++j) {
//            cout << maze[i][j];
//        }
//        cout << endl;
//    }
//    cout << "S x,y" <<endl;
//    cout << S.first << " " << S.second << endl;
//    cout << "T x,y" <<endl;
//    cout << T.first << " " << T.second << endl;

//    for(auto s : memo.front())
//        cout << s.second << " " << s.first<< endl;
    return 0;
}
