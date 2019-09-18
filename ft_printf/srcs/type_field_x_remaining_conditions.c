/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_field_x_remaining_conditions.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 15:09:32 by mbutt             #+#    #+#             */
/*   Updated: 2019/09/16 20:06:01 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	x_width_y_precision_n2(t_printf *pr, char str[], char str_hex[])
{
	if (pr->flag.hash == false)
	{
		if (pr->flag.zero == false)
			append_to_buffer_loop(pr, pr->var.width, " ");
		else if (pr->flag.zero == true)
			append_to_buffer_loop(pr, pr->var.width, "0");
		append_to_buffer(pr, str);
	}
	else if (pr->flag.hash == true)
	{
		if (pr->flag.zero == false)
			append_to_buffer_loop(pr, pr->var.width, " ");
		else if (pr->flag.zero == true)
			ft_strcat_loop(str_hex, pr->var.width, "0");
		ft_strcat(str_hex, str);
		append_to_buffer(pr, str_hex);
	}
}

void	x_width_y_precision_n(t_printf *pr, uint_fast64_t n)
{
	char	str[pr->width_field + 32];
	char	str_hex[pr->width_field + 32];
	int		total_length;

	str[0] = 0;
	str_hex[0] = 0;
	ft_bzero(&pr->var, sizeof(&pr->var));
	if (pr->type_field == 7)
		ft_hex(n, 'x', str);
	else if (pr->type_field == 8)
		ft_hex(n, 'X', str);
	check_flags_for_x(pr, str_hex, n);
	total_length = ft_strlen(str) + ft_strlen(str_hex);
	pr->var.width = ft_pad(pr->width_field, total_length);
	if (pr->flag.minus == true)
	{
		ft_strcat_loop(str, pr->var.width, " ");
		ft_strcat(str_hex, str);
		append_to_buffer(pr, str_hex);
		return ;
	}
	else if (pr->flag.minus == false)
		x_width_y_precision_n2(pr, str, str_hex);
}

void	x_width_y_precision_y2(t_printf *pr, char str[], char str_hex[])
{
	if (pr->flag.minus == true)
	{
		ft_strcat_loop(str_hex, pr->var.precision, "0");
		ft_strcat_loop(str, pr->var.width, " ");
		ft_strcat(str_hex, str);
		append_to_buffer(pr, str_hex);
	}
	else if (pr->flag.minus == false)
	{
		append_to_buffer_loop(pr, pr->var.width, " ");
		if (pr->flag.hash == false)
		{
			append_to_buffer_loop(pr, pr->var.precision, "0");
			append_to_buffer(pr, str);
		}
		else if (pr->flag.hash == true)
		{
			ft_strcat_loop(str_hex, pr->var.precision, "0");
			ft_strcat(str_hex, str);
			append_to_buffer(pr, str_hex);
		}
	}
}

void	x_width_y_precision_y(t_printf *pr, uint_fast64_t n)
{
	char	str[pr->width_field + ft_abs(pr->precision_field) + 32];
	char	str_hex[pr->width_field + ft_abs(pr->precision_field) + 32];
	int		l_s;
	int		l_s_h;

	str[0] = 0;
	str_hex[0] = 0;
	ft_bzero(&pr->var, sizeof(&pr->var));
	(pr->type_field == 7) && (ft_hex(n, 'x', str));
	(pr->type_field == 8) && (ft_hex(n, 'X', str));
	check_flags_for_x(pr, str_hex, n);
	l_s_h = ft_strlen(str_hex);
	l_s = ft_strlen(str);
	(n == 0 && pr->precision_field == 0) && (l_s = 0);
	pr->var.precision = ft_pad(pr->precision_field, l_s);
	pr->var.width = ft_pad(pr->width_field, l_s + l_s_h + pr->var.precision);
	if (n == 0 && pr->precision_field == 0)
	{
		ft_strcpy(str, NULL);
		ft_strcat_loop(str, pr->var.width, " ");
		append_to_buffer(pr, str);
		return ;
	}
	x_width_y_precision_y2(pr, str, str_hex);
}
