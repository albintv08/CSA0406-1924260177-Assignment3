#include <stdio.h>
#include <math.h>
int main(void){
 const double n=6.0,d=4.0,p=0.02;
 printf("Six disks of 4 TB each (nominal):\n");
 printf("RAID 0: %.1f TB usable; survives no disk failure\n",n*d);
 printf("RAID 1 (3 mirrored pairs): %.1f TB usable; survives one disk per mirror pair\n",(n/2)*d);
 printf("RAID 5: %.1f TB usable; survives one disk failure\n",(n-1)*d);
 printf("RAID 10: %.1f TB usable; survives one disk per mirror pair\n",(n/2)*d);
 double loss1=p*p;
 double loss5=1.0-pow(1.0-p,n)-n*p*pow(1.0-p,n-1);
 printf("Assumed independent per-drive failure probability p=%.2f over one chosen interval\n",p);
 printf("RAID 1 pair data-loss probability (both mirror drives fail): %.6f (%.4f%%)\n",loss1,100*loss1);
 printf("RAID 5 data-loss probability (2 or more of 6 drives fail): %.6f (%.4f%%)\n",loss5,100*loss5);
 puts("Assumption: independent equal failure probabilities; real failures may be correlated.");
 return 0;
}
