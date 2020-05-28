
#include <fstream>
#include <algorithm>

using namespace std;

ifstream in("diet.inp");
ofstream out("diet.out");

struct _m{
    int mp=0,mf=0,ms=0,mv=0;
};

typedef struct _nutr{
    int index, cost = 0;
    struct _m m;
} nutr;

struct _optimal{
    int index[30] = {0};
    int m_sum = 0;
    int i = 0;
    int min_cost = 0;
} optimal;

struct _data{
    int index[30] = {0};
    int i = 0;
    int cost = 0;
    struct _m m;
};

int N;
nutr diet[31];

bool compare(nutr& n1, nutr& n2){
    if(n1.cost < n2.cost){
        return 1;
    }
    return 0;
}

inline void input_data(){
    in >> N;
    in >> diet[0].m.mp >> diet[0].m.mf >> diet[0].m.ms >> diet[0].m.mv;
    for(int i = 1; i <= N; ++i){
        diet[i].index = i;
        in >> diet[i].m.mp >> diet[i].m.mf >> diet[i].m.ms >> diet[i].m.mv >> diet[i].cost;
    }
    sort(diet+1,diet+N+1,compare);
}

inline bool check_min_nutr(struct _m& m){
    return m.mp >= diet[0].m.mp && m.mf >= diet[0].m.mf && m.ms >= diet[0].m.ms && m.mv >= diet[0].m.mv;
}

inline void init_optimal(){
    struct _m temp_m;
    int i;
    for(i = 1; !check_min_nutr(temp_m); ++i){
        optimal.index[i-1] = diet[i].index;
        temp_m.mp += diet[i].m.mp;
        temp_m.mf += diet[i].m.mf;
        temp_m.ms += diet[i].m.ms;
        temp_m.mv += diet[i].m.mv;
        optimal.min_cost += diet[i].cost;
    }
    optimal.i = i-1;
    optimal.m_sum = temp_m.mp + temp_m.mf + temp_m.ms + temp_m.mv;
}

void find_optimal(struct _data pre_nutr_data, int next_index, int check){
    if(check && check_min_nutr(pre_nutr_data.m)){
        int temp_sum = pre_nutr_data.m.mp + pre_nutr_data.m.mf + pre_nutr_data.m.ms + pre_nutr_data.m.mv;
        if(pre_nutr_data.cost != optimal.min_cost){
            copy(pre_nutr_data.index,pre_nutr_data.index+pre_nutr_data.i,optimal.index);
            optimal.min_cost = pre_nutr_data.cost;
            optimal.m_sum = temp_sum;
            optimal.i = pre_nutr_data.i;
        }
        else{
            if(temp_sum > optimal.m_sum){
                copy(pre_nutr_data.index,pre_nutr_data.index+pre_nutr_data.i,optimal.index);
                optimal.i = pre_nutr_data.i;
                optimal.m_sum = temp_sum;
            }
            else if(temp_sum == optimal.m_sum){
                sort(pre_nutr_data.index,pre_nutr_data.index+pre_nutr_data.i);
                sort(optimal.index,optimal.index+optimal.i);
                int mini = min(pre_nutr_data.i,optimal.i);
                for(int i = 0; i < mini; ++i){
                    if(pre_nutr_data.index[i] < optimal.index[i]){
                        copy(pre_nutr_data.index,pre_nutr_data.index+pre_nutr_data.i,optimal.index);
                        optimal.i = pre_nutr_data.i;
                    }
                }
            }
        }
    }
    else{
        if(next_index == N+1){
            return;
        }
        find_optimal(pre_nutr_data,next_index+1,0);

        pre_nutr_data.index[pre_nutr_data.i++] = diet[next_index].index;
        pre_nutr_data.cost += diet[next_index].cost;
        pre_nutr_data.m.mp += diet[next_index].m.mp;
        pre_nutr_data.m.mf += diet[next_index].m.mf;
        pre_nutr_data.m.ms += diet[next_index].m.ms;
        pre_nutr_data.m.mv += diet[next_index].m.mv;
        if(pre_nutr_data.cost <= optimal.min_cost)
            find_optimal(pre_nutr_data,next_index+1,1);
    }
}

inline void output_data(){
    sort(optimal.index,optimal.index+optimal.i);
    for(int i = 0 ; i < optimal.i; i++){
        out << optimal.index[i] <<" ";
    }
}

int main(){
    input_data();
    init_optimal();
    struct _data data;
    find_optimal(data,1,0);
    output_data();
    return 0;
}
