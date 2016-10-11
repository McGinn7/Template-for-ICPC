#include<cstdio>
#include<cstring>
#include<stdlib.h>
#include<time.h>
#define N 1000007
#define LL __int64
LL v[N];
int l[N],r[N],hr[N],s[N];
int tot,root;
void init(){
	srand(time(NULL));
	tot=root=0;
}
void Lr(int &x){
	int y;
	y=r[x],r[x]=l[y],l[y]=x;
	s[y]=s[x],s[x]=1+s[l[x]]+s[r[x]];
	x=y;
}
void Rr(int &x){
	int y;
	y=l[x],l[x]=r[y],r[y]=x;
	s[y]=s[x],s[x]=1+s[l[x]]+s[r[x]];
	x=y;
}
void insert(int &k,LL key){
	if(k==0){
		++tot,v[tot]=key,s[tot]=1;
		hr[k=tot]=(int)rand();
		return ;
	}
	++s[k];
	if(key<=v[k]){
		insert(l[k],key);
		if(hr[l[k]]>hr[k]) Rr(k);
		return ;
	}
	else{
		insert(r[k],key);
		if(hr[r[k]]>hr[k]) Lr(k);
		return ;
	}
}
LL del(int &k,LL key){
	LL res;
	--s[k];
	if(key==v[k] || (l[k]==0 && key<v[k]) || (r[k]==0 && key>=v[k])){
		res=v[k];
		if(l[k]==0 || r[k]==0){
			k=l[k]+r[k];
			return res;
		}
		v[k]=del(l[k],key+1);
		return res;
	}
	if(key<=v[k]) return del(l[k],key);
	if(key> v[k]) return del(r[k],key);
	return 0;
}
bool find(int &k,LL key){
	if(k==0) return false;
	if(key>v[k]) return find(r[k],key);
	return v[k]==key || find(l[k],key);
}
int rank(int &k,LL key){
	if(k==0) return 1;
	if(key<=v[k]) return rank(l[k],key);
	return s[l[k]]+1+rank(r[k],key);
}
LL select(int &k,int t){
	if(t==s[l[k]]+1) return v[k];
	if(t<=s[l[k]]) return select(l[k],t);
	return select(r[k],t-1-s[l[k]]);
}
int main(){
	init();
	int n;
	LL x;
	scanf("%d",&n);
	while(n--){
		scanf("%I64d",&x);
		insert(root,x);
		printf("%d\n",rank(root,x));
	}
	return 0;
}
