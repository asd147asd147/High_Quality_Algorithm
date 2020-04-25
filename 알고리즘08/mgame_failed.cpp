#include <iostream>
#include <stdio.h>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

#define DEBUG
#define len 32

ifstream in("1.inp");
ofstream out("mgame.out");

string expression;

struct mgame_sum{
    int min_sum = 0;
    int max_sum = 0;
};

int OPNUM = 0;

void read_data(){
    in >> expression;
    OPNUM = expression.size()/2;
}

int main(){
    read_data();

    int DP_min[OPNUM][OPNUM] = {0};
    int DP_max[OPNUM][OPNUM] = {0};

    for(int i = 0; i < OPNUM; i++){
        for(int j = 0; j < OPNUM; j++){
            DP_min[i][j] = DP_max[i][j] = 0;
        }
    }

    for(int i = 1; i < expression.size()-1; i+=2){
        switch(expression[i]){
        case '*':
            DP_min[(i-1)/2][(i-1)/2] = DP_max[(i-1)/2][(i-1)/2] = (expression[i-1]-'0')*(expression[i+1]-'0');
            break;
        case '+':
            DP_min[(i-1)/2][(i-1)/2] = DP_max[(i-1)/2][(i-1)/2] = (expression[i-1]-'0')+(expression[i+1]-'0');
            break;
        case '-':
            DP_min[(i-1)/2][(i-1)/2] = DP_max[(i-1)/2][(i-1)/2] = (expression[i-1]-'0')-(expression[i+1]-'0');
            break;
        }
    }

    for(int i = 1; i < OPNUM; i++){
        for(int j = 0; j < OPNUM-i; j++){
            char lop = expression[2*j+1];
            char rop = expression[2*(j+i)+1];

            switch(lop){
            case '*':
                DP_max[j][j+i] = max((expression[2*j]-'0')*DP_max[j+1][j+i],(expression[2*j]-'0')*DP_min[j+1][j+i]);
                DP_min[j][j+i] = min((expression[2*j]-'0')*DP_min[j+1][j+i],(expression[2*j]-'0')*DP_max[j+1][j+i]);
                break;
            case '+':
                DP_max[j][j+i] = max((expression[2*j]-'0')+DP_max[j+1][j+i],(expression[2*j]-'0')+DP_min[j+1][j+i]);
                DP_min[j][j+i] = min((expression[2*j]-'0')+DP_max[j+1][j+i],(expression[2*j]-'0')+DP_min[j+1][j+i]);
                break;
            case '-':
                DP_max[j][j+i] = max((expression[2*j]-'0')-DP_max[j+1][j+i],(expression[2*j]-'0')-DP_min[j+1][j+i]);
                DP_min[j][j+i] = min((expression[2*j]-'0')-DP_max[j+1][j+i],(expression[2*j]-'0')-DP_min[j+1][j+i]);
                break;
            }

            switch(rop){
            case '*':
                DP_max[j][j+i] = max({DP_max[j][j+i-1]*(expression[2*(j+i)+2]-'0'), DP_min[j][j+i-1]*(expression[2*(j+i)+2]-'0'),DP_max[j][j+i]});
                DP_min[j][j+i] = min({DP_min[j][j+i-1]*(expression[2*(j+i)+2]-'0'), DP_min[j][j+i-1]*(expression[2*(j+i)+2]-'0'),DP_min[j][j+i]});
                break;
            case '+':
                DP_max[j][j+i] = max({DP_max[j][j+i-1]+(expression[2*(j+i)+2]-'0'),DP_min[j][j+i-1]+(expression[2*(j+i)+2]-'0'),DP_max[j][j+i]});
                DP_min[j][j+i] = min({DP_min[j][j+i-1]+(expression[2*(j+i)+2]-'0'),DP_max[j][j+i-1]+(expression[2*(j+i)+2]-'0'),DP_min[j][j+i]});
                break;
            case '-':
                DP_max[j][j+i] = max({DP_max[j][j+i-1]-(expression[2*(j+i)+2]-'0'),DP_min[j][j+i-1]-(expression[2*(j+i)+2]-'0'),DP_max[j][j+i]});
                DP_min[j][j+i] = min({DP_min[j][j+i-1]-(expression[2*(j+i)+2]-'0'),DP_max[j][j+i-1]-(expression[2*(j+i)+2]-'0'),DP_min[j][j+i]});
                break;
            }

            if(i+j > 1 && j < OPNUM-(i+j)){
                char mop = expression[2*((i+i+j)/2)+1];
                cout << mop << endl;
                cout << j << " " << i+j << endl;
            }
        }
    }

    #ifdef DEBUG

    cout << expression << endl;

    cout << OPNUM << endl;

    cout << endl;

    for(int i = 0; i < OPNUM; i++){
        for(int j = 0; j < OPNUM; j++){
            cout << DP_max[i][j] << " ";
        }
        cout << endl;
    }
    cout <<endl;
    for(int i = 0; i < OPNUM; i++){
        for(int j = 0; j < OPNUM; j++){
            cout << DP_min[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << DP_max[0][OPNUM-1] << endl;
    printf("this : %d",DP_max[0][OPNUM-1]);
    #endif // DEBUG

    out << DP_max[0][OPNUM-1];

    return 0;
}
