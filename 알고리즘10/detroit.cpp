#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

//#define debug

ifstream in("detroit.inp");
ofstream out("detroit.out");

int L;
int k;
int min_unit = 0;

vector <int> unit;

void read_data(){
    in >> L >> k;
    int t;
    for(int i=0; i<k; i++){
        in >> t;
        unit.push_back(t);
    }
    reverse(unit.begin(),unit.end());
}

int main(){
    read_data();

    stack <int> tube;
    int sub_sum = unit[0];
    tube.push(0);

    while(sub_sum!=L){
        for(int i = tube.top(); i < k; i++){
            if(sub_sum+unit[i] <= L){
                sub_sum += unit[i];
                tube.push(i);
                break;
            }
            if(i == k-1){
                while(!tube.empty()){
                    int temp = tube.top()+1;
                    if(temp == k){
                        sub_sum -= unit[tube.top()];
                        tube.pop();
                    }
                    else{
                        sub_sum -= unit[tube.top()];
                        tube.pop();
                        sub_sum += unit[temp];
                        tube.push(temp);
                        break;
                    }
                }
                if(tube.empty()){
                    out << 0;
                    return 0;
                }
            }
        }
    }

    out << tube.size();

    return 0;
}
