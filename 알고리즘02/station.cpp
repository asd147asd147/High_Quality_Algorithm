#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

ifstream in("station.inp");
ofstream out("station.out");

double DISTANCE;

typedef struct _point_coord{
    double x,y,z;
} point_coord;

point_coord A,B,P;

double distance_pq(point_coord p, point_coord q){
    return sqrt(pow((p.x - q.x),2)+pow((p.y - q.y),2)+pow((p.z - q.z),2));
}

point_coord find_middle_point(point_coord p, point_coord q){
    point_coord temp;
    temp.x = (p.x+q.x)/2;
    temp.y = (p.y+q.y)/2;
    temp.z = (p.z+q.z)/2;
    return temp;
}

void min_distance(point_coord m, point_coord n){
    point_coord min_point1, min_point2;
    point_coord middle_point = find_middle_point(m,n);
    if(distance_pq(m,P)>distance_pq(n,P))
        min_point1 = n;
    else
        min_point1 = m;
    min_point2 = middle_point;

    if(distance_pq(min_point1,P) == distance_pq(min_point2,P)){
        DISTANCE = distance_pq(min_point1,P);
    }
    else{
        min_distance(min_point1,min_point2);
    }
}

void input_coord(point_coord* point){
    in >> point->x;
    in >> point->y;
    in >> point->z;
}

void input(){
    input_coord(&A);
    input_coord(&B);
    input_coord(&P);
}

void solve(){
    min_distance(A,B);
}

void output(){
    out << ceil(DISTANCE);
}

int main(){
    input();
    solve();
    output();
    return 0;
}
