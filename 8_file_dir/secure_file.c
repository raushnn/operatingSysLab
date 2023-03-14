#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>

int ends_with(const char *str, const char *suffix) {
    size_t len_str = strlen(str);
    size_t len_suffix = strlen(suffix);
    
    if (len_str < len_suffix) {
        return 0;
    }

    const char *p = str + len_str - len_suffix;
    return strcmp(p, suffix) == 0;
}


int main(int argc, char *argv[])
{
    DIR *dir;
    struct dirent *dirEntry;
    struct stat inode;
    char file_name[1000];
    char extn[7];
    char command[1000];
    sprintf(extn, "%s", argv[2]);

    if (argc != 3)
    {
        printf("Usage: secure_file <dir_name> <extn> \n");
        return 1;
    }

    dir = opendir(argv[1]);

    if (dir == 0)
    {
        printf("Error while opening the dir\n");
        exit(1);
    }
    sprintf(command, "ls -l %s", argv[1]);
    system(command);
    mode_t new_perms = 0700;
    while ((dirEntry = readdir(dir)) != 0)
    {

        sprintf(file_name, "%s/%s", argv[1], dirEntry->d_name);
        if (ends_with(file_name, extn))
        {
            if (chmod(file_name, new_perms) == 0)
            {
                printf("sucess\n");
            }
            else
            {
                printf("Unsucc\n");
            }
        }

        // printf(" %s\n", dirEntry->d_name);
    }
    printf("After removing permission");
    system(command);
}