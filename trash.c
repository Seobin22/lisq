/*#include <stdio.h>

void sub(){static int scount=0;
    printf("scount=%d",scount);
    scount++;}
    
int main(void){sub();sub();sub();return 0;}
_________
static int scount = 0;  // 전역 변수

int main(void) {
    static int scount = 1;  // 지역 static 변수(함수 블록 내부)
}
____________


int main(void){
    static int scount = 0; 
    for(int i=0;i<3;i++) { 
        static int scount = 1; 
        scount++; 
    }
printf("&d",scount);}  0
__________________
int main(void){ 
 for(int i=0;i<3;i++)
 { static int scount = 1; 
  scount++;  }
   printf("&d",scount);}  컴파일오류
_____________
#include <stdio.h> 
void sub(){static int scount=0; 
printf("scount=%d",scount); scount++;} 
int main(void){sub();sub();sub();
printf("scount=%d",scount);return 0;} 도 오류.
_____
scope(범위)와 lifetime(수명)은 다르다. 블락내부에서만 계속 살아있는 것.
*/