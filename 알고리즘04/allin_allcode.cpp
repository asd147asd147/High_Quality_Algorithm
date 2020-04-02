#include <iostream>
#include <fstream>
using namespace std;
ifstream I("test.inp");
ofstream O("allin.out");
int main(){
    int N;
    int Mp = 0;
    int mp;
    int temp;
    int p;
    int buy = 1;
    int tbuy;
    int sell;
    int tmp;
    I>>N>>mp;
    for(int i = 1; i < N; ++i){
        I>>temp;
        p = temp - mp;
        if(p>=Mp && Mp+tmp!=temp){
            Mp=p;
            buy = tbuy;
            tmp = mp;
            sell = i+1;
        }
        if(mp>=temp){
            mp=temp;
            tbuy=i+1;
        }
    }
    O <<buy<<" "<<sell;
    return 0;
}
