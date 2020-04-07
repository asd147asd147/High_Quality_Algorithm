#include "oil.h"
#include <algorithm>
#include <iostream>

using namespace std;

int B,E;

void find_oil(int b, int e, int flag){
    int m = (b+e)/2;
    int first, second;
    if(flag == 0){
        first = observe(b,m);
        second = observe(m+1,e);
    }
    else if(flag == 1){
        second = observe(m+1,e);
        if(second == 0){
            if(b == m)
                first = 1;
            else
                first = observe(b,m);
        }
        else{
            first = 1;
        }
    }
    else if(flag == 2){
        first = observe(b,m);
        if(first == 0){
            if(m+1 == e)
                second = 1;
            else
                second = observe(m+1,e);
        }
        else{
            second = 1;
        }
    }
    cout << b << " " << e <<endl;
    cout << "f" << first << endl;
    cout << "s" << second << endl;
    cout << flag <<endl;
    cout << endl;

    if(first == 0){
        if(second == 1){
            B = min(B,m+1);
            E = max(E,e);
        }
        else if(second == 2){
            find_oil(m+1,e,0);
        }
    }
    else if(first == 1){
        if(second == 0){
            B = min(B,b);
            E = max(E,m);
        }
        else if(second == 1){
            B = min(B,b);
            E = max(E,e);
        }
        else if(second == 2){
            find_oil(m+1,e,1);
            B = min(B,b);
        }
    }
    else if(first == 2){
        if(second == 0){
            find_oil(b,m,0);
        }
        else if(second == 1){
            find_oil(b,m,2);
            E = max(E,e);
        }
        else if(second == 2){
            find_oil(b,m,2);
            find_oil(m+1,e,1);
        }
    }
}

int main(){
    initial();
    int N = oil_size()-1;
    B = N;
    E = 0;
    find_oil(0,N,0);
    oil_report(B,E);
    return 0;
}
