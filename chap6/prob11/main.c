#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

char type(mode_t);
char *perm(mode_t);
void printStat(char *, char *, struct stat *, int, int, int, int);
void printFullPath(char *, char *, int);

int myls_main(int argc, char **argv)
{
    DIR *dp;
    char *dir;
    struct stat st;
    struct dirent *d;
    char path[BUFSIZ + 1];
    int option_l = 0;
    int option_a = 0;
    int option_p = 0;
    int option_i = 0;
    int option_Q = 0;

    
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-l") == 0)
        {
            option_l = 1;
        }
        else if (strcmp(argv[i], "-a") == 0)
        {
            option_a = 1;
        }
        else if (strcmp(argv[i], "-p") == 0)
        {
            option_p = 1;
        }
        else if (strcmp(argv[i], "-i") == 0)
        {
            option_i = 1;
        }
        else if (strcmp(argv[i], "-Q") == 0)
        {
            option_Q = 1;
        }
        else
        {
            dir = argv[i];
        }
    }

    if (dir == NULL)
    {
        dir = ".";
    }

    if ((dp = opendir(dir)) == NULL)
    {
        perror(dir);
        return 1; 
    }

    while ((d = readdir(dp)) != NULL)
    {
     
        if (!option_a && d->d_name[0] == '.')
            continue;

        sprintf(path, "%s/%s", dir, d->d_name);
        if (lstat(path, &st) < 0)
        {
            perror(path);
        }
        else
        {
            if (option_p)
            {
                printFullPath(dir, d->d_name, option_p);
            }
            else
            {
                printStat(path, d->d_name, &st, option_l, option_i, option_Q, option_p);
            }
        }
    }

    closedir(dp);
    return 0;
}

void printStat(char *pathname, char *file, struct stat *st, int option_l, int option_i, int option_Q, int option_p)
{
    if (option_l)
    {
        printf("%5d ", st->st_blocks);
        printf("%c%s ", type(st->st_mode), perm(st->st_mode));
        printf("%3d ", st->st_nlink);

        // Check if getpwuid or getgrgid returns NULL
        struct passwd *pwd = getpwuid(st->st_uid);
        struct group *grp = getgrgid(st->st_gid);
        if (pwd != NULL)
        {
            printf("%s ", pwd->pw_name);
        }
        else
        {
            perror("getpwuid");
        }

        if (grp != NULL)
        {
            printf("%s ", grp->gr_name);
        }
        else
        {
            perror("getgrgid");
        }

        printf("%9d ", st->st_size);
        printf("%.12s ", ctime(&st->st_mtime) + 4);
    }

    if (option_i)
    {
        printf("%ld ", (long)st->st_ino);
    }

    if (option_Q)
    {
        printf("\"%s\"", file);
    }
    else
    {
        printf("%s", file);
    }

    if (option_p && S_ISDIR(st->st_mode))
    {
        printf("/");
    }

    if (!option_l) 
    {
        printf("\n");
    }
}

void printFullPath(char *dir, char *file, int option_p)
{
    char fullpath[BUFSIZ + 1];
    sprintf(fullpath, "%s/%s", dir, file);

    if (option_p)
    {
        struct stat st;
        if (stat(fullpath, &st) == 0)
        {
            if (S_ISDIR(st.st_mode))
            {
                printf("%s/\n", fullpath);
                return;
            }
        }
    }

    printf("%s\n", fullpath);
}

char type(mode_t mode)
{
    if (S_ISREG(mode))
        return '-';
    if (S_ISDIR(mode))
        return 'd';
    if (S_ISCHR(mode))
        return 'c';
    if (S_ISBLK(mode))
        return 'b';
    if (S_ISLNK(mode))
        return 'l';
    if (S_ISFIFO(mode))
        return 'p';
    if (S_ISSOCK(mode))
        return 's';
    return '?';
}

char *perm(mode_t mode)
{
    static char perms[10];
    strcpy(perms, "---------");

    for (int i = 0; i < 3; i++)
    {
        if (mode & (S_IRUSR >> i * 3))
            perms[i * 3] = 'r';
        if (mode & (S_IWUSR >> i * 3))
            perms[i * 3 + 1] = 'w';
        if (mode & (S_IXUSR >> i * 3))
            perms[i * 3 + 2] = 'x';
    }
    return (perms);
}

int main(int argc, char **argv)
{
    return myls_main(argc, argv);
}

