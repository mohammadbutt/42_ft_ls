/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_this6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 18:53:33 by mbutt             #+#    #+#             */
/*   Updated: 2019/10/01 16:40:20 by mbutt            ###   ########.fr       */
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
    struct stat fstat;
	char	full_name[_POSIX_PATH_MAX + 1];
	struct dirent *direntp = NULL;
    DIR *dirp = NULL;
    size_t path_len;

//   if (path == NULL)
//		return(-1);
	path_len = strlen(path);
	
//	if(path == NULL || path_len == 0 || path_len > _POSIX_PATH_MAX)
//		return(-1);
    dirp = opendir(path);
    if (dirp == NULL)
      return -1;

    while ((direntp = readdir(dirp)) != NULL)
    {
//		if(path[2] != '.')
  //      	if((path_len + strlen(direntp->d_name) + 1) < _POSIX_PATH_MAX)
		strcpy(full_name, path);
        (full_name[path_len - 1] != '/') && (strcat(full_name, "/"));
        strcat(full_name, direntp->d_name);
        if((direntp->d_name[0] != '.') && (stat(full_name, & fstat) >= 0))
			if (S_ISDIR(fstat.st_mode))
        	{
            	printf("%s\n", full_name);
//            	if (recursive)
                	print_dirs(full_name, 1);
        	}
    }
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
