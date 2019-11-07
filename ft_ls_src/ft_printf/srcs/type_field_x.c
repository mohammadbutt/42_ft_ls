/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_field_x.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 15:00:55 by mbutt             #+#    #+#             */
/*   Updated: 2019/09/16 20:06:05 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_flags_for_x(t_printf *pr, char s[], uint_fast64_t n)
{
	if (pr->flag.hash == true && n != 0 && pr->type_field == 7)
		ft_strcpy(s, "0x");
	else if (pr->flag.hash == true && n != 0 && pr->type_field == 8)
		ft_strcpy(s, "0X");
}

void	x_width_n_precision_n(t_printf *pr, uint_fast64_t n)
{
	char str[32];
	char str_hex[32];

	str[0] = 0;
	str_hex[0] = 0;
	ft_bzero(&pr->var, sizeof(&pr->var));
	if (pr->type_field == 7)
		ft_hex(n, 'x', str);
	else if (pr->type_field == 8)
		ft_hex(n, 'X', str);
	check_flags_for_x(pr, str_hex, n);
	ft_strcat(str_hex, str);
	append_to_buffer(pr, str_hex);
}

void	x_width_n_precision_y(t_printf *pr, uint_fast64_t n)
{
	char str[ft_abs(pr->precision_field) + 32];
	char str_hex[ft_abs(pr->precision_field) + 32];

	str[0] = 0;
	str_hex[0] = 0;
	ft_bzero(&pr->var, sizeof(&pr->var));
	if (pr->type_field == 7)
		ft_hex(n, 'x', str);
	else if (pr->type_field == 8)
		ft_hex(n, 'X', str);
	check_flags_for_x(pr, str_hex, n);
	if (n == 0 && pr->precision_field == 0)
	{
		ft_strcpy(str, NULL);
		append_to_buffer(pr, str);
		return ;
	}
	pr->var.precision = ft_pad(pr->precision_field, ft_strlen(str));
	if (pr->flag.hash == false)
		append_to_buffer_loop(pr, pr->var.precision, "0");
	else if (pr->flag.hash == true)
		ft_strcat_loop(str_hex, pr->var.precision, "0");
	ft_strcat(str_hex, str);
	append_to_buffer(pr, str_hex);
}

void	collect_x(t_printf *pr)
{
	uint_fast64_t n;

	n = 0;
	n = length_field_uox(pr);
	if (pr->width_field == 0 && pr->precision_field == -1)
		x_width_n_precision_n(pr, n);
	else if (pr->width_field == 0 && pr->precision_field != -1)
		x_width_n_precision_y(pr, n);
	else if (pr->width_field != 0 && pr->precision_field == -1)
		x_width_y_precision_n(pr, n);
	else if (pr->width_field != 0 && pr->precision_field != -1)
		x_width_y_precision_y(pr, n);
}
