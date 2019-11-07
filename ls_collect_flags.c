/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_collect_flags.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 19:12:00 by mbutt             #+#    #+#             */
/*   Updated: 2019/11/06 22:28:27 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** is_flag_valid takes a character and compares it with VALID_FLAG string,
** "latrR", if the character appears then it's valid and returns 1, if the
** character does nor appear in VALID_FLAG, "latrR", then the character is
** invalid and will return 0.
** Return Values: true for valid. false for invalid
*/

bool	is_flag_valid(char c)
{
	int i;

	i = 0;
	while (VALID_FLAG[i])
	{
		if (VALID_FLAG[i] == c)
			return (true);
		i++;
	}
	return (false);
}

void	ls_collect_flags(t_info *info, char c)
{
	if (c == 'l')
		info->flag.l = true;
	else if (c == 'a')
		info->flag.a = true;
	else if (c == 't')
		info->flag.t = true;
	else if (c == 'r')
		info->flag.r = true;
	else if (c == 'R')
		info->flag.uppercase_r = true;
	else if (c == 'G')
		info->flag.uppercase_g = true;
}

/*
** Function handle_improper_usage_of_dash handles the edge cases with dash.
** 1. If the 0th character of the 1st argument is not a '-', dash.
** 2. If the 0th character of the 1st argument is a '-', dash, but 1st character
** is '\0', which means '-', dash, is the only chracter present.
** Below are some of the commands it will handle:
** ./ft_ls abc
** If abc folder does not exist, it will print:
** "ft_ls: abc: No such file or directory"
**
** ./ft_ls abc
** If abc folder exists it will will print contents of that folder.
**
** ./ft_ls
** It will print contents of the current/root directory.
**
** For the second if statement:
** ./ft_ls -
** It will print conetns of the folder if there is a directory named '-'. But
** if a directory does not exist with the name of '-', then it will print the
** following message.
** ft_ls: -: No such file or directory
*/

void	handle_improper_usage_of_dash(t_ls *ls, t_info *info)
{
	int i;

	i = 1;
	if (info->argv[i][0] != '-')
		process_dir(ls, info);
	else if (info->argv[i][0] == '-' && info->argv[i][1] == '\0')
		process_dir(ls, info);
}

/*
** Function flag status returns 1 or true if one of the flags are active.
** If there are no flags, then it returns false or 0.
*/

bool	flag_status(t_info *info)
{
	if (info->flag.l == true || info->flag.a == true || info->flag.t == true)
		return (true);
	else if (info->flag.r == true || info->flag.uppercase_r == true)
		return (true);
	else if (info->flag.uppercase_g == true)
		return (true);
	return (false);
}

int		set_up_environment_to_collect_flags(t_info *info, int i, int j)
{
	while (i < info->argc)
	{
		info->var.str_len = ft_strlen(info->argv[i]);
		while (j < info->var.str_len)
		{
			if (info->argv[i][0] == '-')
			{
				(j == 0) && (j = 1);
				ls_collect_flag_and_illegal_option(info, i, j);
			}
			else if (info->argv[i][0] != '-')
				return (i);
			j++;
		}
		j = 0;
		i++;
	}
	return (i);
}
