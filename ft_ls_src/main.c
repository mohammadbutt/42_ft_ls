/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 01:16:19 by mbutt             #+#    #+#             */
/*   Updated: 2019/11/07 01:38:27 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

t_ls	*store_root_files(t_ls *ls, t_info *info, char *dir_path_str)
{
	struct dirent	*data;
	DIR				*dir;

	dir = opendir(dir_path_str);
	if (dir == NULL)
		return (ls);
	if (info->flag.a == true)
		while ((data = readdir(dir)) != NULL)
			ls = store_file_name(ls, data->d_name);
	else if (info->flag.a == false)
		while ((data = readdir(dir)) != NULL)
			if (data->d_name[0] != '.')
				ls = store_file_name(ls, data->d_name);
	if (dir != NULL)
		closedir(dir);
	merge_sort(&ls, info);
	return (ls);
}

int		main(int argc, char *argv[])
{
	t_ls	*ls;
	t_info	info;

	ls = NULL;
	ft_bzero(&info, sizeof(&info));
	info.argc = argc;
	info.argv = argv;
	if (argc == 1)
		single_argument(ls, &info, ".");
	else if (argc > 1)
		ls_start_parsing(ls, &info);
	if (ls)
		delete_list_file_name(&ls);
	return (0);
}
