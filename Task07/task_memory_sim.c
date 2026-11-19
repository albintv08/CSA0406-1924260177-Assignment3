#include <stdio.h>
#include <stdlib.h>
#define TASKS 3
#define FRAMES 128
int main(void){
 const int task_pages[TASKS]={32,384,16};
 const char *names[TASKS]={"control","machine-learning","logging"};
 int frames[FRAMES],used=0,hand=0,faults=0;
 for(int t=0;t<TASKS;t++){
  for(int k=0;k<task_pages[t];k++){
   int page=t*1000+k,found=0;
   for(int j=0;j<used;j++)if(frames[j]==page){found=1;break;}
   if(found)continue;
   faults++;
   if(used<FRAMES)frames[used++]=page;
   else{frames[hand]=page;hand=(hand+1)%FRAMES;}
  }
  printf("%s task: working set %d pages processed\n",names[t],task_pages[t]);
 }
 printf("Total simulated page faults under FIFO: %d\n",faults);
 puts("This is a simplified teaching simulation; configure page size and frame count to match the target device.");
 return 0;
}
