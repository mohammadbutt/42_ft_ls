/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:59:19 by mbutt             #+#    #+#             */
/*   Updated: 2019/11/06 22:32:22 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** If a flag is not valid at any point. The program will end and by giving the
** illegal option message.
*/

/*
void ft_exit_illegal_option(char c)
{
	ft_printf("ft_ls: illegal option -- %c\n", c);
	ft_printf("usage: ft_ls [-latrRG] [file ...]\n");
	exit(EXIT_SUCCESS);
}


void	ls_collect_flag_and_illegal_option(t_info *info, int i, int j)
{
	if(is_flag_valid(info->argv[i][j]) == true)
		ls_collect_flags(info, info->argv[i][j]);
	else if(is_flag_valid(info->argv[i][j]) == false)
		ft_exit_illegal_option(info->argv[i][j]);
}

*/
/*
** perror will handle following errors:
** 1. No such file or directory - Currently only works with directory. Need to
** make it work with files.
** 2. Permission denied.
** If a folder has permission denied via chmod 000 folder_name or file_name,
** then ls will not show contents of that folder. perror will print a message
** saying ... permission denied.
*/

/*
void ft_permission_denied(char *str)
{
	ft_printf("ft_ls: ");
	perror(str);
}
*/




void print_invalid_file_name(t_ls *ls)
{
	int i;
	char *invalid_str;
	
	i = 0;
	while(ls)
	{
		invalid_str = ls->file_name;
		ft_printf("ft_ls: ");
		perror(invalid_str);
		ls = ls->next;
	}
}
t_ls	*store_root_files(t_ls *ls, t_info *info, char *dir_path_str);


/*
** function find_last_slash, returns the index of the last slash that occurs in
** a file path.
** Functions is used in permission denied case, so slashes can be truncated
** from the beginning of the file path, so just the name is returned.
*/

int find_last_slash(char *file_path_with_slash)
{
	int len;

	len = 0;
	len = ft_strlen(file_path_with_slash) - 1;

	if(len <= 0)
		return(0);
	while(len)
	{
		if(file_path_with_slash[len] == '/')
			return(len + 1);
		len--;
	}
	return(0);
}

t_ls	*append_slash(t_ls *new_ls, t_ls *temp_ls, char *path)
{
	char *full_path;
	int i;
	int j;
	int reset_i;
	char *ref_str;
	
	full_path = malloc(sizeof(char) * (_POSIX_PATH_MAX));
	i = 0;
	j = 0;
	reset_i = 0;
	full_path[0] = 0;
	if(path)
	{
		while(path[j])
			full_path[i++] = path[j++];
		(full_path[i - 1] != '/') && (full_path[i++] = '/');
		full_path[i] = '\0';
	}
	reset_i = i;
	while(temp_ls && temp_ls->file_name)
	{
		ref_str = temp_ls->file_name;
		i = reset_i;
		j = 0;

		if(ft_strcmp(ref_str, ".") == 0 || ft_strcmp(ref_str, "..") == 0)
		{
			new_ls = store_file_name_with_index(new_ls, ref_str, 0);
		}
		else
		{
			while(ref_str[j])
				full_path[i++] = ref_str[j++];
			full_path[i] = '\0';
			new_ls = store_file_name_with_index(new_ls, full_path, reset_i);
		}
		temp_ls = temp_ls->next;
	}
	free(full_path);
	return(new_ls);
}

void	initialize_t_info_struct_variables(t_info *info)
{
	ft_bzero(&info->flag, sizeof(info->flag));
	info->var.temp_i = 1;
	info->var.str_len = 0;
	info->var.double_break = false;
	info->pad_size = 0;
	info->pad_nlink = 0;
	info->total_blocks = 0;
}

t_ls *store_root_files(t_ls *ls, t_info *info, char *dir_path_str)
{
	struct dirent	*data;
	DIR				*dir;

	dir = opendir(dir_path_str);
	if(dir == NULL)
		return(ls);
	if(info->flag.a == true)
		while((data = readdir(dir)) != NULL)
			ls = store_file_name(ls, data->d_name);
	else if(info->flag.a == false)
		while((data = readdir(dir)) != NULL)
			if(data->d_name[0] != '.')
				ls = store_file_name(ls, data->d_name);
	if(dir != NULL)
		closedir(dir);
	merge_sort(&ls, info);
	return(ls);
}

void	ls_start_parsing(t_ls *ls, t_info *info)
{
	t_ls			*temp_ls;
	int				i;
	int				j;
	char			current;

	i = 1;
	j = 1;
	current = info->argv[i][0];
	temp_ls = NULL;

	
	initialize_t_info_struct_variables(info);
	if((current != '-') || (current == '-' && info->argv[i][1] == '\0'))
		handle_improper_usage_of_dash(ls, info);
	else if(info->argv[i][0] == '-' && info->argv[i][1] != '\0')
	{
		i = set_up_environment_to_collect_flags(info, i, j);
		if(i == info->argc && (flag_status(info) == false))
		{
			single_argument(ls, info, ".");
		}
		else if(i == 2 && info->argc == 2 && flag_status(info) == true)
		{
			if(info->flag.uppercase_r == false)
				single_argument(ls, info, ".");
			else if(info->flag.uppercase_r == true)
				{					
					temp_ls = store_root_files(temp_ls, info, ".");
					info->skip_print = false;
					start_recursive_call(temp_ls, info);
					delete_list_file_name(&temp_ls);
				}
			return;
		}
		if (i < info->argc)
		{
				info->skip_print = true;
				info->no_dot_slash = true;
				info->var.temp_i = i;
				process_dir(ls, info);
		}

	}
}

void	initialize_info_values(t_info *info)
{
	ft_bzero(&info->flag, sizeof(info->flag));
}
/*
** Function print_file_name will print contents, files and folders, of the
** current directory.
*/

/*
** Returns a substring
*/
char *ft_substring(char *dest, char *source, int start)
{
    int i;

    i = 0;
    if(source)
        while(source[start])
            dest[i++] = source[start++];
    dest[i] = '\0';
    return(dest);
}

char *ft_substr_start_end(char *dest, char *source, int start, int end)
{
	int i;

	i = 0;

	if(source)
		while(end && source[start])
		{
			dest[i++] = source[start++];
			end--;
		}
	dest[i] = '\0';
	return(dest);
}


void get_total_for_long_listing(t_ls *ls)
{
	struct stat meta;
	int total;

	total = 0;
	while(ls)
	{
		stat(ls->file_name, &meta);
		total = total + meta.st_blocks;
		ls = ls->next;
	}
	ft_printf("total %d\n", total);
}

char permission_file_type(int file_mode)
{
	char type;
	
	if(S_ISDIR(file_mode))
		type = 'd';
	else if(S_ISCHR(file_mode))
		type = 'c';
	else if(S_ISBLK(file_mode))
		type = 'b';
	else if(S_ISFIFO(file_mode))
		type = 'p';
	else if(S_ISLNK(file_mode))
		type = 'l';
	else if(S_ISSOCK(file_mode))
		type = 's';
	else
		type = '-';
	return(type);

}

//char extended_attributes(struct stat meta, char *file_name)
char 	extended_attributes(char *file_name)
{
	ssize_t xattr;
	char character;

	xattr = 0;
	xattr = listxattr(file_name, NULL, 0, XATTR_NOFOLLOW);
	if(xattr > 0)
		character = '@';
	else
		character = ' ';
	return(character);
}

void permission_column(struct stat meta, char *file_name)
{
	int i;
	char extended_character;
	char permission[12];

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

void link_column(struct stat meta, int pad_nlink)
{
	ft_printf("%*d ", pad_nlink, meta.st_nlink);
}

void owner_and_group_column(struct stat meta)
{
	if(getpwuid(meta.st_uid)->pw_name)
		ft_printf("%s  ", getpwuid(meta.st_uid)->pw_name);
	if(getgrgid(meta.st_gid)->gr_name)
		ft_printf("%s  ", getgrgid(meta.st_gid)->gr_name);
}


void size_column(struct stat meta, int pad_size)
{
	ft_printf("%*d ", pad_size, meta.st_size);
}

/*
** skip_day_and_space = 4 because time string's first three characters are to
** represent a day + 1 for space.
** To calulate time in years, take time in seconds and divide it by 86,400 sec
** per day and divide it by 365 days, so to convert 1,572,511,743 seconds into
** years, we would do:
** (1572511743 seconds / 86400 seconds per day) / 365 days = 49.86 years.
*/


void month_date_time_column(struct stat meta)
{
	struct timespec last_modified;
	time_t seconds_since_epoch;
	char *month_date;
	char *time_or_year;
	char *time_str;
	
	last_modified = meta.st_mtimespec;
	seconds_since_epoch = time(&seconds_since_epoch);
	time_str = ctime(&meta.st_mtimespec.tv_sec);
	month_date = malloc(sizeof(char) * (8));
	time_or_year = malloc(sizeof(char) * (8));
	if(month_date == NULL || time_or_year == NULL)
		return;
	month_date[0] = 0;
	time_or_year[0] = 0;

	ft_printf("%s ", ft_substr_start_end(month_date, time_str, 4, 6));	
	if((seconds_since_epoch - last_modified.tv_sec) < SIX_MONTH)
		ft_printf("%s ", ft_substr_start_end(time_or_year, time_str, 11, 5));
	else if((seconds_since_epoch - last_modified.tv_sec) >= SIX_MONTH)
		ft_printf("%5s ", ft_substr_start_end(time_or_year, time_str, 20, 4));
	free(month_date);
	free(time_or_year);
}

void	long_file_listing(struct stat meta, char *file_name, t_info *info)
{
	permission_column(meta, file_name);
	link_column(meta, info->pad_nlink);
	owner_and_group_column(meta);
	size_column(meta, info->pad_size);
	month_date_time_column(meta);
}

int get_link_padding(t_ls *ls)
{
	struct stat meta;
	int padding;
	int numlen;

	padding = 0;
	numlen = 0;
	while (ls)
	{
		lstat(ls->file_name, &meta);
		numlen = ft_numlen(meta.st_nlink, FT_DECIMAL);
		(numlen > padding) && (padding = numlen);
		ls = ls->next;
	}
	return(padding);
}

int get_size_padding(t_ls *ls)
{
	struct stat meta;
	int padding;
	int numlen;

	padding = 0;
	numlen = 0;
	while(ls)
	{
		lstat(ls->file_name, &meta);
		numlen = ft_numlen(meta.st_size, FT_DECIMAL);
		(numlen > padding) && (padding = numlen);
		ls = ls->next;
	}
	return(padding);
}

int find_max(int num1, int num2)
{
	if(num1 > num2)
		return(num1);
	return(num2);
}

void padding_and_blocks_total(t_ls *ls, int *pad_nlink, int *pad_size)
{
	struct stat meta;
	int numlen_nlink;
	int numlen_size;
	int total;

	numlen_nlink = 0;
	numlen_size = 0;
	total = 0;
	while(ls)
	{
		stat(ls->file_name, &meta);
		total = total + meta.st_blocks;
		*pad_nlink = find_max(ft_numlen(meta.st_nlink, FT_DECIMAL), *pad_nlink);
		*pad_size = find_max(ft_numlen(meta.st_size, FT_DECIMAL), *pad_size);
		ls = ls->next;
	}
	ft_printf("total %d\n", total);
}

/*
** stat(2) is an incredibly powerful functions that provides information about
** a filepath. However, it is not good at determining a symbolik link.
** 
** In order to know if a file is a symoblik link, lstat(2) is used instead.
** man 2 stat and man 2 lstat has some really good information and it also
** mentions members of stat struct family and time struct.
*/

void file_is_link(char *link_str, char *ls_file_name, char *str)
{
	ft_bzero(link_str, _POSIX_PATH_MAX);
	readlink(ls_file_name, link_str, _POSIX_PATH_MAX);
	ft_printf("%s -> %s\n", str, link_str);
}

void print_file_name(t_ls *ls, t_info *info)
{
	struct stat meta;
	char *str;
	char *link_str;
	
	info->pad_size = 0;
	info->pad_nlink = 0;
	str = malloc(sizeof(char) * (_POSIX_PATH_MAX));
	if(str == NULL)
		return;
	if(info->flag.l == true)
	{
		link_str = malloc(sizeof(char) * (_POSIX_PATH_MAX));
		padding_and_blocks_total(ls, &info->pad_nlink, &info->pad_size);
	}
	while(ls)
	{

		lstat(ls->file_name, &meta);
		str[0] = 0;
		if(ls->slash_index >= 0)
			ft_substring(str, ls->file_name, ls->slash_index);
		else if(ls->slash_index <= 0)
			ft_strcpy(str, ls->file_name);
		if(info->flag.l == true)
			long_file_listing(meta, ls->file_name, info);
		if(S_ISLNK(meta.st_mode) && info->flag.l == true)
			file_is_link(link_str, ls->file_name, str);
		else if(info->flag.uppercase_g == true)
		{
			if(S_ISDIR(meta.st_mode))
				ft_printf(BLUE"%s\n"NC, str);
			else if(meta.st_mode & S_IXUSR)
				ft_printf(RED"%s\n"NC, str);
			else
				ft_printf("%s\n", str);
		}
		else
			ft_printf("%s\n", str);
		ls = ls->next;
	}

	free(str);
	if(info->flag.l == true)
		free(link_str);
}

/*
** Get count function calculates how many nodes there are, used to determine
** if there are 2 nodes in a linked list, then it breaks and returns count
** if the count is 2 then path will be printed.
*/

int get_count(t_ls *ls)
{
	int count;

	count = 0;
	if(ls)
		while(ls)
		{
			ls = ls->next;
			count++;
			if (count == 2)
				break;
		}
	return(count);
}

/*
** if statement:
** if(data->d_name[0] != '.') -> will help ignore hidden files which begin with
** '.', dot, '..', and dot dot.
** And then it will start storing names of all files and folders in a linked
** list, and as mentioned earlier, but ignore hidden files which begin with '.'
*/

// Works trying to add stat to this
void	single_argument(t_ls *ls, t_info *info, char *dir_path_str)
{
	struct dirent	*data;
	DIR				*dir;
	t_ls 			*new_ls;

	new_ls = NULL;
	dir = opendir(dir_path_str);
	if(dir == NULL)
		ft_permission_denied(dir_path_str);
	else if(dir != NULL)
	{
		while((data = readdir(dir)) != NULL)
		{
			if(info->flag.a == true)
				ls = store_file_name_with_index(ls, data->d_name, 0);
			else if(info->flag.a == false && data->d_name[0] != '.')
				ls = store_file_name_with_index(ls, data->d_name, 0);
		}
	}

	if(dir != NULL)
	{
		closedir(dir);
		if(ls != NULL)
			new_ls = append_slash(new_ls, ls, dir_path_str);
		delete_list_file_name(&ls);
		merge_sort(&new_ls, info);
		print_file_name(new_ls, info);
		delete_list_file_name(&new_ls);
	}
}

int main(int argc, char *argv[])
{
	t_ls	*ls;
	t_info	info;
	

	ls = NULL;
	ft_bzero(&info, sizeof(&info));
	info.argc = argc;
	info.argv = argv;
	if(argc == 1)
		single_argument(ls, &info, ".");
	else if(argc > 1)
		ls_start_parsing(ls, &info);
	if(ls)
		delete_list_file_name(&ls);
	return(0);
}
