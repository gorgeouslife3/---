#include<cstdio>
#include<cstring>
#define int long long
#define F(i,j,n) for(register int i=j;i<=n;i++)
#define Hashmod 299993 
using namespace std;
/*
12 12
............
............
............
............
............
............
............
............
............
............
............
............*/
//cout:1076226888605605706
struct Hash {
	int num[2],sta[2],next;
}s[300010];
struct ha {
	int _s[20];
};
int cnt[2],n,m,endi,endj,head[300010],ans=0;
int mp[20][20],last,now;
char ch[21];
inline int read() {
	register int d=0,f=1;
	char ch = getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		d = (d<<1)+(d<<3)+(ch^48);
		ch = getchar();
	}
	return d*f;	
}
inline void ins(int sta,int num) {
	int temp=sta%Hashmod;
	for(register int i=head[temp];i;i=s[i].next) {
		if(sta==s[i].sta[now]){
			s[i].num[now]+=num;
			return;
		}
	}
	s[++cnt[now]].sta[now]=sta;
	s[cnt[now]].num[now]=num;
	s[cnt[now]].next=head[temp];
	head[temp]=cnt[now];
}
inline ha up(int sta) {
	ha rt;
	rt._s[0]=sta&3;
	for(register int i=1; i<=m; i++) {
		rt._s[i]=(sta>>(i<<1))&3;
	}
	return rt;
}
inline int Win(ha rt) {
	int sta=0;
	for(register int i=1; i<=m; i++) {
		sta=sta|(rt._s[i]<<(i<<1));
	}
	sta|=rt._s[0];
	return sta;
}
void DP() {
	ins(0,1);
	for(register int i=1;i<=n; i++) {
		for(register int j=1;j<=m;j++) {
			last=now;
			now^=1;
			cnt[now]=0;
			memset(head,0,sizeof(head));
			for(register int k=1;k<=cnt[last];k++) {
				ha _pnt=up(s[k].sta[last]),_k=_pnt;
				int lastnum=s[k].num[last],west=_pnt._s[0],north=_k._s[j];
				if(!mp[i][j]) {
					if(!west&&!north) {
						ins(Win(_k),lastnum);
					}
					continue;
				}
				if(!west&&!north){
					if(mp[i][j+1]&&mp[i+1][j]){
						_k._s[0]=2;
						_k._s[j]=1;
						ins(Win(_k),lastnum);
					}
					continue;
				}
				if(!west&&north){
					if(mp[i+1][j]){
						ins(Win(_k),lastnum);
					}
					if(mp[i][j+1]){
						_k._s[0]=north;
						_k._s[j]=0;
						ins(Win(_k),lastnum);
					}
					continue;
				}
				if(west&&!north){
					if(mp[i][j+1]){
						ins(Win(_k),lastnum);
					}
					if(mp[i+1][j]){
						_k._s[j]=west;
						_k._s[0]=0;
						ins(Win(_k),lastnum);
					}
					continue;
				}
				if(west==2&&north==1){
					_k._s[0]=_k._s[j]=0;
					ins(Win(_k),lastnum);
					continue;
				}
				if(west==1&&north==1){
					register int pei=1,place=j+1;
					for(;place<=m;place++){
						if(_k._s[place]==1) pei++;
						else if(_k._s[place]==2) pei--;
						if(!pei) break;
					}
					_k._s[place]=1;
					_k._s[0]=_k._s[j]=0;
					ins(Win(_k),lastnum);
					continue;
				}
				if(west==2&&north==2){
					register int pei=-1,place=j-1;
					for(;place>=1;place--){
						if(_k._s[place]==1) pei++;
						else if(_k._s[place]==2) pei--;
						if(!pei) break;
					}
					_k._s[place]=2;
					_k._s[0]=_k._s[j]=0;
					ins(Win(_k),lastnum);
					continue;
				}
				if(west==1&&north==2){
					_k._s[0]=_k._s[j]=0;
					bool flag=true;
					if(i==endi&&j==endj){
						for(register int pos=0;pos<=m;pos++){
							if(_k._s[pos]){
								flag=false;break;
							}
						}
						if(flag){
							ans+=lastnum;
						}
					}
					continue;
				}
			}
		}
	}
}
signed main(){
	n=read(),m=read();
	for(register int i=1;i<=n;i++){
		scanf("%s",ch+1);
		for(register int j=1;j<=m;j++){
			if(ch[j]=='.') mp[i][j]=1,endi=i,endj=j;
			else mp[i][j]=0;
		}
	}
	DP();
	printf("%lld\n",ans);
	return 0;
}