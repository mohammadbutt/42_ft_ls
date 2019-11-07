/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:59:19 by mbutt             #+#    #+#             */
/*   Updated: 2019/11/07 00:25:18 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
