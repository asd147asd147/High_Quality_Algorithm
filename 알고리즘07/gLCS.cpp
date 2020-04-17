#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

//#define DEBUG

ifstream in("gLCS.inp");
ofstream out("gLCS.out");

string seq1 = " ", seq2 = " ";

int longest_num = 0;

vector <tuple<int,int>> LCS_position;

vector <string> LCS;

void read_data(){
    string temp;
    in >> temp;
    seq1.append(temp);
    in >> temp;
    seq2.append(temp);
}

void find_LCS(string t_s, int num, int t_i, int t_j, int (*DP)[501] ){
    cout << t_s <<endl;
    if(num == 0){
        reverse(t_s.begin(),t_s.end());
        LCS.push_back(t_s);
    }
    else{
        if(DP[t_i-1][t_j-1]==num){
            find_LCS(t_s+seq1[t_i-1],num-1,t_i-1,t_j-1,DP);
        }
        else{
            if(DP[t_i-1][t_j-2]==num){
                find_LCS(t_s+seq1[t_i-1],num-1,t_i-1,t_j-2,DP);
            }
            if(DP[t_i-2][t_j-1]==num){
                find_LCS(t_s+seq1[t_i-2],num-1,t_i-2,t_j-1,DP);
            }
            if(DP[t_i-2][t_j-2]==num){
                find_LCS(t_s+seq1[t_i-2],num-1,t_i-2,t_j-2,DP);
            }
        }

    }
}

int main(){
    read_data();

    int DP[501][501];

    for(int i = 0; i < seq1.size(); i++){
        for(int j = 0; j < seq2.size(); j++){
            DP[i][j] = 0;
        }
    }
    for(int i = 1; i < seq1.size(); i++){
        for(int j = 1; j < seq2.size(); j++){
            if(seq1[i] == seq2[j]){
                if(i > 1 && j == 1){
                    DP[i][j] = max(DP[i-1][j-1]+1,DP[i-2][j-1]+1);
                }
                else if(j > 1 && i == 1){
                    DP[i][j] = max(DP[i-1][j-1]+1,DP[i-1][j-2]+1);
                }
                else if(i == 1 && j == 1){
                    DP[i][j] = 1;
                }
                else{
                    DP[i][j] = max({DP[i-1][j-1]+1,DP[i-1][j-2]+1,DP[i-2][j-1]+1,DP[i-2][j-2]+1});
                }
            }
            else{
                DP[i][j] = max(DP[i][j-1],DP[i-1][j]);
                if(DP[i-1][j]==DP[i][j] || DP[i][j-1]==DP[i][j]){
                    DP[i][j] = 0;
                }
            }
            longest_num = max(longest_num,DP[i][j]);
        }
    }

    for(int i = 1; i < seq1.size(); i++){
        for(int j = 1; j < seq2.size(); j++){
            if(longest_num==DP[i][j]){
                LCS_position.push_back(make_tuple(i,j));
            }
        }
    }

    for(int i = 0; i < LCS_position.size(); i++){
        string temp_s = "";
        int temp_i = get<0>(LCS_position[i]);
        int temp_j = get<1>(LCS_position[i]);
        temp_s=seq1[temp_i];
        find_LCS(temp_s,longest_num-1,temp_i,temp_j,DP);
    }

    sort(LCS.begin(),LCS.end());

    #if defined(DEBUG)
    cout <<" " <<seq2 << endl;
    for(int i = 0; i < seq1.size(); i++){
        cout << seq1[i];
        for(int j = 0; j < seq2.size(); j++){
            cout << "" << DP[i][j];
        }
        cout << endl;
    }

    cout << endl;
    cout << "longest : " << longest_num << endl;
    for(int i = 0; i<LCS_position.size();i++){
        cout << get<0>(LCS_position[i]) << ", " << get<1>(LCS_position[i])<< endl;
    }

    for(auto s : LCS){
        cout << s << endl;
    }
    cout <<endl;

    cout << LCS[0] << endl;

    #endif

    out << LCS[0] << endl;

    return 0;
}
