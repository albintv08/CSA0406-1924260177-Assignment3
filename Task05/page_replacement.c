#include <stdio.h>
#include <stdbool.h>
#define N 13
#define MAXF 8
static const int refs[N]={7,0,1,2,0,3,0,4,2,3,0,3,2};
static int find(const int f[],int n,int p){for(int i=0;i<n;i++)if(f[i]==p)return i;return -1;}
static int fifo(int c){
 int f[MAXF],n=0,next=0,x=0;
 for(int i=0;i<N;i++)if(find(f,n,refs[i])<0){x++;if(n<c)f[n++]=refs[i];else{f[next]=refs[i];next=(next+1)%c;}}
 return x;
}
static int lru(int c){
 int f[MAXF],last[MAXF],n=0,x=0;
 for(int i=0;i<N;i++){int s=find(f,n,refs[i]);if(s>=0){last[s]=i;continue;}x++;
 if(n<c)s=n++;else{s=0;for(int j=1;j<n;j++)if(last[j]<last[s])s=j;}
 f[s]=refs[i];last[s]=i;}return x;
}
static int optimal(int c){
 int f[MAXF],n=0,x=0;
 for(int i=0;i<N;i++){if(find(f,n,refs[i])>=0)continue;x++;if(n<c){f[n++]=refs[i];continue;}
 int v=0,far=-1;for(int j=0;j<n;j++){int k=i+1;while(k<N&&refs[k]!=f[j])k++;if(k>far){far=k;v=j;}}f[v]=refs[i];}return x;
}
static int clock_alg(int c){
 int f[MAXF],n=0,h=0,x=0;bool use[MAXF]={false};
 for(int i=0;i<N;i++){int s=find(f,n,refs[i]);if(s>=0){use[s]=true;continue;}x++;
 if(n<c){s=n++;f[s]=refs[i];use[s]=true;}else{while(use[h]){use[h]=false;h=(h+1)%c;}f[h]=refs[i];use[h]=true;h=(h+1)%c;}}
 return x;
}
int main(void){
 const int counts[]={3,4};
 for(size_t i=0;i<2;i++){int c=counts[i];printf("Frames=%d | FIFO=%d | LRU=%d | Optimal=%d | Clock=%d\n",c,fifo(c),lru(c),optimal(c),clock_alg(c));}
 return 0;
}
