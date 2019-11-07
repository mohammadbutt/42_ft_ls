/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort_invalid_file.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 19:45:53 by mbutt             #+#    #+#             */
/*   Updated: 2019/11/06 19:51:17 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_ls	*sorted_merge_invalid_file_name(t_ls *a, t_ls *b)
{
	t_ls *result;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (ft_strcmp(a->file_name, b->file_name) <= 0)
	{
		result = a;
		result->next = sorted_merge_invalid_file_name(a->next, b);
	}
	else
	{
		result = b;
		result->next = sorted_merge_invalid_file_name(a, b->next);
	}
	return (result);
}

/*
** One seperate merge sort is created for invalid files because invalid files
** are always sorted in lexical order regardless of what flags there are.
*/

void	merge_sort_invalid_file_name(t_ls **head_ref)
{
	t_ls *head;
	t_ls *a;
	t_ls *b;

	head = *head_ref;
	if (head == NULL || head->next == NULL)
		return ;
	front_back_split(head, &a, &b);
	merge_sort_invalid_file_name(&a);
	merge_sort_invalid_file_name(&b);
	*head_ref = sorted_merge_invalid_file_name(a, b);
}
