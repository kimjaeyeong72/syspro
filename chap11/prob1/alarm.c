#include <stdio.h>

int main( )
{
   alarm(5);
   printf("infinite loop\n");
   while (1) {
      sleep(1);
      printf("1 second passed\n");
   }
   printf("not running\n");
}

