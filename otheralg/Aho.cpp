#include<bits/stdc++.h>
#define reutrn return
#define idx(QQQ) (QQQ-'a')
using namespace std;
int ch[550005][27],f[550005],last[550005],ne[550005],tot=1;
char cc[55];
char ss[5000005];
void insert(char* cc){
	int k=1;
	for(int i=0;i<strlen(cc);i++){
		if(!ch[k][idx(cc[i])])ch[k][idx(cc[i])]=++tot;
		k=ch[k][idx(cc[i])];
	}
	f[k]++;
}
void clear(){memset(ch,0,sizeof ch);memset(f,0,sizeof f);tot=1;}
void fail(){
	queue<int> Q;
	for(int i=0;i<26;i++){
		if(!ch[1][i])ch[1][i]=1;else Q.push(ch[1][i]),ne[ch[1][i]]=1;
	}
	while(!Q.empty()){
		int x=Q.front();Q.pop();
		for(int i=0;i<26;i++){
			if(ch[x][i]){
				ne[ch[x][i]]=ch[ne[x]][i];
				last[ch[x][i]]=f[ne[ch[x][i]]]?ne[ch[x][i]]:last[ne[ch[x][i]]];
				Q.push(ch[x][i]);
			}else ch[x][i]=ch[ne[x]][i];
		}
	}
}
int ans(char* ss){
	int len=strlen(ss),ans=0,vi=1;
	for(int i=0;i<len;i++){
		vi=ch[vi][idx(ss[i])];
		ans+=f[vi];f[vi]=0;
		int t=last[vi];
		while(t){
			ans+=f[t];f[t]=0;
			t=last[t];
		}
	}
	return ans;
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		clear();
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%s",cc);
			insert(cc);
		}
		fail();
		scanf("%s",ss);
		printf("%d\n",ans(ss));
	}
	return 0;
}
