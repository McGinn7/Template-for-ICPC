#include<cstdio>
#include<algorithm>
using namespace std;
#define N 300007
#define root1 ch[root][1]
#define root10 ch[root1][0]
int n,q;
int a[N],b[N];
int tot,root,query;
int pre[N],val[N],size[N],ch[N][2],light[N];
int gcd0[N],gcd1[N];
int GCD(int a,int b){
	if(b==0) return a;
	int r=a%b;
	while(r){
		a=b,b=r,r=a%b;
	}
	return b;
}
void pushUp(int t){
	if(t<=0) return ;
	size[t]=1+size[ch[t][0]]+size[ch[t][1]];
	gcd0[t]=GCD(gcd0[ch[t][0]],gcd0[ch[t][1]]);
	gcd1[t]=GCD(gcd1[ch[t][0]],gcd1[ch[t][1]]);
	if(light[t]){
		gcd1[t]=GCD(val[t],gcd1[t]);
	}
	else{
		gcd0[t]=GCD(val[t],gcd0[t]);
	}
}
void pushDown(int t){
}
void newNode(int &t,int value,int on_off,int father){
	t=++tot;
	size[t]=1;
	val[t]=value;
	pre[t]=father;
	light[t]=on_off;
	if(on_off){
		gcd0[t]=0,gcd1[t]=value;
	}
	else{
		gcd0[t]=value,gcd1[t]=0;
	}
	ch[t][0]=ch[t][1]=0;
}
void buildtree(int &t,int l,int r,int father){
	if(l>r) return ;
	int m=(l+r)>>1;
	newNode(t,a[m],b[m],father);
	buildtree(ch[t][0],l,m-1,t);
	buildtree(ch[t][1],m+1,r,t);
	pushUp(t);
}
void rotate(int x,int k){
	int y=pre[x];
	pushDown(y),pushDown(x);
	ch[y][!k]=ch[x][k];
	pre[ch[x][k]]=y;
	if(pre[y]) ch[pre[y]][ch[pre[y]][1]==y]=x;
	pre[x]=pre[y];
	ch[x][k]=y;
	pre[y]=x;
	pushUp(y),pushUp(x);
}
void splay(int x,int goal){
	pushDown(x);
	int k;
	while(pre[x]!=goal)
	if(pre[pre[x]]==goal){
		pushDown(pre[x]),pushDown(x);
		rotate(x,ch[pre[x]][0]==x);
	}
	else{
		int y=pre[x];
		pushDown(pre[y]),pushDown(y),pushDown(x);
		k=(ch[pre[y]][0]==y);
		if(ch[y][k]==x) rotate(x,!k); else rotate(y,k);
		rotate(x,k);
	}
	pushUp(x);
	if(goal==0) root=x;
}
int getMin(int t){
	pushDown(t);
	while(ch[t][0]){
		t=ch[t][0];
		pushDown(t);
	}
	return t;
}
int getRank(int t,int rank){
	pushDown(t);
	int s=size[ch[t][0]];
	if(rank==1+s) return t;
	if(rank<=s) return getRank(ch[t][0],rank);
	return getRank(ch[t][1],rank-1-s);
}
void ins(int t,int value,int on_off){
	int x=getRank(root,t);
	if(ch[x][1]==0){
		newNode(ch[x][1],value,on_off,x);
	}
	else{
		x=getMin(ch[x][1]);
		newNode(ch[x][0],value,on_off,x);
	}
	while(x){
		pushUp(x);
		x=pre[x];
	}
	++n;
}
void del(int k){
	int x=getRank(root,k-1);
	int y=getRank(root,k+1);
	splay(x,0);
	splay(y,root);
	pre[root10]=0,root10=0;
	pushUp(root1),pushUp(root);
	splay(1,0);
	--n;
}
char getChar(){
	char CH=getchar();
	while(CH!='Q' && CH!='I' && CH!='D' && CH!='R' && CH!='M') CH=getchar();
	return CH;
}
int main(){
	int i,l,r,x,y,ans,status;
	while(scanf("%d%d",&n,&q)!=EOF){
		tot=root=query=0;
		for(i=1;i<=n;++i) scanf("%d%d",&a[i],&b[i]);
		newNode(root,0,0,0);
		newNode(root1,0,0,root);
		buildtree(root10,1,n,root1);
		pushUp(root1),pushUp(root);
		while(q--){
			char CH=getChar();
			switch(CH){
			case 'Q':
				scanf("%d%d%d",&l,&r,&status);
				x=getRank(root,l-1+1);
				y=getRank(root,r+1+1);
				splay(x,0);
				splay(y,root);
				if(status) ans=gcd1[root10];
				else ans=gcd0[root10];
				if(ans==0) ans=-1;
				printf("%d\n",ans);
				splay(1,0);
				break;
			case 'I':
				scanf("%d%d%d",&x,&y,&status);
				ins(x+1,y,status);
				break;
			case 'D':
				scanf("%d",&x);
				del(x+1);
				break;
			case 'R':
				scanf("%d",&l);
				x=getRank(root,l-1+1);
				y=getRank(root,l+1+1);
				splay(x,0);
				splay(y,root);
				light[root10]=1-light[root10];
				pushUp(root10),pushUp(root1),pushUp(root);
				splay(1,0);
				break;
			case 'M':
				scanf("%d%d",&l,&r);
				x=getRank(root,l-1+1);
				y=getRank(root,l+1+1);
				splay(x,0);
				splay(y,root);
				val[root10]=r;
				pushUp(root10),pushUp(root1),pushUp(root);
				splay(1,0);
				break;
			}
		}
	}
	return 0;
}