#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

ifstream in("station.inp");
ofstream out("station.out");

double DISTANCE;

typedef struct _point_coord{
    int x,y,z;
} point_coord;

point_coord A,B,P;

double vector_length(point_coord point){
    return pow((double)point.x,2)+pow((double)point.y,2)+pow((double)point.z,2);
}

point_coord make_vector_pq(point_coord p, point_coord q){
    point_coord temp;
    temp.x = q.x - p.x;
    temp.y = q.y - p.y;
    temp.z = q.z - p.z;
    return temp;
}

point_coord cross_product(point_coord OM, point_coord ON){
    point_coord temp;
    temp.x = (OM.y*ON.z)-(OM.z*ON.y);
    temp.y = (OM.z*ON.x)-(OM.x*ON.z);
    temp.z = (OM.x*ON.y)-(OM.y*ON.x);
    return  temp;
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
    point_coord AP, AB;
    point_coord APcrossAB;
    AP = make_vector_pq(A,P);
    AB = make_vector_pq(A,B);

    APcrossAB = cross_product(AP, AB);
    DISTANCE = sqrt(vector_length(APcrossAB)/vector_length(AB));
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
