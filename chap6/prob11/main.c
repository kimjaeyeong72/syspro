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
void listDir(char *, int, int, int, int, int, int);
char *quoteIfNeeded(char *, int);

int main(int argc, char **argv)
{
    char *dir = ".";
    int show_hidden = 0;
    int show_details = 0;
    int recursive = 0;
    int show_permissions = 0;
    int show_inode = 0;
    int show_quoted = 0;

    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "-a") == 0)
        {
            show_hidden = 1;
        }
        else if (strcmp(argv[i], "-l") == 0)
        {
            show_details = 1;
        }
        else if (strcmp(argv[i], "-R") == 0)
        {
            recursive = 1;
        }
        else if (strcmp(argv[i], "-p") == 0)
        {
            show_permissions = 1;
        }
        else if (strcmp(argv[i], "-i") == 0)
        {
            show_inode = 1;
        }
        else if (strcmp(argv[i], "-Q") == 0)
        {
            show_quoted = 1;
        }
        else
        {
            dir = argv[i];
        }
    }

    listDir(dir, show_hidden, show_details, recursive, show_permissions, show_inode, show_quoted);

    return 0;
}

void listDir(char *dir, int show_hidden, int show_details, int recursive, int show_permissions, int show_inode, int show_quoted)
{
    DIR *dp;
    struct stat st;
    struct dirent *d;
    char path[BUFSIZ + 1];

    if ((dp = opendir(dir)) == NULL)
    {
        perror(dir);
        exit(EXIT_FAILURE);
    }

    printf("%s:\n", dir);

    while ((d = readdir(dp)) != NULL)
    {
        if (!show_hidden && d->d_name[0] == '.')
        {
            continue;
        }

        sprintf(path, "%s/%s", dir, d->d_name);

        if (lstat(path, &st) < 0)
        {
            perror(path);
        }
        else
        {
            if (show_details)
            {
                printStat(path, d->d_name, &st, show_permissions, show_inode, show_quoted);
            }
            else
            {
                printf("%s\n", show_quoted ? quoteIfNeeded(d->d_name, 1) : d->d_name);
            }

            if (recursive && S_ISDIR(st.st_mode) && strcmp(d->d_name, ".") != 0 && strcmp(d->d_name, "..") != 0)
            {
                listDir(path, show_hidden, show_details, recursive, show_permissions, show_inode, show_quoted);
            }
        }
    }

    closedir(dp);
}

void printStat(char *pathname, char *file, struct stat *st, int show_permissions, int show_inode, int show_quoted)
{
    if (show_inode)
    {
        printf("%lu ", st->st_ino);
    }

    printf("%s ", show_quoted ? quoteIfNeeded(file, 1) : file);

    if (show_permissions)
    {
        printf("%s ", perm(st->st_mode));
    }

    printf("%5d ", st->st_blocks);
    printf("%c%s ", type(st->st_mode), perm(st->st_mode));
    printf("%3d ", st->st_nlink);
    printf("%s %s ", getpwuid(st->st_uid)->pw_name, getgrgid(st->st_gid)->gr_name);
    printf("%9d ", st->st_size);
    printf("%.12s ", ctime(&st->st_mtime) + 4);
    printf("\n");
}

char type(mode_t mode)
{
    if (S_ISREG(mode))
        return('-');
    if (S_ISDIR(mode))
        return('d');
    if (S_ISCHR(mode))
        return('c');
    if (S_ISBLK(mode))
        return('b');
    if (S_ISLNK(mode))
        return('l');
    if (S_ISFIFO(mode))
        return('p');
    if (S_ISSOCK(mode))
        return('s');
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

char *quoteIfNeeded(char *str, int show_quoted)
{
    static char quoted_str[BUFSIZ + 3]; // 큰따옴표로 둘러싸인 문자열의 최대 길이는 BUFSIZ + 2
    if (show_quoted)
    {
        snprintf(quoted_str, sizeof(quoted_str), "\"%s\"", str);
        return quoted_str;
    }
    else
    {
        return str;
    }
}

