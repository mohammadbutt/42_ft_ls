/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_file_listing_permission_column.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 22:51:43 by mbutt             #+#    #+#             */
/*   Updated: 2019/11/06 22:57:05 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	permission_file_type(int file_mode)
{
	char type;

	if (S_ISDIR(file_mode))
		type = 'd';
	else if (S_ISCHR(file_mode))
		type = 'c';
	else if (S_ISBLK(file_mode))
		type = 'b';
	else if (S_ISFIFO(file_mode))
		type = 'p';
	else if (S_ISLNK(file_mode))
		type = 'l';
	else if (S_ISSOCK(file_mode))
		type = 's';
	else
		type = '-';
	return (type);
}

char	extended_attributes(char *file_name)
{
	ssize_t xattr;
	char	character;

	xattr = 0;
	xattr = listxattr(file_name, NULL, 0, XATTR_NOFOLLOW);
	if (xattr > 0)
		character = '@';
	else
		character = ' ';
	return (character);
}

void	permission_column(struct stat meta, char *file_name)
{
	int		i;
	char	extended_character;
	char	permission[12];

	i = 0;
	extended_character = extended_attributes(file_name);
	permission[i++] = permission_file_type(meta.st_mode);
	permission[i++] = (meta.st_mode & S_IRUSR) ? 'r' : '-';
	permission[i++] = (meta.st_mode & S_IWUSR) ? 'w' : '-';
	permission[i++] = (meta.st_mode & S_IXUSR) ? 'x' : '-';
	permission[i++] = (meta.st_mode & S_IRGRP) ? 'r' : '-';
	permission[i++] = (meta.st_mode & S_IWGRP) ? 'w' : '-';
	permission[i++] = (meta.st_mode & S_IXGRP) ? 'x' : '-';
	permission[i++] = (meta.st_mode & S_IROTH) ? 'r' : '-';
	permission[i++] = (meta.st_mode & S_IWOTH) ? 'w' : '-';
	permission[i++] = (meta.st_mode & S_IXOTH) ? 'x' : '-';
	permission[i++] = extended_character;
	permission[i] = '\0';
	ft_printf("%s ", permission);
}
