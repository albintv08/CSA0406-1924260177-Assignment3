#include <stdio.h>
#include <math.h>
int main(void){
 const unsigned long long page=4096,entry=8;
 const int bits[]={32,48};
 for(int i=0;i<2;i++){
  unsigned long long pages=1ULL<<(bits[i]-12);
  printf("%d-bit virtual address, 4 KB pages: %llu entries, %llu bytes (%.2f MiB) at %llu-byte PTEs\n",
   bits[i],pages,pages*entry,(double)(pages*entry)/(1024.0*1024.0),entry);
 }
 puts("This is a single-level, fully populated page-table estimate; real multi-level tables allocate lower levels on demand.");
 return 0;
}
