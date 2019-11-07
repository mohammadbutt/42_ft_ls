/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_recursive_call.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 20:58:33 by mbutt             #+#    #+#             */
/*   Updated: 2019/11/06 21:58:43 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_dir_path_for_recursion(t_info *info, char *path)
{
	if (info->skip_print == false)
	{
		if (info->no_dot_slash == false)
			ft_printf("\n./%s:\n", path);
		else if (info->no_dot_slash == true)
			ft_printf("\n%s:\n", path);
	}
	else if (info->print_path_name == true)
		ft_printf("%s:\n", path);
}

t_ls	*store_inner_recursive_files(t_ls *temp_ls, t_info *info, DIR *dir)
{
	struct dirent *dr;

	if (info->flag.a == true)
		while ((dr = readdir(dir)) != NULL)
			temp_ls = store_file_name(temp_ls, dr->d_name);
	else if (info->flag.a == false)
		while ((dr = readdir(dir)) != NULL)
			if (dr->d_name[0] != '.')
				temp_ls = store_file_name(temp_ls, dr->d_name);
	if (dir != NULL)
		closedir(dir);
	return (temp_ls);
}

t_ls	*store_file_recursively(t_info *info, char *path)
{
	DIR		*dir;
	t_ls	*temp_ls;
	t_ls	*new_ls;

	temp_ls = NULL;
	new_ls = NULL;
	dir = opendir(path);
	if (dir == NULL)
	{
		(info->no_dot_slash == false) && (ft_printf(BRED"\n./%s\n"NC, path));
		(info->no_dot_slash == true) && (ft_printf(BRED"\n%s\n"NC, path));
		ft_permission_denied(path + find_last_slash(path));
		return (NULL);
	}
	else if (info->skip_print == false || info->print_path_name == true)
		print_dir_path_for_recursion(info, path);
	temp_ls = store_inner_recursive_files(temp_ls, info, dir);
	(temp_ls != NULL) && (new_ls = append_slash(new_ls, temp_ls, path));
	delete_list_file_name(&temp_ls);
	merge_sort(&new_ls, info);
	return (new_ls);
}

/*
** I had initially decided to store the inner directories on stack as below:
** char full_path[_POSIX_PATH_MAX]
** _POSIX_PATH_MAX which allocates 256 bytes, so I decided to find out the total
** number of files on my current system to get an approximate idea how much
** memory will be reseverd on stack.
** running the below command gave me the total number of files at the root:
** ls -R | wc -l
** This was 45,238.
** 45,238 * 256 = 11,580,928.
** When I allocated this much memory on stack, well it didn't work, but malloc
** will allow memory allocation of upto INT_MAX, which is 2,147,483,647.
** Now there are two nice things about malloc in this case:
** 1. We are able to allocate more memory than stack.
** 2. Memory allocated using malloc can be used again when it's free, but that's
** not the case when memory is allocated on stack, when memory is allocated on
** stack, it can not be freed, the only way would be to reuse that variable
** that has memory on stack.
** Ran a few more test. Might be able to store file names on stack.
** Each occurence can have upto 26,000 recursivce calls.
** skip_first_print is used because when valid directory names are entered,
** they get stored in a linked list: to avoid printing the valid directory
** name right in the beginning skip_first_print is set to true for the first
** time, but when it enters second recursion false is passed in.
** for ./ft_ls -R skip_first_print is set to false because in that case, root
** files and directories need to be printed.
*/

void	handle_inner_dir(t_ls *inner_dir, t_info *info, char *ref_str)
{
	if (info->flag.a == false && ref_str[0] != '.')
		inner_dir = store_file_recursively(info, ref_str);
	else if (info->flag.a == true)
		inner_dir = store_file_recursively(info, ref_str);
	info->skip_print = false;
	if (inner_dir != NULL)
	{
		start_recursive_call(inner_dir, info);
		delete_list_file_name(&inner_dir);
	}
}

int		start_recursive_call(t_ls *temp_ls, t_info *info)
{
	t_ls		*inner_dir;
	struct stat	meta;
	char		*ref_str;

	inner_dir = NULL;
	if (temp_ls != NULL && temp_ls->file_name && info->skip_print == false)
		print_file_name(temp_ls, info);
	while (temp_ls != NULL)
	{
		ref_str = temp_ls->file_name;
		if (ft_strcmp(ref_str, ".") != 0 && ft_strcmp(ref_str, "..") != 0)
			if (stat(ref_str, &meta) == 0 && S_ISDIR(meta.st_mode))
				handle_inner_dir(inner_dir, info, ref_str);
		temp_ls = temp_ls->next;
	}
	return (0);
}
