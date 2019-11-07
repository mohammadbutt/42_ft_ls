/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_and_blocks_total.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 22:39:47 by mbutt             #+#    #+#             */
/*   Updated: 2019/11/06 22:43:44 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int get_link_padding(t_ls *ls)
{
	struct stat	meta;
	int			padding;
	int			numlen;

	padding = 0;
	numlen = 0;
	while (ls)
	{
		lstat(ls->file_name, &meta);
		numlen = ft_numlen(meta.st_nlink, FT_DECIMAL);
		(numlen > padding) && (padding = numlen);
		ls = ls->next;
	}
	return (padding);
}

int get_size_padding(t_ls *ls)
{
	struct stat	meta;
	int			padding;
	int			numlen;

	padding = 0;
	numlen = 0;
	while (ls)
	{
		lstat(ls->file_name, &meta);
		numlen = ft_numlen(meta.st_size, FT_DECIMAL);
		(numlen > padding) && (padding = numlen);
		ls = ls->next;
	}
	return (padding);
}

int find_max(int num1, int num2)
{
	if (num1 > num2)
		return (num1);
	return (num2);
}

void padding_and_blocks_total(t_ls *ls, int *pad_nlink, int *pad_size)
{
	struct stat	meta;
	int			numlen_nlink;
	int			numlen_size;
	int			total;

	numlen_nlink = 0;
	numlen_size = 0;
	total = 0;
	while (ls)
	{
		stat(ls->file_name, &meta);
		total = total + meta.st_blocks;
		*pad_nlink = find_max(ft_numlen(meta.st_nlink, FT_DECIMAL), *pad_nlink);
		*pad_size = find_max(ft_numlen(meta.st_size, FT_DECIMAL), *pad_size);
		ls = ls->next;
	}
	ft_printf("total %d\n", total);
}
