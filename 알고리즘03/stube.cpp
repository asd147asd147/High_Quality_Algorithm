#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace std;

ifstream in("test.inp");
ofstream out("test.out");

const double GAP = 0.00001;
double DISTANCE = 1e9;

typedef struct _point_coord{
    double x,y,z;
} point_coord;

point_coord A,B,C,D;

double distance_pq(point_coord p, point_coord q){
    return sqrt(pow((p.x - q.x),2)+pow((p.y - q.y),2)+pow((p.z - q.z),2));
}

point_coord find_point(point_coord p, point_coord q, double t){
    point_coord middle;
    middle.x = t*p.x + (1-t)*q.x;
    middle.y = t*p.y + (1-t)*q.y;
    middle.z = t*p.z + (1-t)*q.z;
    return middle;
}

point_coord min_point(point_coord lop, point_coord hip, point_coord q, double lo, double hi){
    double t = (lo+hi)/2;
    double tohi = t + GAP;
    double tolo = t - GAP;
    point_coord temp1 = find_point(lop,hip,t);
    if(lo + GAP >= hi) {
        return temp1;
    }
    point_coord temp2 = find_point(lop,hip,tolo);
    double lodis = distance_pq(temp2,q);
    DISTANCE = min(DISTANCE,lodis);

    point_coord temp3 = find_point(lop,hip,tohi);
    double hidis = distance_pq(temp3,q);
    DISTANCE = min(DISTANCE,hidis);

    if(lodis>hidis){
        return min_point(lop,hip,q,t,hi);
    }
    else{
        return min_point(lop,hip,q,lo,t);
    }
}

void input_coord(point_coord* point){
    in >> point->x;
    in >> point->y;
    in >> point->z;
}

void read_Data(){
    input_coord(&A);
    input_coord(&B);
    input_coord(&C);
    input_coord(&D);
}

void solve(){
    point_coord test = min_point(A,B,C,0,1);
    for(int i = 0; i < 10; ++i){
        test = min_point(C,D,test,0,1);
        test = min_point(A,B,test,0,1);
    }
}

void output(){
    cout << endl;
    cout << DISTANCE << endl;
    cout << ceil(DISTANCE);
}

int main(){
    read_Data();
    solve();
    output();
    return 0;
}
