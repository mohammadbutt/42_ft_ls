/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 19:45:19 by mbutt             #+#    #+#             */
/*   Updated: 2019/10/04 16:24:56 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>


void printdir(char *dir, int depth)
{
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
	int spaces = depth*4;

    if((dp = opendir(dir)) == NULL)
	{
        fprintf(stderr,"cannot open directory: %s\n", dir);
        return;
    }
    chdir(dir);
    while((entry = readdir(dp)) != NULL)
	{
        lstat(entry->d_name,&statbuf);
        if(S_ISDIR(statbuf.st_mode))
		{
            if(entry->d_name[0] != '.')
			{
			printf("%*s%s/\n",spaces,"",entry->d_name);
            printdir(entry->d_name,depth+1);
			}
        }
        else printf("%*s%s\n",spaces,"",entry->d_name);
    }
    chdir("..");
    closedir(dp);
}

/*  Now we move onto the main function.  */

int main(int argc, char* argv[])
{
    char *topdir, pwd[2]=".";
    if (argc != 2)
        topdir=pwd;
    else
        topdir=argv[1];

    printf("Directory scan of %s\n",topdir);
    printdir(topdir,0);
    printf("done.\n");

    return 0;
}
