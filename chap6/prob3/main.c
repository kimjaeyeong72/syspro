#include <sys/types.h>
#include <utime.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    struct stat buf;        
    struct utimbuf time;

    if (argc < 3) {
        fprintf(stderr, “How to use: cptime file1 file2\n");
        exit(1);
    }

    if (stat(argv[1], &buf) <0) { 
        perror("stat()");
        exit(-1);
    }

    time.actime = buf.st_atime;
    time.modtime = buf.st_mtime;

    if (utime(argv[2], &time))   
        perror("utime");
    else exit(0);
}
