/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 12:04:22 by mbutt             #+#    #+#             */
/*   Updated: 2019/09/16 13:51:47 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	initialize_flag_and_field_values(t_printf *pr)
{
	pr->width_field = 0;
	pr->precision_field = -1;
	pr->length_field = 0;
	pr->type_field = 0;
	ft_bzero(&pr->flag, sizeof(pr->flag));
	ft_bzero(&pr->length, sizeof(pr->length));
}

void	start_collecting_flags(t_printf *pr)
{
	while (collect_flags(pr) != -1)
		pr->i++;
	cancel_flags(pr);
	collect_width(pr);
	collect_precision(pr);
	collect_length(pr);
	collect_type_field(pr);
}

/*
** 0 = c,  1 = s,  2 = p
** 3 = d,  4 = i,  5 = o
** 6 = u,  7 = x,  8 = X
** 9 = f, 10 = b, 11 = %
*/

/*
**void collect_data(t_printf *pr)
**{
**	if(pr->type_field == 0)
**		collect_c(pr);
**	else if(pr->type_field == 1)
**		collect_s(pr);
**	else if(pr->type_field == 2)
**		collect_p(pr);
**	else if(pr->type_field == 3 || pr->type_field == 4)
**		collect_d(pr);
**	else if(pr->type_field == 5)
**		collect_o(pr);
**	else if(pr->type_field == 6)
**		collect_u(pr);
**	else if(pr->type_field == 7 || pr->type_field == 8)
**		collect_x(pr);
**	else if(pr->type_field == 9)
**		collect_f(pr);
**	else if(pr->type_field == 10)
**		collect_b(pr);
**	else if(pr->type_field == 11)
**		collect_percent(pr);
**}
*/

/*
** Above commented function that uses if and else if statements can also be
** used to instead of the disptach table. But I implemented dispatch table to
** learn how it works, which is pretty similar to if and else if statements.
*/

void	collect_data(t_printf *pr)
{
	g_ft_dispatch_table[pr->type_field](pr);
}

void	start_parsing(t_printf *pr)
{
	pr->i++;
	initialize_flag_and_field_values(pr);
	if (pr->string[pr->i] == '\0')
		return ;
	start_collecting_flags(pr);
	collect_data(pr);
}
