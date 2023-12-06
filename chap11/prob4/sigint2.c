#include <stdio.h>
#include <unistd.h>
#include <signal.h>

struct sigaction newact;
struct sigaction oldact;
void sigint_handler(int signo); 

int main( void)
{
     newact.sa_handler = sigint_handler; 
     sigfillset(&newact.sa_mask); 
	 sigaction(SIGINT, &newact, &oldact);

	 while(1 ) {
        printf( "Try pressing Ctrl-C!\n");
        sleep(1);
     }
 }

 void sigint_handler(int signo)
 {
     printf( "%d signal processing!\n", signo);
     printf( "If you press it again, it will end.\n");
     sigaction(SIGINT, &oldact, NULL);
 }



