/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_file_name_with_index.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 20:08:20 by mbutt             #+#    #+#             */
/*   Updated: 2019/11/06 20:12:09 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Storing file names in a linked list with slash index
*/

t_ls	*create_with_index(char *valid_file_path_str, int index)
{
	t_ls *new_node;

	new_node = malloc(sizeof(t_ls));
	if (new_node == NULL)
		exit(EXIT_SUCCESS);
	new_node->file_name = ft_strdup(valid_file_path_str);
	new_node->slash_index = index;
	new_node->next = NULL;
	return (new_node);
}

t_ls	*append_with_index(t_ls *head, char *valid_file_path_str, int index)
{
	t_ls *cursor;
	t_ls *new_node;

	cursor = head;
	while (cursor->next != NULL)
		cursor = cursor->next;
	new_node = create_with_index(valid_file_path_str, index);
	cursor->next = new_node;
	return (head);
}

t_ls	*store_file_name_with_index(t_ls *ls, char *file_name, int index)
{
	if (ls == NULL)
		ls = create_with_index(file_name, index);
	else
		ls = append_with_index(ls, file_name, index);
	return (ls);
}
