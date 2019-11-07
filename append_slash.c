/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_slash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 00:00:31 by mbutt             #+#    #+#             */
/*   Updated: 2019/11/07 00:25:24 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

t_ls *get_new_ls(t_ls *new_ls, t_ls *temp_ls, char *full_path, int slash_i)
{
	char *ref_str;
	int i;
	int j;

	i = 0;
	j = 0;
	while(temp_ls && temp_ls->file_name)
	{
		ref_str = temp_ls->file_name;
		i = slash_i;
		j = 0;

		if(ft_strcmp(ref_str, ".") == 0 || ft_strcmp(ref_str, "..") == 0)
			new_ls = store_file_name_with_index(new_ls, ref_str, 0);
		else
		{
			while(ref_str[j])
				full_path[i++] = ref_str[j++];
			full_path[i] = '\0';
			new_ls = store_file_name_with_index(new_ls, full_path, slash_i);
		}
		temp_ls = temp_ls->next;
	}
	return(new_ls);
}

t_ls	*append_slash(t_ls *new_ls, t_ls *temp_ls, char *path)
{
	char *full_path;
	int i;
	int j;
	int slash_i;

	full_path = malloc(sizeof(char) * (_POSIX_PATH_MAX));
	i = 0;
	j = 0;
	slash_i = 0;
	full_path[0] = 0;
	if(path)
	{
		while(path[j])
			full_path[i++] = path[j++];
		(full_path[i - 1] != '/') && (full_path[i++] = '/');
		full_path[i] = '\0';
	}
	slash_i = i;
	new_ls = get_new_ls(new_ls, temp_ls, full_path, slash_i);
	free(full_path);
	return(new_ls);
}
