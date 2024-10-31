#include<bits/stdc++.h>

#define FOR(x,y,z) for(int x=y,x##_=z;x<=x##_;x++)
#define DOR(x,y,z) for(int x=y,x##_=z;x>=x##_;x--)
#define FOR_(x,y,z,s) for(int x=y;x<=z;x+=s)
#define FOR__(x,y,z,s) for(int x=y,x##_=z;x<=x##_;x+=s)
#define EOR(x,y) for(int x##_=head[x],y=edge[x##_].e;x##_;y=edge[x##_=edge[x##_].to].e)
#define EGOR(x,y,z) for(int x##_=head[x],y=edge[x##_].e,z=edge[x##_].c;x##_;y=edge[x##_=edge[x##_].to].e,z=edge[x##_].c)

#define clr(x,y) memset(x,y,sizeof(x))
#define szf(x) sizeof(x)
#define min3(x,y,z) min(min(x,y),z)
#define max3(x,y,z) max(max(x,y),z)

#define read2(x,y) read(x),read(y)
#define read3(x,y,z) read(x),read(y),read(z)
#define read4(x,y,z,w) read3(x,y,z),read(w)
#define reads(str) sf("%s",str)

#define ts (*this)
#define sf scanf
#define pf printf

#define ll long long
#define ull unsigned long long
#define db double
#define ct clock_t
#define ck() clock()


using namespace std;

template<class T>bool tomin(T &x,T y){return x>y?x=y,1:0;}
template<class T>bool tomax(T &x,T y){return x<y?x=y,1:0;}
template<class T>void read(T &x){
    char c;
    x=0;
    int f=1;
    while(c=getchar(),c<'0'||c>'9')if(c=='-')f=-1;
    do x=(x<<3)+(x<<1)+(c^48);
    while(c=getchar(),c>='0'&&c<='9');
    x*=f;
}

const db Pi=acos(-1);
const int maxn=2e5+5;
int n,m;
int to[maxn];
namespace LCT{
    int ch[maxn][2],fa[maxn];
    bool isrt(int x){return x==ch[fa[x]][0]||x==ch[fa[x]][1];}
    void rotate(int x){
        int y=fa[x],z=fa[y];
        bool k=ch[y][1]==x;
        if(isrt(y))ch[z][ch[z][1]==y]=x;fa[x]=z;
        ch[y][k]=ch[x][k^1];if(ch[x][k^1])fa[ch[x][k^1]]=y;
        ch[x][k^1]=y;fa[y]=x;
    }
    void splay(int x){
        while(isrt(x)){
            int y=fa[x],z=fa[y];
            if(isrt(y))rotate((ch[z][1]==y)^(ch[y][1]==x)?x:y);
            rotate(x);
        }
    }
    void Access(int x){
        int y=0;
        do{
            splay(x);
            ch[x][1]=y;
            x=fa[y=x];
        }while(x);
    }
    int Get_rt(int x){
        Access(x);
        splay(x);
        while(ch[x][0])x=ch[x][0];
        return x;
    }
    bool Judge(int x,int y){
        while(fa[x])x=fa[x];
        while(fa[y])y=fa[y];
        return x==y;
    }
    int Add(int x,int y){
        if(Judge(x,y))return y;
        splay(x);
        fa[x]=y;
        return 0;
    }
    void Cutto(int x){
        Access(x);
        splay(x);
        if(to[x])to[x]=0;
        else{
            int rt=Get_rt(x);
            ch[x][0]=fa[ch[x][0]]=0;
            to[rt]=Add(rt,to[rt]);
        }
    }
}
int main(){
    read2(n,m);
    FOR(i,1,n){
        read(to[i]);
        to[i]=LCT::Add(i,to[i]);
    }
    int x,y;
    while(m--){
        read(x);
        if(x==1){
            read2(x,y);
            LCT::Cutto(x);
            to[x]=LCT::Add(x,y);
        }else{
            read(x);
            x=LCT::Get_rt(x);
            if(to[x])puts("-1");
            else pf("%d\n",x);
        }
    }
    return 0;
}
