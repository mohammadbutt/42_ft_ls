/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 00:58:19 by mbutt             #+#    #+#             */
/*   Updated: 2019/11/07 01:13:28 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_substring(char *dest, char *source, int start)
{
	int i;

	i = 0;
	if (source)
		while (source[start])
			dest[i++] = source[start++];
	dest[i] = '\0';
	return (dest);
}

char	*ft_substr_start_end(char *dest, char *source, int start, int end)
{
	int i;

	i = 0;
	if (source)
		while (end && source[start])
		{
			dest[i++] = source[start++];
			end--;
		}
	dest[i] = '\0';
	return (dest);
}

void	get_total_for_long_listing(t_ls *ls)
{
	struct stat	meta;
	int			total;

	total = 0;
	while (ls)
	{
		stat(ls->file_name, &meta);
		total = total + meta.st_blocks;
		ls = ls->next;
	}
	ft_printf("total %d\n", total);
}

void	file_is_link(char *link_str, char *ls_file_name, char *str)
{
	ft_bzero(link_str, _POSIX_PATH_MAX);
	readlink(ls_file_name, link_str, _POSIX_PATH_MAX);
	ft_printf("%s -> %s\n", str, link_str);
}

/*
** Get count function calculates how many nodes there are, used to determine
** if there are 2 nodes in a linked list, then it breaks and returns count
** if the count is 2 then path will be printed.
*/

int		get_count(t_ls *ls)
{
	int count;

	count = 0;
	if (ls)
		while (ls)
		{
			ls = ls->next;
			count++;
			if (count == 2)
				break ;
		}
	return (count);
}
