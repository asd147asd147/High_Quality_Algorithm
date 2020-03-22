#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace std;

ifstream in("3.inp");
ofstream out("test.out");

double DISTANCE;

typedef struct _point_coord{
    double x,y,z;
} point_coord;

point_coord A,B,C,D;

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

int equal_point(point_coord m, point_coord n){
    if(ceil(m.x*100000)/100000 == ceil(n.x*100000)/100000 && ceil(m.y*100000)/100000 == ceil(n.y*100000)/100000 && ceil(m.z*100000)/100000 == ceil(n.z*100000)/100000)
        return 1;
    return 0;
}

point_coord min_distance(point_coord p, point_coord q, point_coord r){
    point_coord min_point1, min_point2;
    point_coord middle_point = find_middle_point(p,q);
    if(distance_pq(p,r)>distance_pq(q,r))
        min_point1 = q;
    else
        min_point1 = p;
    min_point2 = middle_point;
    if(equal_point(min_point1,min_point2)){
        return min_point2;
    }
    else{
        return min_distance(min_point1, min_point2, r);     t t
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
    point_coord pre_AB, pre_CD;
    pre_CD = min_distance(C,D,A);
    pre_AB = min_distance(A,B,pre_CD);
    while(1){
        point_coord cur_CD, cur_AB;
        cur_CD = min_distance(C,D,pre_AB);
        cur_AB = min_distance(A,B,pre_CD);

        cout << "pre_CD : " << pre_CD.x <<endl;
        cout << "pre_CD : " << pre_CD.y <<endl;
        cout << "pre_CD : " << pre_CD.z <<endl;
        cout <<endl;
        cout << "pre_AB : " << pre_AB.x <<endl;
        cout << "pre_AB : " << pre_AB.y <<endl;
        cout << "pre_AB : " << pre_AB.z <<endl;
        cout <<endl;

        if(equal_point(pre_AB,cur_AB) && equal_point(pre_CD,cur_CD)){
            break;
        }
        pre_CD = cur_CD;
        pre_AB = cur_AB;
    }
    if(equal_point(pre_AB,pre_CD)){
        DISTANCE = 0;
    }
    else{
        DISTANCE = distance_pq(pre_CD,pre_AB);
    }
}

void output(){

    cout << DISTANCE << endl;
    cout << ceil(DISTANCE);
}

int main(){
    read_Data();
    solve();
    output();
    return 0;
}
