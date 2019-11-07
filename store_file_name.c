/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_file_name.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 20:00:03 by mbutt             #+#    #+#             */
/*   Updated: 2019/11/06 20:12:14 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Storing file names and directory paths in a linked list
*/

t_ls	*store_file_name(t_ls *ls, char *file_name)
{
	if (ls == NULL)
		ls = create(file_name);
	else
		ls = append(ls, file_name);
	return (ls);
}

t_ls	*create(char *valid_file_path_str)
{
	t_ls *new_node;

	new_node = malloc(sizeof(t_ls));
	if (new_node == NULL)
		exit(EXIT_SUCCESS);
	new_node->file_name = ft_strdup(valid_file_path_str);
	new_node->next = NULL;
	return (new_node);
}

t_ls	*append(t_ls *head, char *valid_file_path_str)
{
	t_ls *cursor;
	t_ls *new_node;

	cursor = head;
	while (cursor->next != NULL)
		cursor = cursor->next;
	new_node = create(valid_file_path_str);
	cursor->next = new_node;
	return (head);
}
