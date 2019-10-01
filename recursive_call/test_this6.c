/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_this6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 18:53:33 by mbutt             #+#    #+#             */
/*   Updated: 2019/09/30 19:06:56 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <limits.h>

/*
** Actually works - Need to modify a few things
*/

int print_dirs(const char *path, int recursive)
{
    struct dirent *direntp = NULL;
    DIR *dirp = NULL;
    size_t path_len;

    /* Check input parameters. */
    if (!path)
        return -1;
    path_len = strlen(path);  

    if (!path || !path_len || (path_len > _POSIX_PATH_MAX))
        return -1;

    /* Open directory */
    dirp = opendir(path);
    if (dirp == NULL)
        return -1;

    while ((direntp = readdir(dirp)) != NULL)
    {
        /* For every directory entry... */
        struct stat fstat;
        char full_name[_POSIX_PATH_MAX + 1];

        /* Calculate full name, check we are in file length limts */
        if ((path_len + strlen(direntp->d_name) + 1) > _POSIX_PATH_MAX)
            continue;

        strcpy(full_name, path);
        if (full_name[path_len - 1] != '/')
            strcat(full_name, "/");
        strcat(full_name, direntp->d_name);

        /* Ignore special directories. */
        if ((strcmp(direntp->d_name, ".") == 0) ||
            (strcmp(direntp->d_name, "..") == 0))
            continue;

        /* Print only if it is really directory. */
        if (stat(full_name, &fstat) < 0)
            continue;
        if (S_ISDIR(fstat.st_mode))
        {
            printf("%s\n", full_name);
            if (recursive)
                print_dirs(full_name, 1);
        }
    }

    /* Finalize resources. */
    (void)closedir(dirp);
    return 0;
}

/* We are taking first argument as initial path name. */
int main(int argc, const char* argv[])
{
    if (argc < 2)
        return -1;

    print_dirs(argv[1], 1);
    return 0;
}
