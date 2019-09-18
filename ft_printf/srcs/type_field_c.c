/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_field_c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 10:59:14 by mbutt             #+#    #+#             */
/*   Updated: 2019/09/13 15:03:12 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	collect_c(t_printf *pr)
{
	int c;
	int repeat;

	c = va_arg(pr->arguments, int);
	repeat = 0;
	if (pr->width_field > 0)
		repeat = pr->width_field - 1;
	if (pr->flag.minus == false)
	{
		if (pr->flag.zero == true)
			append_to_buffer_loop(pr, repeat, "0");
		else if (pr->flag.zero == false)
			append_to_buffer_loop(pr, repeat, " ");
		pr->buffer[pr->buffer_i++] = c;
	}
	else if (pr->flag.minus == true)
	{
		pr->buffer[pr->buffer_i++] = c;
		append_to_buffer_loop(pr, repeat, " ");
	}
}
