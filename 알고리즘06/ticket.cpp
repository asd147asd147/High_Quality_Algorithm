#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

ifstream in("ticket.inp");
ofstream out("ticket.out");


int s,d,t,w,N;

int TABLE[365] = {0,};
int lastday = 0;

int singleOrDay(int r){
    return min(r*s,d);
}

void read_data(){
    in >> s >> d >> t >> w >> N;
    int t1, t2;

    for(int i = 0 ; i < N; i++){
        in >> t1 >> t2;
        TABLE[t1-1] = t2;
        lastday = max(t1,lastday);
    }
}

void calc_MIN(int* min_table){
    min_table[0] = singleOrDay(TABLE[0]);
    min_table[1] = singleOrDay(TABLE[1])+min_table[0];
    min_table[2] = min(singleOrDay(TABLE[2])+min_table[1],t);
    for(int i = 3; i < lastday; i++){
        if(i%7 == 6){
            if(i == 6){
                min_table[6] = min(min(min_table[i-1]+singleOrDay(TABLE[6]),min_table[i-3]+t),w);
            }
            else{
                min_table[i] = min(min(min_table[i-1]+singleOrDay(TABLE[i]),min_table[i-3]+t),w+min_table[i-7]);
            }

        }
        else{
            min_table[i] = min(min_table[i-1]+singleOrDay(TABLE[i]),min_table[i-3]+t);
        }
    }


}

int main(){
    read_data();
    int MIN_TABLE[lastday] = {0,};
    calc_MIN(MIN_TABLE);
    out << MIN_TABLE[lastday-1] <<endl;
    return 0;
}
