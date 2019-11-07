/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_to_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 11:15:04 by mbutt             #+#    #+#             */
/*   Updated: 2019/09/12 18:52:21 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Function append_to_buffe works just like strcat, but it takes in the struct
** and source string to append.
** Destination string and index inside the struct are used to append the source
** to the end of the destination.
** RETURN VALUE: Concatenated destination string
*/

void	append_to_buffer(t_printf *pr, char *source)
{
	int i;

	i = 0;
	if (source)
		while (source[i])
			pr->buffer[pr->buffer_i++] = source[i++];
	pr->buffer[pr->buffer_i] = '\0';
}

/*
** Function append_to_buffer_in_loop will append the string or a character in a
** while loop as many times as the x_times value.
**
** Note: Uses ft_str_append function so the string, or character will be
** appended at the end of the buffer and buffer_index will be incremented
*/

void	append_to_buffer_loop(t_printf *pr, int x_times, char *str)
{
	if (str[1] != '\0')
		while (x_times--)
			append_to_buffer(pr, str);
	else if (str[1] == '\0')
		while (x_times--)
			pr->buffer[pr->buffer_i++] = str[0];
}
