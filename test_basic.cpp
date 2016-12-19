#include <cstdio>
#include "big.h"
#include <windows.h>

int main()
{
 int stg = GetTickCount();

 big a = 123;
 printf("= a=123 %s\n",a.c_str());

 big b = a;
 printf("= b=123 %s\n",a.c_str());

 a = "321";
 printf("= a=321 %s\n",a.c_str());

 a = a + 1;
 printf("+ a=322 %s\n",a.c_str());

 a += 1;
 printf("+ a=323 %s\n",a.c_str());

 a -= 1;
 printf("+ a=322 %s\n",a.c_str());

 a = a + "1";
 printf("+ a=323 %s\n",a.c_str());

 a = a - 1;
 printf("- a=322 %s\n",a.c_str());

 a = a - "23";
 printf("- a=299 %s\n",a.c_str());

 a = a - 302;
 printf("- a=-3 %s\n",a.c_str());

 a = (a + 5) * 5;
 printf("* a=10 %s\n",a.c_str());

 a = a / 2;
 printf("/ a=5 %s\n",a.c_str());

 a = a / 3;
 printf("/ a=1 %s\n",a.c_str());

 big t = big(5)*big(3);
 if (t!=15) {
	 printf("5*3==15 <= error");
	 return 0;
}

 if ((big(4)+big(1))*big(3) > big(17)) {
	 printf("(4+1)*3 <= error");
	 return 0;
 }

 a = (a*17) % 3;
 printf("%% a=2 %s\n",a.c_str());

 a = a << 2;
 printf("<< a=8 %s\n",a.c_str());

 a = a >> 1;
 printf(">> a=4 %s\n",a.c_str()); 

 if (big(3)<big(13952))
	 printf("3 < 13952 ok\n");
 else
	 printf("< error\n");

 if (big(25)<big(25))
	 printf("< error\n");
 else
	 printf(" not 25<25 ok\n");

 if ((big)10 / (big)2 == (big)5)
	 printf("10/2 == ok\n");
 else
	 printf("10/2 == %s error\n",(big(10)/big(2)).c_str());

 if ((big)1720 / (big)20 == (big)86)
	 printf("1720/20 == ok\n");
 else
	 printf("1720/20 == error\n");

 big t2 = big(117) - big(15)*big(2) - big(-10)*2 + big(35);
 t2 -= 35;
 if (t2 == 107)
	 printf("t2 == ok\n");
 else
	 printf("t2 == error\n");

 big tr = (t2-100)*(t2-100) + 1;
 tr++;  
 tr--;
 tr+=2;
 if (tr == 52)
	 printf("tr == ok\n");
 else
	 printf("tr == error\n");

 tr = tr * 10;
 if (tr == 520)
	 printf("tr == ok\n");
 else
	 printf("tr == error\n");

 tr = big(40) * 10;
 if (tr == 400)
	 printf("tr == ok\n");
 else
	 printf("tr == error\n");

 big bi = 100010;
 big bj = 4;
 if (bi-bj*(bi/bj)!=bi%bj) {
	 printf("100010 4 error\n");
	 return 0;
 }

 for (int i=1000;i<1030;i++)
	 for (int j=1;j<100;j++) {
		 big bi = i;
		 big bj = j;
		 if (bi-bj*(bi/bj)!=bi%bj) {
			 printf("i=%d j=%d error\n",i,j);
			 return 0;
		 }
	 }

 int stg2 = GetTickCount()-stg;
 printf("Ticks %d\n",stg2);
}

