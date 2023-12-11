#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void alarmHandler(int signo);

int main() {
    signal(SIGALRM, alarmHandler);
    alarm(5);

    for (int i = 1; i <= 5; ++i) {
        sleep(1);
        printf("%d second\n", i);
    }

    printf("wake up\n");
    return 0;
}

void alarmHandler(int signo) {
    printf("wake up\n");
    exit(0);
}
