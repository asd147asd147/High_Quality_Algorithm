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

point_coord optim_point(point_coord p){
    if(abs(p.x - (int)p.x)<GAP){
        p.x = (int)p.x;
    }
    if(abs(p.y - (int)p.y)<GAP){
        p.y = (int)p.y;
    }
    if(abs(p.z - (int)p.z)<GAP){
        p.z = (int)p.z;
    }
    return p;
}

int equal_point(point_coord p, point_coord q){
    if(round(p.x*10000) == round(q.x*10000) && round(p.y*10000) == round(q.y*10000) && round(p.z*10000) == round(q.z*10000)){
        return 1;
    }
    return 0;
}

point_coord find_min_point(point_coord p, point_coord q, point_coord r){
    point_coord temp;
    p = optim_point(p);
    q = optim_point(q);

    if(equal_point(p,q)){
        return p;
    }

    if(distance_pq(p,r)>distance_pq(q,r)){
        temp = find_min_point(q,find_point(p,q,0.5),r);
    }
    else{
        temp =  find_min_point(p,find_point(p,q,0.5),r);
    }

    return temp;
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

point_coord make_vec(point_coord p, point_coord q){
    point_coord temp;
    temp.x = p.x-q.x;
    temp.y = p.y-q.y;
    temp.z = p.z-q.z;
    return temp;
}

point_coord cross_product(point_coord p, point_coord q){
    point_coord temp;
    temp.x = p.y*q.z-p.z*q.y;
    temp.y = p.z*q.x-p.x*q.z;
    temp.z = p.x*q.y-p.y*q.x;
    return temp;
}

int check_vec(point_coord p, point_coord q){
    double temp;
    if(p.x!=0 && q.x!=0){
        if(abs(p.x)>abs(q.x)){
            temp = abs(p.x)/abs(q.x);
            q.x = q.x*temp;
            q.y = q.y*temp;
            q.z = q.z*temp;
            if(p.x*(-1) == q.x && p.y*(-1) == q.y && p.z*(-1) == q.z)
                return 1;
        }
        else{
            temp = abs(q.x)/abs(p.x);
            p.x = p.x*temp;
            p.y = p.y*temp;
            p.z = p.z*temp;
            if(p.x*(-1) == q.x && p.y*(-1) == q.y && p.z*(-1) == q.z)
                return 1;
        }
    }
    else if(p.y!=0 && q.y!=0){
        if(abs(p.y)>abs(q.y)){
            temp = abs(p.y)/abs(q.y);
            q.x = q.x*temp;
            q.y = q.y*temp;
            q.z = q.z*temp;
            if(p.x*(-1) == q.x && p.y*(-1) == q.y && p.z*(-1) == q.z)
                return 1;
        }
        else{
            temp = abs(q.y)/abs(p.y);
            p.x = p.x*temp;
            p.y = p.y*temp;
            p.z = p.z*temp;
            if(p.x*(-1) == q.x && p.y*(-1) == q.y && p.z*(-1) == q.z)
                return 1;
        }
    }
    else if(p.z!=0 && q.z!=0){
        if(abs(p.z)>abs(q.z)){
            temp = abs(p.z)/abs(q.z);
            q.x = q.x*temp;
            q.y = q.y*temp;
            q.z = q.z*temp;
            if(p.x*(-1) == q.x && p.y*(-1) == q.y && p.z*(-1) == q.z)
                return 1;
        }
        else{
            temp = abs(q.z)/abs(p.z);
            p.x = p.x*temp;
            p.y = p.y*temp;
            p.z = p.z*temp;
            if(p.x*(-1) == q.x && p.y*(-1) == q.y && p.z*(-1) == q.z){
                return 1;
            }

        }
    }
    return 0;
}

int ccw(){
    point_coord vec_AB, vec_AC, vec_AD;
    vec_AB = make_vec(B,A);
    vec_AC = make_vec(C,A);
    vec_AD = make_vec(D,A);
    point_coord cross_AB_AC = cross_product(vec_AB,vec_AC);
    point_coord cross_AB_AD = cross_product(vec_AB,vec_AD);

    point_coord vec_CD, vec_CA, vec_CB;
    vec_CD = make_vec(D,C);
    vec_CA = make_vec(A,C);
    vec_CB = make_vec(B,C);
    point_coord cross_CD_CA = cross_product(vec_CD,vec_CA);
    point_coord cross_CD_CB = cross_product(vec_CD,vec_CB);

    if(check_vec(cross_AB_AC,cross_AB_AD) && check_vec(cross_CD_CA,cross_CD_CB)){
        DISTANCE = 0;
        return 1;
    }
    return 0;
}

void solve(){
    if(ccw()){
        cout << "call" <<endl;
        return;
    }
    point_coord min_AB, min_CD, temp_AB, temp_CD;
    min_AB = find_min_point(A,B,C);
    min_CD = find_min_point(C,D,min_AB);
    DISTANCE = min(DISTANCE,distance_pq(min_AB,min_CD));
    while(1){
        temp_AB = find_min_point(A,B,min_CD);
        temp_CD = find_min_point(C,D,min_AB);
        if(distance_pq(temp_AB,temp_CD)>=DISTANCE){
            break;
        }
        else{
            min_AB = temp_AB;
            min_CD = temp_CD;
            DISTANCE = min(DISTANCE,distance_pq(min_AB,min_CD));
        }
    }
    min_AB = find_min_point(A,B,D);
    min_CD = find_min_point(C,D,min_AB);
    DISTANCE = min(DISTANCE,distance_pq(min_AB,min_CD));
    while(1){
        temp_AB = find_min_point(A,B,min_CD);
        temp_CD = find_min_point(C,D,min_AB);
        if(distance_pq(temp_AB,temp_CD)>=DISTANCE){
            break;
        }
        else{
            min_AB = temp_AB;
            min_CD = temp_CD;
            DISTANCE = min(DISTANCE,distance_pq(min_AB,min_CD));
        }
    }
}

void output(){
    cout << DISTANCE<<endl;
    if(DISTANCE < 4.999e-5)
        DISTANCE = 0;
    cout << ceil(DISTANCE);
}

int main(){
    read_Data();
    solve();
    output();
    return 0;
}
