/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_linked_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 20:25:47 by mbutt             #+#    #+#             */
/*   Updated: 2019/11/06 20:31:20 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	delete_list_file_name(t_ls **head_ref)
{
	t_ls *current_node;
	t_ls *next_node;

	current_node = *head_ref;
	while (current_node != NULL)
	{
		next_node = current_node->next;
		if (current_node->file_name)
			free(current_node->file_name);
		if (current_node)
			free(current_node);
		current_node = next_node;
	}
	*head_ref = NULL;
}

/*
void	delete_list_file_name(t_ls **head_ref)
{
	t_ls *current_node;
//	t_ls *next_node;

	current_node = *head_ref;
	while (current_node != NULL)
	{
//		next_node = current_node->next;
		if (current_node->file_name)
			free(current_node->file_name);
		if (current_node)
			free(current_node);
//		current_node = next_node;
		current_node = current_node->next;
	}
	free(*head_ref);
	*head_ref = NULL;
}
*/
