/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_field_percent.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 11:07:38 by mbutt             #+#    #+#             */
/*   Updated: 2019/09/12 20:05:40 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	collect_percent(t_printf *pr)
{
	int repeat;

	repeat = 0;
	if (pr->width_field > 0)
		repeat = pr->width_field - 1;
	if (pr->flag.minus == false)
	{
		if (pr->flag.zero == true)
			append_to_buffer_loop(pr, repeat, "0");
		else if (pr->flag.zero == false)
			append_to_buffer_loop(pr, repeat, " ");
		pr->buffer[pr->buffer_i++] = pr->string[pr->i];
	}
	else if (pr->flag.minus == true)
	{
		pr->buffer[pr->buffer_i++] = pr->string[pr->i];
		append_to_buffer_loop(pr, repeat, " ");
	}
}
