#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

ifstream in("1.inp");
ofstream out("marathon.out");

int BUCKET_NUM;
int BUCKET_V[6];//capacity
int BUCKET_G[6];//goal
int check = 0;

typedef struct _state{
    int num = 0;
    int bucket_state[6];
} state;

set<int> memo;
queue<state> bucket_q;

state root_state;

void input_data(){
    in >> BUCKET_NUM;
    for(int i = 0; i < BUCKET_NUM; ++i){
        in >> BUCKET_V[i];
    }
    for(int i = 0; i < BUCKET_NUM; ++i){
        in >> root_state.bucket_state[i];
    }
    for(int i = 0; i < BUCKET_NUM; ++i){
        in >> BUCKET_G[i];
    }
}

int convert_state_to_int(int* temp_bucket){
    int res = 0;
    for(int i = 0; i < BUCKET_NUM; ++i){
        res*=10;
        res += temp_bucket[i];
    }
    return res;
}

int check_bucket(int index, int* temp_bucket){
    if(temp_bucket[index] == 0){
        return 0; //empty
    }
    else if(temp_bucket[index]==BUCKET_V[index]){
        return -1; //full
    }
    return 1;
}

bool goal(int* temp_bucket){
    for(int i = 0; i < BUCKET_NUM; ++i){
        if(temp_bucket[i] != BUCKET_G[i])
            return 0;
    }
    return 1;
}

void next_state(state cur_state){
    int bucket_state[6] = {0};
    for(int i = 0; i < BUCKET_NUM; ++i){
        bucket_state[i] = check_bucket(i,cur_state.bucket_state);
    }
    for(int i = 0; i < BUCKET_NUM; ++i){
        if(bucket_state[i] == 0)
            continue;
        for(int j = 0; j < BUCKET_NUM; ++j){
            if(j==i || bucket_state[j] == -1)
                continue;
            state t_state = cur_state;
            t_state.num++;
            t_state.bucket_state[j] = t_state.bucket_state[j] + t_state.bucket_state[i];
            t_state.bucket_state[i] = 0;
            if(t_state.bucket_state[j]>BUCKET_V[j]){
                t_state.bucket_state[i] = t_state.bucket_state[j] - BUCKET_V[j];
                t_state.bucket_state[j] = BUCKET_V[j];
            }
            if(memo.find(convert_state_to_int(t_state.bucket_state))==memo.end()){
                memo.insert(convert_state_to_int(t_state.bucket_state));
                bucket_q.push(t_state);
            }
            if(goal(t_state.bucket_state)){
                out << t_state.num;
                check = 1;
                return;
            }
        }
    }
}
//
//void output_data(){
//    for(int i = 0; i < BUCKET_NUM; ++i){
//        cout << BUCKET_V[i] << " ";
//    }
//    cout <<endl;
//    for(int i = 0; i < BUCKET_NUM; ++i){
//        cout << root_state.bucket_state[i] << " ";
//    }
//    cout <<endl;
//    for(int i = 0; i < BUCKET_NUM; ++i){
//        cout << BUCKET_G[i] << " ";
//    }
//    cout <<endl;
//}

int main(){
    input_data();
    bucket_q.push(root_state);
    memo.insert(convert_state_to_int(root_state.bucket_state));
    while(!bucket_q.empty() && !check){
        next_state(bucket_q.front());
        bucket_q.pop();
    }
    if(!check){
        out << 0;
    }
    return 0;
}
