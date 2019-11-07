/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 13:55:03 by mbutt             #+#    #+#             */
/*   Updated: 2019/10/01 18:25:18 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/dir.h>
#include <sys/stat.h>
#include <limits.h>
int ft_strlen(char *str)
{
	int i;

	i = 0;
	if(str)
		while(str[i])
			i++;
	return(i);
}

char *ft_strcpy(char *dest, char *source)
{
	int i;

	i = 0;
	if(source)
		while(source[i])
		{
			dest[i] = source[i];
			i++;
		}
	dest[i] = '\0';
	return(dest);
}

char *ft_strcat(char *dest, char *source)
{
	int i;
	int j;

	i = ft_strlen(dest);
	j = 0;
	if(source)
		while(source[j])
			dest[i++] = source[j++];
	dest[i] = '\0';
	return(dest);
}
/*
** 1. stat(dirent->d_name, &stat) has to be called first
** 2. S_ISDIR(stat.st_mode) is used to idetify if a given file is directory.
** Since the above order matters: in the below if statement stat has to appear
** first:
** if((stat(full_path, &meta) == 0) && (S_ISDIR(meta.st_mode) == 1))
**
** swapping the order of stat with S_ISDIR as shown below will not work:
** if((S_ISDIR(meta.st_mode) == 1) && (stat(full_path, &meta) == 0))
**
** Return Values:
** 1 means it is a directory.
** 0 means it is a file.
** -1 mean it is an invalid file.
** _POSIX_PATH_MAX can store upto 256 characters
*/
int implement_recurssion(char *path)
{
	struct dirent	*dr;
	struct stat		meta;
	DIR *dir;
	char full_path[_POSIX_PATH_MAX];

//	dir = opendir(path);
//	if(dir == NULL)
//		return(0);
	if((dir = opendir(path)) == NULL)
		return(0);
	while((dr = readdir(dir)) != NULL)
	{
		ft_strcpy(full_path, path);
		(full_path[ft_strlen(path) - 1] != '/')	&& (ft_strcat(full_path, "/"));
		ft_strcat(full_path, dr->d_name);
		if((stat(full_path, &meta) == 0) && (S_ISDIR(meta.st_mode) == 1))
		{
			if(dr->d_name[0] != '.')
			{
				printf("%s\n", full_path);
				implement_recurssion(full_path);
			}
		}
	}
	closedir(dir);
	return(0);
}

int main(void)
{
	implement_recurssion(".");
}
