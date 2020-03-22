#include <bits/stdc++.h>
using namespace std;

// epsilon 값
const double GAP = 0.0001;

vector < double > A(3);
vector < double > B(3);
vector < double > P(3);
double ans = 1e9;
double calc(vector < double >& P1, vector < double >& P2) {
    double ret = 0;
    for(int i=0; i<3; i++) {
        ret += (P1[i] - P2[i]) * (P1[i] - P2[i]);
    }
    return ret;
}

double search(double lo, double hi) {

    double t = (lo+hi)/2;
    vector < double > tt(3);

    double tohi = t + GAP;
    double tolo = t - GAP;
    cout << tohi <<endl;
    for(int i=0; i<3; i++) {
        tt[i] = t * A[i] + (1-t) * B[i];
    }
    ans = min(ans,calc(P,tt));

    // 탐색 종료 조건
    if(lo + GAP >= hi) {
        return ans;
    }

    // 현재 t에서 epsilon만큼 A방향으로 이동하여 거리 계산
    for(int i=0; i<3; i++) {
        tt[i] = tolo * A[i] + (1-tolo) * B[i];
    }
    double loans = calc(P,tt);
    ans = min(ans,loans);

    // 현재 t에서 epsilon만큼 B방향으로 이동하여 거리 계산
    for(int i=0; i<3; i++) {
        tt[i] = tohi * A[i] + (1-tohi) * B[i];
    }
    double hians = calc(P,tt);
    ans = min(ans,hians);

    // 거리가 줄어드는 쪽으로 이진 탐색 실행
    if(loans > hians) {
        ans = min(ans,search(t,hi));
    }
    else {
        ans = min(ans,search(lo,t));
    }

    return ans;
}

int main() {
    ifstream in("1.inp");
    ofstream out("test.out");
	for(int i=0; i<3; i++) {
        in >> A[i];
    }
    for(int i=0; i<3; i++) {
        in >> B[i];
    }
    for(int i=0; i<3; i++) {
        in >> P[i];
    }
    cout << ceil(sqrt(search(0,1)));
    return 0;
}
