/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_dir_valid.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 20:42:32 by mbutt             #+#    #+#             */
/*   Updated: 2019/11/06 20:48:57 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** info->var.i = i
** info->argv = arg_string
** info->argc = arg_count
** When storing valid directories, all the directories are stored including the
** ones that have permission denied.
** if(dir != NULL)
**		temp_ls = store_valid_dir(temp)
** Above if statement will work, but it will not store directories that have
** permission denied, which is why the below if statement is used to store the
** directories, including the ones that have permission denied:
**
** 	if(stat(info->argv[info->var.i], &meta) == 0)
**		if(S_ISDIR(meta.st_mode) == 1)
**			temp_ls = store_valid_dir(temp);
*/

t_ls	*store_dir_path(t_ls *temp_ls, t_info *info)
{
	struct stat	meta;
	DIR			*dir;

	while (info->var.i < info->argc)
	{
		dir = opendir(info->argv[info->var.i]);
		if (stat(info->argv[info->var.i], &meta) == 0)
			if (S_ISDIR(meta.st_mode) == 1)
				temp_ls = store_file_name(temp_ls, info->argv[info->var.i]);
		(dir != NULL) && (closedir(dir));
		info->var.i++;
	}
	return (temp_ls);
}

void	files_from_stored_dir_path(t_ls *ls, t_ls *temp_ls, t_info *info)
{
	int number_of_nodes;

	number_of_nodes = get_count(temp_ls);
	while (temp_ls)
	{
		(info->var.new_line == true) && (write(1, "\n", 1));
		(number_of_nodes == 2) && (ft_printf("%s:\n", temp_ls->file_name));
		single_argument(ls, info, temp_ls->file_name);
		info->var.new_line = true;
		temp_ls = temp_ls->next;
	}
}

void	process_dir_valid(t_ls *ls, t_info *info)
{
	t_ls	*temp_ls_dir;

	temp_ls_dir = NULL;
	temp_ls_dir = store_dir_path(temp_ls_dir, info);
	merge_sort(&temp_ls_dir, info);
	if (info->flag.uppercase_r == false)
	{
		files_from_stored_dir_path(ls, temp_ls_dir, info);
		delete_list_file_name(&temp_ls_dir);
	}
	else if (info->flag.uppercase_r == true)
	{
		info->var.new_line = false;
		if (get_count(temp_ls_dir) == 2)
			info->print_path_name = true;
		else
			info->print_path_name = false;
		start_recursive_call(temp_ls_dir, info);
		delete_list_file_name(&temp_ls_dir);
	}
}

/*
** function process_dir does the below three things and the order matters.
** which is why the functions is split into three parts.
** 1. process_invalid_file is called to store names of files that do not
** exist, to store them in a linked list, sort them in lexical order and then
** invalid file names are printed.
** 2. process_valid_file is then called to store names of files that are
** actually valid, these are files they may not have a file extension and may
** simply just be a file called file_1, or they may have a file extension,
** such as file_1.c, file_1.o file_1.txt. As long as the file is valid, it is
** stored in a linked list, sorted via merge sort, and then printed.
** 3. process_dir_valid is then called to store the names of folders. Names of
** the folders are stored in a linked list, sorted using merge sort.
** Then names of sorted folders are passed through so the contents of each
** folder can be printed.
*/

void	process_dir(t_ls *ls, t_info *info)
{
	info->var.new_line = false;
	info->print_path_name = false;
	info->var.i = info->var.temp_i;
	process_invalid_file(ls, info);
	info->var.i = info->var.temp_i;
	process_valid_file(ls, info);
	info->var.i = info->var.temp_i;
	process_dir_valid(ls, info);
}
