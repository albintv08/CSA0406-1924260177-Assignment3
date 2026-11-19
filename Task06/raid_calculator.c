#include <stdio.h>
#include <math.h>
int main(void){
 const double n=6.0,d=4.0,p=0.02;
 printf("Six disks of 4 TB each (nominal):\n");
 printf("RAID 0: %.1f TB usable; no disk-failure tolerance\n",n*d);
 printf("RAID 1 (six-way mirror): %.1f TB usable; survives up to five disk failures\n",d);
 printf("RAID 5: %.1f TB usable; survives one disk failure\n",(n-1)*d);
 printf("RAID 10 (three mirrored pairs): %.1f TB usable; survives one disk per mirror pair\n",(n/2)*d);
 printf("Assumed independent per-drive failure probability p=%.2f over one chosen interval\n",p);
 double loss1=pow(p,n);
 double loss5=1.0-pow(1.0-p,n)-n*p*pow(1.0-p,n-1);
 printf("RAID 1 six-way mirror data-loss probability (all six fail): %.8f (%.6f%%)\n",loss1,100*loss1);
 printf("RAID 5 data-loss probability (2 or more of 6 drives fail): %.8f (%.6f%%)\n",loss5,100*loss5);
 puts("Assumptions: independent equal failure probabilities, same interval, equal-size disks; real failures can be correlated.");
 return 0;
}
