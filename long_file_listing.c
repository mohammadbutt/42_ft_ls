/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_file_listing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 23:11:19 by mbutt             #+#    #+#             */
/*   Updated: 2019/11/06 23:11:27 by mbutt            ###   ########.fr       */
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

/*
** skip_day_and_space = 4 because time string's first three characters are to
** represent a day + 1 for space.
** To calulate time in years, take time in seconds and divide it by 86,400 sec
** per day and divide it by 365 days, so to convert 1,572,511,743 seconds into
** years, we would do:
** (1572511743 seconds / 86400 seconds per day) / 365 days = 49.86 years.
*/

void	month_date_time_column(struct stat meta)
{
	struct timespec	last_modified;
	time_t			seconds_since_epoch;
	char			*month_date;
	char			*time_or_year;
	char			*time_str;

	last_modified = meta.st_mtimespec;
	seconds_since_epoch = time(&seconds_since_epoch);
	time_str = ctime(&meta.st_mtimespec.tv_sec);
	month_date = malloc(sizeof(char) * (8));
	time_or_year = malloc(sizeof(char) * (8));
	if (month_date == NULL || time_or_year == NULL)
		return ;
	month_date[0] = 0;
	time_or_year[0] = 0;
	ft_printf("%s ", ft_substr_start_end(month_date, time_str, 4, 6));
	if ((seconds_since_epoch - last_modified.tv_sec) < SIX_MONTH)
		ft_printf("%s ", ft_substr_start_end(time_or_year, time_str, 11, 5));
	else if ((seconds_since_epoch - last_modified.tv_sec) >= SIX_MONTH)
		ft_printf("%5s ", ft_substr_start_end(time_or_year, time_str, 20, 4));
	free(month_date);
	free(time_or_year);
}

void	long_file_listing(struct stat meta, char *file_name, t_info *info)
{
	permission_column(meta, file_name);
	ft_printf("%*d ", info->pad_nlink, meta.st_nlink);
	if (getpwuid(meta.st_uid)->pw_name)
		ft_printf("%s  ", getpwuid(meta.st_uid)->pw_name);
	if (getgrgid(meta.st_gid)->gr_name)
		ft_printf("%s  ", getgrgid(meta.st_gid)->gr_name);
	ft_printf("%*d ", info->pad_size, meta.st_size);
	month_date_time_column(meta);
}
