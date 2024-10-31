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
const int P=1e4+7;
const int maxn=3e4+5;
int n,Q;
int K[maxn],B[maxn],to[maxn];
int inv[maxn];
namespace LCT{
    #pragma GCC optimize(2)
    #pragma GCC optimize(3)
    int stk[maxn],top;
    int ch[maxn][2],fa[maxn];
    bool rev[maxn];
    int k[maxn],b[maxn];
    bool isrt(int x){return x==ch[fa[x]][0]||x==ch[fa[x]][1];}
    #define ls ch[x][0]
    #define rs ch[x][1]
    void Up(int x){
        k[x]=(ll)k[ls]*k[rs]%P*K[x]%P;
        b[x]=((ll)b[ls]*K[x]%P+B[x])%P;
        b[x]=((ll)k[rs]*b[x]%P+b[rs])%P;
//        b[x][1]=((ll)b[rs][1]*K[x]%P+B[x])%P;
//        b[x][1]=((ll)k[ls]*b[x][1]%P+b[ls][1])%P;
        //锛燂紵锛熶氦鎹?
    }
    void Modi_rev(int x){
        if(!x)return;
        rev[x]^=1;
        swap(ls,rs);
//        swap(b[x][0],b[x][1]);
    }
    void Down(int x){
        if(rev[x]){
            Modi_rev(ls);
            Modi_rev(rs);
            rev[x]=0;
        }
    }
    void rotate(int x){
        int y=fa[x],z=fa[y];
        bool k=ch[y][1]==x;
        if(isrt(y))ch[z][ch[z][1]==y]=x;fa[x]=z;
        ch[y][k]=ch[x][k^1];if(ch[x][k^1])fa[ch[x][k^1]]=y;
        fa[y]=x;ch[x][k^1]=y;
        Up(y);Up(x);
    }
    void Push_Down(int x){
        stk[top=1]=x;
        while(isrt(x))stk[++top]=x=fa[x];
        while(top)Down(stk[top--]);
    }
    void splay(int x){
        Push_Down(x);
        while(isrt(x)){
            int y=fa[x],z=fa[y];
            if(isrt(y))rotate((ch[y][1]==x)^(ch[z][1]==y)?x:y);
            rotate(x);
        }
    }
    void Access(int x){
        int y=0;
        do{
            splay(x);
            rs=y;
            Up(x);
            x=fa[y=x];
        }while(x);
    }
    void Mroot(int x){
        Access(x);
        splay(x);
        Modi_rev(x);
    }
    int Get_rt(int x){
        Access(x);
        splay(x);
        while(ls)Down(x=ls);
        return x;
    }
    bool Judge(int x,int y){
        while(fa[x])x=fa[x];
        while(fa[y])y=fa[y];
        return x==y;
    }
    int Link(int x,int y){
        if(!y||Judge(x,y))return y;
        Mroot(x);
        splay(x);
        fa[x]=y;
        return 0;
    }
    void Cutfa(int x){
        int rt=Get_rt(x);
        Access(x);splay(x);
        ls=fa[ls]=0;
        Up(x);
        if(to[rt])to[rt]=Link(rt,to[rt]);
    }
    void Change(){
        int x;
        read(x);
        Cutfa(x);
        read3(K[x],to[x],B[x]);
        to[x]=Link(x,to[x]);
    }
    bool Check(int x,int y){
        splay(y);
        while(isrt(x))x=fa[x];
        return x==y;
    }
    int query(){
        int x;
        read(x);
        int rt=Get_rt(x),y=to[rt];
        Access(y);
        splay(y);
        int S=b[y],T=(1-k[y]+P)%P;
        int v;
        if(!T)return S?-1:-2;
        else v=(ll)S*inv[T]%P;
        Access(x);
        splay(x);
        return ((ll)v*k[x]+b[x])%P;
    }
}
void Init(){
    inv[1]=1;
    FOR(i,2,P-1)inv[i]=P-P/i*inv[P%i]%P;
    LCT::k[0]=1;
}
int main(){
    Init();
    read(n);
    FOR(i,1,n){
        read3(K[i],to[i],B[i]);
        to[i]=LCT::Link(i,to[i]);
    }
    read(Q);
    char op[2];
    while(Q--){
        reads(op);
        switch(op[0]){
            case 'A':
                pf("%d\n",LCT::query());
                break;
            case 'C':
                LCT::Change();
                break;
        }
    }
    return 0;
}