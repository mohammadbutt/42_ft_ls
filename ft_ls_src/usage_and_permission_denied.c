/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage_and_permission_denied.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 22:34:38 by mbutt             #+#    #+#             */
/*   Updated: 2019/11/06 22:34:47 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** If a flag is not valid at any point. The program will end and by giving the
** illegal option message.
*/

void	ft_exit_illegal_option(char c)
{
	ft_printf("ft_ls: illegal option -- %c\n", c);
	ft_printf("usage: ft_ls [-latrRG] [file ...]\n");
	exit(EXIT_SUCCESS);
}

void	ls_collect_flag_and_illegal_option(t_info *info, int i, int j)
{
	if (is_flag_valid(info->argv[i][j]) == true)
		ls_collect_flags(info, info->argv[i][j]);
	else if (is_flag_valid(info->argv[i][j]) == false)
		ft_exit_illegal_option(info->argv[i][j]);
}

/*
** perror will handle following errors:
** 1. No such file or directory - Currently only works with directory. Need to
** make it work with files.
** 2. Permission denied.
** If a folder has permission denied via chmod 000 folder_name or file_name,
** then ls will not show contents of that folder. perror will print a message
** saying ... permission denied.
*/

void	ft_permission_denied(char *str)
{
	ft_printf("ft_ls: ");
	perror(str);
}
