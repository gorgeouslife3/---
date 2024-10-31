#include<bits/stdc++.h>
    
#define LL long long
    
#define int long long

#define _ 0
    
using namespace std;
    
/*Grievous Lady*/
    
template <typename _n_> void mian(_n_ & _x_){
    _x_ = 0;int _m_ = 1;char buf_ = getchar();
    while(buf_ < '0' || buf_ > '9'){if(buf_ == '-')_m_ =- 1;buf_ = getchar();}
    do{_x_ = _x_ * 10 + buf_ - '0';buf_ = getchar();}while(buf_ >= '0' && buf_ <= '9');_x_ *= _m_;
}
    
unordered_map<int , int> dp[2];

int n , m , endx , endy , mp[101][101];

char c;

inline int oqs(int x , int y){
    return x << (y << 1);
}

inline int DP(){
    int tmp = (1 << ((m + 1) << 1)) - 1;
    int numnow = 0 , numnxt = 1;
    dp[numnow][0] = 1;
    for(int i = 1;i <= n;i ++){
        for(int j = 1;j <= m;j ++){
            dp[numnxt].clear();
            for(auto k = dp[numnow].begin(); k != dp[numnow].end(); k ++){
                int S = k -> first , val = k -> second;
                int L = (S >> ((j - 1) << 1)) & 3 , R = (S >> (j << 1)) & 3;
                if(!mp[i][j]){ 
                    if(!L && !R) dp[numnxt][S] += val;
                    continue;
                }
                if(!L && !R){
                    if(mp[i][j + 1] && mp[i + 1][j]) dp[numnxt][S ^ oqs(1 , j - 1) ^ oqs(2 , j)] += val;
                }
                if(!L && R){
                    if(mp[i][j + 1]) dp[numnxt][S] += val;
                    if(mp[i + 1][j]) dp[numnxt][S ^ oqs(R , j) ^ oqs(R , j - 1)] += val;
                }
                if(L && !R){
                    if(mp[i][j + 1]) dp[numnxt][S ^ oqs(L , j - 1) ^ oqs(L , j)] += val;
                    if(mp[i + 1][j]) dp[numnxt][S] += val;
                }
                if(L == R){
                    if(L == 1 && R == 1){
                        int nowar = 0;
                        for(int p = j ; ; p ++){
                            int dou = (S >> (p << 1)) & 3;
                            if(dou == 1) nowar ++;
                            if(dou == 2) nowar --;
                            if(nowar == 0){
                                dp[numnxt][S ^ oqs(L , j - 1) ^ oqs(R , j) ^ oqs(2 , p) ^ oqs(1 , p)] += val;
                                break;
                            }
                        }
                    }
                    if(L == 2 && R == 2){
                        int nowar = 0;
                        for(int p = j - 1; ; p --){
                            int dou = (S >> (p << 1)) & 3;
                            if(dou == 2) nowar ++;
                            if(dou == 1) nowar --;
                            if(nowar == 0){
                                dp[numnxt][S ^ oqs(L , j - 1) ^ oqs(R , j) ^ oqs(1 , p) ^ oqs(2 , p)] += val;
                                break;
                            }
                        }
                    }
                }
                if(L == 2 && R == 1){
                    dp[numnxt][S ^ oqs(L , j - 1) ^ oqs(R , j)] += val;
                }
                if(L == 1 && R == 2 && i == endx && j == endy){ return val; }
            }
            swap(numnow , numnxt);
        }
        dp[numnxt].clear();
        for(auto k = dp[numnow].begin(); k != dp[numnow].end(); k ++){
            dp[numnxt][(k -> first << 2) & tmp] += k -> second;
        }
        swap(numnxt , numnow);
    }
    return 0;
}

inline int Ame_(){
    mian(n) , mian(m);
    for(int i = 1;i <= n;i ++){
        for(int j = 1;j <= m;j ++){
            cin >> c;
            if(c == '*') mp[i][j] = 0;
            else if(c == '.') mp[i][j] = 1 , endx = i , endy = j;
        }
    }
    printf("%lld\n" , DP());
    return ~~(0^_^0);
}
    
int Ame__ = Ame_();
    
signed main(){;