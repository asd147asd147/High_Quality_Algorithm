#include <iostream>
#include <fstream>

using namespace std;

ifstream in("cards.in");
ofstream out("cards.out");

int MAX_NUM;
int SUM_NUM;

void input(){
    in >> MAX_NUM;
    SUM_NUM = MAX_NUM*(MAX_NUM+1)/2;
}

void solve(){
    int input_num;
    for(int i = 0; i < MAX_NUM - 2; ++i){
        in >> input_num;
        SUM_NUM -= input_num;
    }
    int find_num1 = SUM_NUM/2;
    int sum_num1 = find_num1*(find_num1+1)/2;
    in.seekg(0L,ios::beg);
    in >> input_num;
    for(int i = 0; i < MAX_NUM - 2; ++i){
        in >> input_num;
        if(input_num <= find_num1){
            sum_num1 -= input_num;
        }
    }
    out << sum_num1 << endl;
    out << SUM_NUM - sum_num1;
}

int main(){
    input();
    solve();
    return 0;
}
