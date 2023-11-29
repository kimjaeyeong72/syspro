#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_environment_value(const char *env_name) {
    char *value = getenv(env_name);
    if (value != NULL) {
        printf("%s = %s\n", env_name, value);
    } else {
        printf("%s is not set.\n", env_name);
    }
}

int main(int argc, char *argv[]) {
    int opt;

    while ((opt = getopt(argc, argv, "e:ugiip")) != -1) {
        switch (opt) {
            case 'e':
                print_environment_value(optarg);
                break;
            case 'u':
                printf("Real User ID: %d\nEffective User ID: %d\n", getuid(), geteuid());
                break;
            case 'g':
                printf("Real Group ID: %d\nEffective Group ID: %d\n", getgid(), getegid());
                break;
            case 'i':
                printf("Process ID: %d\n", getpid());
                break;
            case 'p':
                printf("Parent Process ID: %d\n", getppid());
                break;
            case '?':
                if (optopt == 'e') {
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                } else {
                    fprintf(stderr, "Unknown option: -%c\n", optopt);
                }
                exit(EXIT_FAILURE);
        }
    }

    return 0;
}
