#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>	

void p1(), p2();
jmp_buf env;
	
int main() 
{
    if (setjmp(env) != 0) {
         printf("Return and processing due to error\n");
         exit(0);
    } 
   else printf("first pass\n");
	
   p1(); 
} 

void p1()
{
    p2();
}

void p2()
{
    int error;

    error = 1;
    if (error) {
        printf("error\n");
        longjmp(env, 1);
    }
}

