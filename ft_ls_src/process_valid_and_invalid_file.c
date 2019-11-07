/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_valid_and_invalid_file.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 20:49:12 by mbutt             #+#    #+#             */
/*   Updated: 2019/11/06 20:57:31 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	process_invalid_file(t_ls *ls, t_info *info)
{
	struct stat	meta;
	int			file_status;
	char		**arg_str;
	int			arg_count;
	int			i;

	arg_str = info->argv;
	arg_count = info->argc;
	i = info->var.i;
	while (i < arg_count)
	{
		file_status = stat(arg_str[i], &meta);
		if (file_status == -1)
			ls = store_file_name(ls, arg_str[i]);
		i++;
	}
	if (ls != NULL)
	{
		merge_sort_invalid_file_name(&ls);
		print_invalid_file_name(ls);
		delete_list_file_name(&ls);
		info->print_path_name = true;
		info->no_dot_slash = true;
	}
}

/*
** In function process_valid_file.
** If a directory/folder has permission denied, it will still be able to go
** through the below if statement
** 	if((stat(arg_str[i], &meta) == 0) && (opendir(arg_str[i]) == NULL))
** which is why an additional if statement will be placed:
** 	if(S_ISREG(meta.st_mode))
** This if statement will determine if a file is a regular file or not.
**
** The below one liner can also check if its a valid file as well as a
** directory:
** if((stat(arg_str[i], &meta) == 0) && (S_ISREG(meta.st_mode)));
*/

void	process_valid_file(t_ls *ls, t_info *info)
{
	struct stat	meta;
	char		**arg_str;
	int			arg_count;
	int			i;

	arg_str = info->argv;
	arg_count = info->argc;
	i = info->var.i;
	while (i < arg_count)
	{
		if ((stat(arg_str[i], &meta) == 0) && (S_ISREG(meta.st_mode)))
			ls = store_file_name(ls, arg_str[i]);
		i++;
	}
	if (ls != NULL)
	{
		merge_sort(&ls, info);
		print_file_name(ls, info);
		delete_list_file_name(&ls);
		info->var.new_line = true;
		info->print_path_name = true;
		info->no_dot_slash = true;
	}
}
