/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 23:17:38 by mbutt             #+#    #+#             */
/*   Updated: 2019/11/06 23:59:01 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	two_arguments(t_ls *ls, t_ls *temp_ls, t_info *info, char *path)
{
	if (info->flag.uppercase_r == false)
		single_argument(ls, info, path);
	else if (info->flag.uppercase_r == true)
	{
		temp_ls = store_root_files(temp_ls, info, path);
		info->skip_print = false;
		start_recursive_call(temp_ls, info);
		delete_list_file_name(&temp_ls);
	}
}

void	more_than_two_arguments(t_ls *ls, t_info *info, int i)
{
	info->skip_print = true;
	info->no_dot_slash = true;
	info->var.temp_i = i;
	process_dir(ls, info);
}

void	ls_start_parsing(t_ls *ls, t_info *info)
{
	t_ls	*temp_ls;
	int		i;
	int		j;
	char	current;

	i = 1;
	j = 1;
	current = info->argv[i][0];
	temp_ls = NULL;
	initialize_t_info_struct_variables(info);
	if ((current != '-') || (current == '-' && info->argv[i][1] == '\0'))
		handle_improper_usage_of_dash(ls, info);
	else if (info->argv[i][0] == '-' && info->argv[i][1] != '\0')
	{
		i = set_up_environment_to_collect_flags(info, i, j);
		if (i == info->argc && (flag_status(info) == false))
			single_argument(ls, info, ".");
		else if (i == 2 && info->argc == 2 && flag_status(info) == true)
			two_arguments(ls, temp_ls, info, ".");
		else if (i < info->argc)
			more_than_two_arguments(ls, info, i);
	}
}

void	merge_delete_append_slash(t_ls *ls, t_info *info, char *dir_path_str)
{
	t_ls *new_ls;

	new_ls = NULL;
	if (ls != NULL)
		new_ls = append_slash(new_ls, ls, dir_path_str);
	delete_list_file_name(&ls);
	merge_sort(&new_ls, info);
	print_file_name(new_ls, info);
	delete_list_file_name(&new_ls);
}

void	single_argument(t_ls *ls, t_info *info, char *dir_path_str)
{
	struct dirent	*data;
	DIR				*dir;

	dir = opendir(dir_path_str);
	if (dir == NULL)
		ft_permission_denied(dir_path_str);
	else if (dir != NULL)
	{
		if (info->flag.a == true)
			while ((data = readdir(dir)) != NULL)
				ls = store_file_name_with_index(ls, data->d_name, 0);
		else if (info->flag.a == false)
			while ((data = readdir(dir)) != NULL)
				if (data->d_name[0] != '.')
					ls = store_file_name_with_index(ls, data->d_name, 0);
	}
	if (dir != NULL)
	{
		closedir(dir);
		merge_delete_append_slash(ls, info, dir_path_str);
	}
}
