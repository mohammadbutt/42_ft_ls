/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_file_name.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 00:29:22 by mbutt             #+#    #+#             */
/*   Updated: 2019/11/07 00:54:37 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_invalid_file_name(t_ls *ls)
{
	int		i;
	char	*invalid_str;

	i = 0;
	while (ls)
	{
		invalid_str = ls->file_name;
		ft_printf("ft_ls: ");
		perror(invalid_str);
		ls = ls->next;
	}
}

void	print_uppercase_g(char *str, struct stat meta)
{
	if (S_ISDIR(meta.st_mode))
		ft_printf(BLUE"%s\n"NC, str);
	else if (meta.st_mode & S_IXUSR)
		ft_printf(RED"%s\n"NC, str);
	else
		ft_printf("%s\n", str);
}

void	format_and_print(t_ls *ls, t_info *info, char *str, char *link_str)
{
	struct stat meta;

	while (ls)
	{
		lstat(ls->file_name, &meta);
		str[0] = 0;
		if (ls->slash_index >= 0)
			ft_substring(str, ls->file_name, ls->slash_index);
		else if (ls->slash_index < 0)
			ft_strcpy(str, ls->file_name);
		if (info->flag.l == true)
			long_file_listing(meta, ls->file_name, info);
		if (S_ISLNK(meta.st_mode) && info->flag.l == true)
			file_is_link(link_str, ls->file_name, str);
		else if (info->flag.uppercase_g == true)
			print_uppercase_g(str, meta);
		else
			ft_printf("%s\n", str);
		ls = ls->next;
	}
}

void	print_file_name(t_ls *ls, t_info *info)
{
	char *str;
	char *link_str;

	info->pad_size = 0;
	info->pad_nlink = 0;
	link_str = NULL;
	str = malloc(sizeof(char) * (_POSIX_PATH_MAX));
	if (str == NULL)
		return ;
	if (info->flag.l == true)
	{
		link_str = malloc(sizeof(char) * (_POSIX_PATH_MAX));
		padding_and_blocks_total(ls, &info->pad_nlink, &info->pad_size);
	}
	format_and_print(ls, info, str, link_str);
	free(str);
	if (info->flag.l == true)
		free(link_str);
}
