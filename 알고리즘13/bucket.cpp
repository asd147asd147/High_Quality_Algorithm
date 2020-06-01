#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>

using namespace std;

ifstream in("1.inp");
ofstream out("bucket.out");

int BUCKET_NUM;
int* BUCKET_V;
int* BUCKET_I;
int* BUCKET_G;

void input_data(){
    in >> BUCKET_NUM;
    BUCKET_V = new int[BUCKET_NUM];
    BUCKET_I = new int[BUCKET_NUM];
    BUCKET_G = new int[BUCKET_NUM];
    memset(BUCKET_V,0,sizeof(BUCKET_V));
    memset(BUCKET_I,0,sizeof(BUCKET_I));
    memset(BUCKET_G,0,sizeof(BUCKET_G));
    for(int i = 0; i < BUCKET_NUM; ++i){
        in >> BUCKET_V[i];
    }
    for(int i = 0; i < BUCKET_NUM; ++i){
        in >> BUCKET_I[i];
    }
    for(int i = 0; i < BUCKET_NUM; ++i){
        in >> BUCKET_G[i];
    }

}

void output_data(){
    for(int i = 0; i < BUCKET_NUM; ++i){
        cout << BUCKET_V[i] << " ";
    }
    cout <<endl;
    for(int i = 0; i < BUCKET_NUM; ++i){
        cout << BUCKET_I[i] << " ";
    }
    cout <<endl;
    for(int i = 0; i < BUCKET_NUM; ++i){
        cout << BUCKET_G[i] << " ";
    }
    cout <<endl;
}

int main(){
    input_data();
    output_data();
    return 0;
}
