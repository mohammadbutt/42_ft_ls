/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_this.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 12:44:16 by mbutt             #+#    #+#             */
/*   Updated: 2019/09/29 12:46:02 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * C program to list all files and sub-directories in a directory.
 */

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>


void listFiles(const char *path);

int main()
{
    // Directory path to list files
    char path[100];

    // Input path from user
    printf("Enter path to list files: ");
    scanf("%s", path);

    listFiles(path);

    return 0;
}


/**
 * Lists all files and sub-directories at given path.
 */
void listFiles(const char *path)
{
    struct dirent *dp;
    DIR *dir = opendir(path);

    // Unable to open directory stream
    if (!dir) 
        return; 

    while ((dp = readdir(dir)) != NULL)
    {
        printf("%s\n", dp->d_name);
    }

    // Close directory stream
    closedir(dir);
}
