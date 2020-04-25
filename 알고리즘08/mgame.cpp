#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

//#define debug

ifstream in("mgame.inp");
ofstream out("mgame.out");

string expression;

vector <int> operand;
vector <char> opcode;

void read_data(){
    in >> expression;
    for(int i = 0; i < expression.size();i+=2){
        operand.push_back(expression[i]-'0');
        opcode.push_back(expression[i+1]);
    }
    opcode.erase(opcode.begin()+opcode.size()-1);
}

int main(){
    read_data();

    int DP_max[operand.size()-1][operand.size()-1];
    int DP_min[operand.size()-1][operand.size()-1];

    for(int i = 0; i < operand.size()-1; i++){
        for(int j = 0; j < operand.size()-1; j++){
            DP_max[i][j] = DP_min[i][j] = 0;
        }
    }
    for(int i = 0; i < operand.size()-1; i++){
        switch(opcode[i]){
        case '+':
            DP_max[i][i] = DP_min[i][i] = operand[i] + operand [i+1];
            break;
        case '-':
            DP_max[i][i] = DP_min[i][i] = operand[i] - operand [i+1];
            break;
        case '*':
            DP_max[i][i] = DP_min[i][i] = operand[i] * operand [i+1];
            break;
        }
    }

    for(int i = 0; i < opcode.size()-1;i++){
        switch(opcode[i+1]){
        case '+':
            DP_max[i][i+1] = DP_max[i][i] + operand[i+2];
            DP_min[i][i+1] = DP_min[i][i] + operand[i+2];
            break;
        case '-':
            DP_max[i][i+1] = DP_max[i][i] - operand[i+2];
            DP_min[i][i+1] = DP_min[i][i] - operand[i+2];
            break;
        case '*':
            DP_max[i][i+1] = DP_max[i][i]*operand[i+2];
            DP_min[i][i+1] = DP_min[i][i]*operand[i+2];
            break;
        }

        switch(opcode[i]){
        case '+':
            DP_max[i][i+1] = max(DP_max[i][i+1],operand[i] + DP_max[i+1][i+1]);
            DP_min[i][i+1] = min(DP_min[i][i+1],operand[i] + DP_min[i+1][i+1]);
            break;
        case '-':
            DP_max[i][i+1] = max({operand[i] - DP_max[i+1][i+1], operand[i] - DP_min[i+1][i+1],DP_max[i][i+1]});
            DP_min[i][i+1] = min({operand[i] - DP_max[i+1][i+1], operand[i] - DP_min[i+1][i+1],DP_min[i][i+1]});
            break;
        case '*':
            DP_max[i][i+1] = max(DP_max[i][i+1],operand[i]*DP_max[i+1][i+1]);
            DP_min[i][i+1] = min(DP_min[i][i+1],operand[i]*DP_min[i+1][i+1]);
            break;
        }
    }

    for(int i = 0; i < opcode.size()-2;i++){
        for(int j = 0; j < opcode.size()-2-i;j++){
            switch(opcode[i+j+2]){
            case '+':
                DP_max[j][i+j+2] = DP_max[j][i+j+1] + operand[i+j+3];
                DP_min[j][i+j+2] = DP_min[j][i+j+1] + operand[i+j+3];
                break;
            case '-':
                DP_max[j][i+j+2] = DP_max[j][i+j+1] - operand[i+j+3];
                DP_min[j][i+j+2] = DP_min[j][i+j+1] - operand[i+j+3];
                break;
            case '*':
                DP_max[j][i+j+2] = DP_max[j][i+j+1]*operand[i+j+3];
                DP_min[j][i+j+2] = DP_min[j][i+j+1]*operand[i+j+3];
                break;
            }

            switch(opcode[j]){
            case '+':
                DP_max[j][i+j+2] = max(DP_max[j][i+j+2],DP_max[j+1][i+j+2] + operand[j]);
                DP_min[j][i+j+2] = min(DP_min[j][i+j+2],DP_min[j+1][i+j+2] + operand[j]);
                break;
            case '-':
                DP_max[j][i+j+2] = max({operand[j]-DP_max[j+1][i+j+2],operand[j]-DP_min[j+1][i+j+2],DP_max[j][i+j+2]});
                DP_min[j][i+j+2] = min({operand[j]-DP_max[j+1][i+j+2],operand[j]-DP_min[j+1][i+j+2],DP_min[j][i+j+2]});
                break;
            case '*':
                DP_max[j][i+j+2] = max(DP_max[j][i+j+2],DP_max[j+1][i+j+2]*operand[j]);
                DP_min[j][i+j+2] = min(DP_min[j][i+j+2],DP_min[j+1][i+j+2]*operand[j]);
                break;
            }

            for(int k = 0,m = j+1; k < i+1 ; k++,m++){
                switch(opcode[m]){
                case '+':
                    DP_max[j][i+j+2] = max(DP_max[j][i+j+2],DP_max[j][j+k] + DP_max[j+2+k][i+j+2]);
                    DP_min[j][i+j+2] = min(DP_min[j][i+j+2],DP_min[j][j+k] + DP_min[j+2+k][i+j+2]);
                    break;
                case '-':
                    DP_max[j][i+j+2] = max(DP_max[j][j+k] - DP_min[j+2+k][i+j+2],DP_max[j][i+j+2]);
                    DP_min[j][i+j+2] = min(DP_min[j][j+k] - DP_max[j+2+k][i+j+2],DP_min[j][i+j+2]);
                    break;
                case '*':
                    DP_max[j][i+j+2] = max({DP_max[j][i+j+2],DP_max[j][j+k]*DP_max[j+2+k][i+j+2],DP_min[j][j+k]*DP_min[j+2+k][i+j+2]});
                    DP_min[j][i+j+2] = min({DP_min[j][i+j+2],DP_min[j][j+k]*DP_max[j+2+k][i+j+2],DP_max[j][j+k]*DP_min[j+2+k][i+j+2]});
                    break;
                }
            }
        }
    }


    #ifdef debug

    for(int i = 0; i < operand.size()-1; i++){
        for(int j = 0; j < operand.size()-1; j++){
            cout << DP_max[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    for(int i = 0; i < operand.size()-1; i++){
        for(int j = 0; j < operand.size()-1; j++){
            cout << DP_min[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    for(auto s : operand)
        cout << s << " ";
    cout << endl;
    for(auto s : opcode)
        cout << s << " ";
    cout << endl;
    cout << DP_max[0][operand.size()-2] << endl;
    #endif // debug

    out << DP_max[0][operand.size()-2];
    return 0;
}
