#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 100000
#define MAXF 10
#define PAGES 64
static int findp(const int f[],int n,int p){for(int i=0;i<n;i++)if(f[i]==p)return i;return -1;}
static int fifo(const int *r,int n,int c){int f[MAXF],u=0,h=0,x=0;for(int i=0;i<n;i++)if(findp(f,u,r[i])<0){x++;if(u<c)f[u++]=r[i];else{f[h]=r[i];h=(h+1)%c;}}return x;}
static int lru(const int *r,int n,int c){int f[MAXF],t[MAXF],u=0,x=0;for(int i=0;i<n;i++){int k=findp(f,u,r[i]);if(k>=0){t[k]=i;continue;}x++;if(u<c)k=u++;else{k=0;for(int j=1;j<u;j++)if(t[j]<t[k])k=j;}f[k]=r[i];t[k]=i;}return x;}
static int opt(const int *r,int n,int c){
 int *next_at=malloc((size_t)n*sizeof *next_at);if(!next_at)return -1;
 int last[PAGES];for(int p=0;p<PAGES;p++)last[p]=n;
 for(int i=n-1;i>=0;i--){next_at[i]=last[r[i]];last[r[i]]=i;}
 int next_pos[PAGES];for(int p=0;p<PAGES;p++)next_pos[p]=last[p];
 int f[MAXF],u=0,x=0;
 for(int i=0;i<n;i++){
  if(findp(f,u,r[i])<0){x++;if(u<c)f[u++]=r[i];else{
   int v=0,far=-1;for(int j=0;j<u;j++)if(next_pos[f[j]]>far){far=next_pos[f[j]];v=j;}
   f[v]=r[i];}}
  next_pos[r[i]]=next_at[i];
 }
 free(next_at);return x;
}
int main(void){
 int *r=malloc(N*sizeof *r);if(!r)return 1;unsigned s=1234567;
 for(int i=0;i<N;i++){s=1664525U*s+1013904223U;r[i]=(int)((s>>16)%PAGES);}
 struct timespec a,b;
 for(int c=3;c<=10;c++){
  clock_gettime(CLOCK_MONOTONIC,&a);int x=fifo(r,N,c);clock_gettime(CLOCK_MONOTONIC,&b);double tf=(b.tv_sec-a.tv_sec)+(b.tv_nsec-a.tv_nsec)/1e9;
  clock_gettime(CLOCK_MONOTONIC,&a);int y=lru(r,N,c);clock_gettime(CLOCK_MONOTONIC,&b);double tl=(b.tv_sec-a.tv_sec)+(b.tv_nsec-a.tv_nsec)/1e9;
  clock_gettime(CLOCK_MONOTONIC,&a);int z=opt(r,N,c);clock_gettime(CLOCK_MONOTONIC,&b);double to=(b.tv_sec-a.tv_sec)+(b.tv_nsec-a.tv_nsec)/1e9;
  printf("frames=%d faults FIFO=%d LRU=%d Optimal=%d times %.6f %.6f %.6f s\n",c,x,y,z,tf,tl,to);
 }
 free(r);return 0;
}
