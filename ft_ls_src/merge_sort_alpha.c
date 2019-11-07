/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort_alpha.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 19:11:43 by mbutt             #+#    #+#             */
/*   Updated: 2019/11/06 19:21:43 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_ls	*sorted_merge_alpha(t_ls *a, t_ls *b)
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
		result->next = sorted_merge_alpha(a->next, b);
	}
	else
	{
		result = b;
		result->next = sorted_merge_alpha(a, b->next);
	}
	return (result);
}

t_ls	*sorted_merge_alpha_reverse(t_ls *a, t_ls *b)
{
	t_ls *result;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (ft_strcmp(b->file_name, a->file_name) > 0)
	{
		result = b;
		result->next = sorted_merge_alpha_reverse(a, b->next);
	}
	else
	{
		result = a;
		result->next = sorted_merge_alpha_reverse(a->next, b);
	}
	return (result);
}

void	front_back_split(t_ls *source, t_ls **front_ref, t_ls **back_ref)
{
	t_ls *fast;
	t_ls *slow;

	slow = source;
	fast = source->next;
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*front_ref = source;
	*back_ref = slow->next;
	slow->next = NULL;
}

void	merge_sort(t_ls **head_ref, t_info *info)
{
	t_ls *head;
	t_ls *a;
	t_ls *b;

	head = *head_ref;
	if (head == NULL || head->next == NULL)
		return ;
	front_back_split(head, &a, &b);
	merge_sort(&a, info);
	merge_sort(&b, info);
	if (info->flag.r == false && info->flag.t == false)
		*head_ref = sorted_merge_alpha(a, b);
	else if (info->flag.r == true && info->flag.t == false)
		*head_ref = sorted_merge_alpha_reverse(a, b);
	else if (info->flag.t == true && info->flag.r == false)
		*head_ref = sorted_merge_time(a, b);
	else if (info->flag.t == true && info->flag.r == true)
		*head_ref = sorted_merge_time_reverse(a, b);
}
