#include <fstream>
std::ifstream I("allin.inp");std::ofstream O("allin.out");int main(){int N,m,t,B,s,T,i=1,M=0,b=1;I>>N>>m;for(;i<N;++i){I>>t;if(t-m>=M&&M+T!=t)M=t-(T=m),b=B,s=i+1;if(m>=t)m=t,B=i+1;}O<<b<<' '<<s;return 0;}
