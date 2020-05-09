#include <iostream>
#include <fstream>
#include <string.h>
#include <bitset>

std::ifstream in("test.inp");
std::ofstream out("detroit.out");

typedef struct _position{
    int x = 0;
    int y = 0;
} position;

int main(){
    int N;
    in >> N;
    int pizza[N][N];
    int col_data[N];
    int row_data[N];
    position position_pair[N*N];
    memset(pizza,0,sizeof(pizza));
    memset(row_data,0,sizeof(row_data));
    memset(col_data,0,sizeof(col_data));
    int topping;
    int pair_size = 0;
    int i,j;
    position temp_position;
    for(i = 0; i < N; ++i){
        for(j = 0; j < N; ++j){
            in >> topping;
            if(topping){
                topping = 1 << topping-1;
                if( (row_data[i] | col_data[j]) & topping){
                    out << 0;
                    return 0;
                }
                else{
                    pizza[i][j] = topping;
                    row_data[i] |= topping;
                    col_data[j] |= topping;
                }
            }
            else{
                temp_position.x = j;
                temp_position.y = i;
                position_pair[pair_size++] = {j,i};
            }
        }
    }
    if(!pair_size){
        out << 1;
        return 0;
    }
    int mask = 1;
    int position_index = 0;
    int m,n;
    int likelihood = 0;
    int max = 1 << N;
    int NUM = 0;
    init:
        m = position_pair[position_index].y;
        n = position_pair[position_index].x;
        likelihood = row_data[m] | col_data[n];
        if(pizza[m][n]){
            row_data[m] &= ~pizza[m][n];
            col_data[n] &= ~pizza[m][n];
            mask = pizza[m][n] << 1;
            pizza[m][n] = 0;
        }
        if(!(likelihood^0x1FF))
            goto reset;
        for(; mask < max; mask <<= 1){
            if(std::bitset<9>(mask & likelihood) == 0){
                pizza[m][n] = mask;
                row_data[m] |= mask;
                col_data[n] |= mask;
                ++position_index;
                mask = 1;
                if(position_index == pair_size){
                    ++NUM;
                    --position_index;
                    goto init;
                }
                goto init;
            }
        }
        --position_index;
        if(position_index == -1){
            out << NUM;
            return 0;
        }
        goto init;
    reset:
        row_data[m] &= ~pizza[m][n];
        col_data[n] &= ~pizza[m][n];
        pizza[m][n] = 0;
        --position_index;
        if(position_index == -1){
            out << NUM;
            return 0;
        };
        goto init;
    return 0;
}
