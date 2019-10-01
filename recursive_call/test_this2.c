/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_this2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 12:46:07 by mbutt             #+#    #+#             */
/*   Updated: 2019/09/30 18:35:11 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

void listFilesRecursively(char *path);


int main()
{
    // Directory path to list files
    char path[100];

    // Input path from user
    printf("Enter path to list files: ");
    scanf("%s", path);

    listFilesRecursively(path);

    return 0;
}


/**
 * Lists all files and sub-directories recursively 
 * considering path as base path.
 */
void listFilesRecursively(char *basePath)
{
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);
//	DIR *temp_dir; // Added
	int		folder_status;
	struct	stat meta;

    // Unable to open directory stream
    if (!dir)
        return;
    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
//           temp_dir = opendir(dp->d_name);	// Added
//		   if(temp_dir != NULL)				// Added
			folder_status = stat(dp->d_name, &meta);
			printf("|%d|\n", folder_status);
//			if(S_ISREG(meta.st_mode))
				printf("%s\n", dp->d_name);
//			if(temp_dir != NULL)			// Added
//				closedir(temp_dir);			// Added
            // Construct new path from our base path
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            listFilesRecursively(path);
        }
    }

    closedir(dir);
}
