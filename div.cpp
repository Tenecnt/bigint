#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#define maxn (1<<18)
#define clr(a,b) memset(a,b,sizeof(a))
using namespace std;
const double pi=acos(-1);
struct cn{
	double a,b;
	cn(double a=0,double b=0):a(a),b(b){}
};
cn operator+(cn a,cn b){return cn(a.a+b.a,a.b+b.b);}
cn operator-(cn a,cn b){return cn(a.a-b.a,a.b-b.b);}
cn operator*(cn a,cn b){return cn(a.a*b.a-a.b*b.b,a.a*b.b+a.b*b.a);}
int rev[2*maxn+10];
void fft(cn *a,int t,int n,int f){
	for(int i=1;i<n;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<t-1);
	for(int i=0;i<n;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
	for(int i=1;i<n;i<<=1){
		cn wn(cos(pi/i),f*sin(pi/i));
		for(int p=i<<1,j=0;j<n;j+=p){
			cn w(1,0);
			for(int k=j;k<j+i;k++){
				cn x=a[k],y=w*a[k+i];
				a[k]=x+y;
				a[k+i]=x-y;
				w=w*wn;
			}
		}
	}
	if(f==-1)for(int i=0;i<n;i++)a[i].a/=n,a[i].b/=n;
}
struct bint{
	int a[10000],len;
	void print(){
		if(!len)puts("0");
		else{
			for(int i=len-1;i>=0;i--)printf("%d",a[i]);
			putchar('\n');
		}
	}
	bint(int x=0){
		len=0;
		clr(a,0);
		while(x)a[len++]=x%10,x/=10;
	}
	void clear(int lim){
		int m=len-lim;
		for(int i=0;i<lim;i++)a[i]=a[i+m];
		for(int i=lim;i<len;i++)a[i]=0;
		len=lim;
	}
};
bool operator==(const bint &a,const bint &b){
	if(a.len!=b.len)return 0;
	for(int i=0;i<a.len;i++)if(a.a[i]!=b.a[i])return 0;
	return 1;
}
bool operator<(const bint &a,const bint &b){
	if(a.len!=b.len)return a.len<b.len;
	for(int i=a.len-1;i>=0;i--)if(a.a[i]!=b.a[i])return a.a[i]<b.a[i];
	return 0;
}
bint operator+(const bint &a,const bint &b){
	bint c;
	c.len=max(a.len,b.len);
	for(int i=0;i<c.len;i++)c.a[i]+=a.a[i]+b.a[i],c.a[i+1]+=c.a[i]/10,c.a[i]%=10;
	if(c.a[c.len])c.len++;
	return c;
}
bint operator*(const bint &a,const bint &b){
	static cn x[maxn+10],y[maxn+10],z[maxn+10];
	int n=a.len+b.len;
	int t=0;
	while((1<<t)<n)t++;
	n=1<<t;
	for(int i=0;i<n;i++)x[i]=cn(a.a[i],0),y[i]=cn(b.a[i],0);
	fft(x,t,n,1);
	fft(y,t,n,1);
	for(int i=0;i<n;i++)z[i]=x[i]*y[i];
	fft(z,t,n,-1);
	bint c;
	c.len=a.len+b.len-1;
	for(int i=0;i<c.len;i++)c.a[i]+=z[i].a+0.5,c.a[i+1]+=c.a[i]/10,c.a[i]%=10;
	if(c.a[c.len])c.len++;
	return c;
}
bint operator-(const bint &a,const bint &b){
	bint c;
	for(int i=0;i<a.len;i++){
		c.a[i]+=a.a[i]-b.a[i];
		if(c.a[i]<0)c.a[i]+=10,c.a[i+1]--; 
	}
	c.len=a.len;
	while(c.len&&!c.a[c.len-1])c.len--;
	return c;
}
bint n,ni;
int fac;
//预处理n的倒数
void init(){
	ni=1;
	fac=n.len;
	int lim=n.len<<1;
	for(int i=1;i<=100;i++){
		bint two;
		two.len=fac+1;
		two.a[fac]=2;
		ni=ni*(two-n*ni);
		fac*=2;
		if(ni.len>lim){
			fac-=ni.len-lim;
			ni.clear(lim); 
		}
	}
}
void mod(bint &a){
	bint q=a*ni;
	q.clear(q.len-fac);
	a=a-q*n;
	while(a==n||n<a)
		a=a-n;
}
int main(){
	n=431923;
	bint a=54812353;
	init();
	mod(a);
	a.print();
}          
