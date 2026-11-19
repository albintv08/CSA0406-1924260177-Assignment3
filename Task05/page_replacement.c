#include <stdio.h>
#include <stdbool.h>
#define MAXF 8
int find(const int f[],int n,int page){for(int i=0;i<n;i++)if(f[i]==page)return i;return -1;}
int fifo(const int ref[],int len,int frames){
 int f[MAXF],used=0,next=0,faults=0;
 for(int i=0;i<len;i++){if(find(f,used,ref[i])>=0)continue;faults++;
 if(used<frames)f[used++]=ref[i];else{f[next]=ref[i];next=(next+1)%frames;}}
 return faults;
}
int lru(const int ref[],int len,int frames){
 int f[MAXF],last[MAXF],used=0,faults=0;
 for(int i=0;i<len;i++){
  int k=find(f,used,ref[i]);
  if(k>=0){last[k]=i;continue;}
  faults++;
  if(used<frames)k=used++;
  else{k=0;for(int j=1;j<used;j++)if(last[j]<last[k])k=j;}
  f[k]=ref[i];last[k]=i;
 }
 return faults;
}
int optimal(const int ref[],int len,int frames){
 int f[MAXF],used=0,faults=0;
 for(int i=0;i<len;i++){
  if(find(f,used,ref[i])>=0)continue;faults++;
  if(used<frames){f[used++]=ref[i];continue;}
  int victim=0,farthest=-1;
  for(int j=0;j<frames;j++){int next=len;for(int t=i+1;t<len;t++)if(ref[t]==f[j]){next=t;break;}
   if(next>farthest){farthest=next;victim=j;}}
  f[victim]=ref[i];
 }
 return faults;
}
int clock_policy(const int ref[],int len,int frames){
 int f[MAXF],used=0,hand=0,faults=0;bool bit[MAXF]={false};
 for(int i=0;i<len;i++){
  int k=find(f,used,ref[i]);if(k>=0){bit[k]=true;continue;}faults++;
  if(used<frames){k=used++;f[k]=ref[i];bit[k]=true;}
  else{while(bit[hand]){bit[hand]=false;hand=(hand+1)%frames;}
   f[hand]=ref[i];bit[hand]=true;hand=(hand+1)%frames;}
 }
 return faults;
}
int main(void){
 int ref[]={7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
 int len=(int)(sizeof ref/sizeof ref[0]);
 for(int fr=3;fr<=4;fr++)
  printf("%d frames: FIFO %d, LRU %d, Optimal %d, Clock %d\n",fr,
   fifo(ref,len,fr),lru(ref,len,fr),optimal(ref,len,fr),clock_policy(ref,len,fr));
 int belady[]={1,2,3,4,1,2,5,1,2,3,4,5};
 printf("Belady string, FIFO: 3 frames %d faults, 4 frames %d faults\n",
  fifo(belady,12,3),fifo(belady,12,4));
 return 0;
}
