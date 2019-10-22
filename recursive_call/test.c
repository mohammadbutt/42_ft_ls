/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 19:39:35 by mbutt             #+#    #+#             */
/*   Updated: 2019/10/03 19:41:40 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/dir.h>

void listdir(char *dir)
{
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    char *subdir;

    if((dp = opendir(dir)) == NULL)
    {
        fprintf(stderr,"cannot open directory: %s\n", dir);
        return;
    }

    while((entry = readdir(dp)) != NULL)
    {
        if(lstat(entry->d_name, &statbuf) == 0)
        {
            if(statbuf.st_mode & S_IFDIR)
            {
                /* Found a directory, but ignore . and .. */
                if(strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
                    continue;

                // allocate space for parent directory, "/", subdir, plus NULL terminator
                subdir = malloc(strlen(dir) + strlen(entry->d_name) + 2);
                // Concatenate directory name
                strcpy(subdir, dir);
                strcat(subdir, "/");
                strcat(subdir, entry->d_name);

                /* Recurse at a new indent level */
                listdir(subdir);
                free(subdir);
            }
            else
            {
                // Print file name
                printf("%s/%s\n", dir, entry->d_name);
            }
        }
    }

    closedir(dp);
}

int main(void)
{
	listdir(".");
}
