/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort_time.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 19:21:53 by mbutt             #+#    #+#             */
/*   Updated: 2019/11/06 19:36:20 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_ls	*sorted_merge_time_nano_second(t_ls *a, t_ls *b)
{
	t_ls		*result;
	struct stat	meta1;
	struct stat	meta2;

	result = NULL;
	lstat(a->file_name, &meta1);
	lstat(b->file_name, &meta2);
	if (meta1.st_mtimespec.tv_nsec > meta2.st_mtimespec.tv_nsec)
	{
		result = a;
		result->next = sorted_merge_time(a->next, b);
	}
	else
	{
		result = b;
		result->next = sorted_merge_time(a, b->next);
	}
	return (result);
}

t_ls	*sorted_merge_time(t_ls *a, t_ls *b)
{
	t_ls		*result;
	struct stat meta1;
	struct stat meta2;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	lstat(a->file_name, &meta1);
	lstat(b->file_name, &meta2);
	if (meta1.st_mtimespec.tv_sec > meta2.st_mtimespec.tv_sec)
	{
		result = a;
		result->next = sorted_merge_time(a->next, b);
	}
	else if (meta1.st_mtimespec.tv_sec == meta2.st_mtimespec.tv_sec)
		result = sorted_merge_time_nano_second(a, b);
	else
	{
		result = b;
		result->next = sorted_merge_time(a, b->next);
	}
	return (result);
}

t_ls	*sorted_merge_time_nano_second_reverse(t_ls *a, t_ls *b)
{
	t_ls		*result;
	struct stat meta1;
	struct stat meta2;

	result = NULL;
	lstat(a->file_name, &meta1);
	lstat(b->file_name, &meta2);
	if (meta1.st_mtimespec.tv_nsec < meta2.st_mtimespec.tv_nsec)
	{
		result = a;
		result->next = sorted_merge_time_reverse(a->next, b);
	}
	else
	{
		result = b;
		result->next = sorted_merge_time_reverse(a, b->next);
	}
	return (result);
}

t_ls	*sorted_merge_time_reverse(t_ls *a, t_ls *b)
{
	t_ls		*result;
	struct stat meta1;
	struct stat meta2;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	lstat(a->file_name, &meta1);
	lstat(b->file_name, &meta2);
	if (meta1.st_mtimespec.tv_sec < meta2.st_mtimespec.tv_sec)
	{
		result = a;
		result->next = sorted_merge_time_reverse(a->next, b);
	}
	else if (meta1.st_mtimespec.tv_sec == meta2.st_mtimespec.tv_sec)
		result = sorted_merge_time_nano_second_reverse(a, b);
	else
	{
		result = b;
		result->next = sorted_merge_time_reverse(a, b->next);
	}
	return (result);
}
