#include <iostream>
#include <fstream>
#include <string.h>
#include <cstdlib>

using namespace std;

ifstream in("1.inp");
ofstream out("drone.out");

typedef struct _coord{
    int x;
    int y;
} coord;

int N;

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
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            dist[i][j] = abs(point[i].x-point[j].x)+abs(point[i].y-point[j].y);
        }
    }


    cout << "weight_init : " << cur_w << endl;
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            cout << dist[i][j] << " ";
        }
        cout <<endl;
    }

    return 0;
}
