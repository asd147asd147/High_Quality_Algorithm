#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

ifstream in("angle.inp");
ofstream out("angle.out");

int N;


typedef struct _coord{
    int p_num;
    int x;
    int y;

} coord;

vector<vector<coord>> quad;

void input_data(){
    in >> N;
    coord temp;
    vector<coord> quad1;
    vector<coord> quad2;
    vector<coord> quad3;
    vector<coord> quad4;
    for(int i = 1; i <= N; ++i){
        temp.p_num = i;
        in >> temp.x >> temp.y;
        if(temp.x>0 && temp.y>=0){
            quad1.push_back(temp);
        }
        else if(temp.x<=0 && temp.y>0){
            quad2.push_back(temp);
        }
        else if(temp.x<0 && temp.y<=0){
            quad3.push_back(temp);
        }
        else{
            quad4.push_back(temp);
        }
    }
    quad.push_back(quad1);
    quad.push_back(quad2);
    quad.push_back(quad3);
    quad.push_back(quad4);
}

void swap(coord& c1, coord& c2){
    coord temp = c1;
    c1 = c2;
    c2 = temp;
}

inline int signed_area(coord c1, coord c2){
    return c1.x*c2.y-c2.x*c1.y;
}

bool operator>(const coord& c1, const coord& c2){
    if(signed_area(c1,c2) > 0){
        return 0;
    }
    else if(signed_area(c1,c2) < 0){
        return 1;
    }
    else{
        return c1.x*c1.x+c1.y*c1.y > c2.x*c2.x+c2.y*c2.y;
    }
}

bool operator<(const coord& c1, const coord& c2){
    if(signed_area(c1,c2) > 0){
        return 1;
    }
    else if(signed_area(c1,c2) < 0){
        return 0;
    }
    else{
        return c1.x*c1.x+c1.y*c1.y < c2.x*c2.x+c2.y*c2.y;
    }
}

void quick_sort(int q_num, int left, int right){
    if(right <= left) return;
    int i = left;
    int j = right+1;
    int pivot = left;

    while(i<j){
        do{
            i++;
        }while(quad[q_num][pivot] > quad[q_num][i] && i <= right);
        do{
            j--;
        }while(quad[q_num][pivot] < quad[q_num][j] && j >= left+1);

        if(i < j){
            swap(quad[q_num][i],quad[q_num][j]);
        }
    }
    swap(quad[q_num][pivot],quad[q_num][j]);
    quick_sort(q_num,left,j-1);
    quick_sort(q_num,j+1,right);
}

void output_data(){
    for(auto s : quad)
        for(auto t : s)
            out << t.p_num << endl;
}

int main() {
    input_data();
    for(int i = 0; i < 4; i++)
        quick_sort(i,0,quad[i].size()-1);
    output_data();

    return 0;
}
