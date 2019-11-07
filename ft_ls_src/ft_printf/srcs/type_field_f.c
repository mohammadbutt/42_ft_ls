/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_field_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 22:07:00 by mbutt             #+#    #+#             */
/*   Updated: 2019/09/16 18:10:16 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	f_append_buffer(t_printf *pr, char s[], char t_s[])
{
	int len;

	len = ft_strlen(t_s);
	pr->var.precision = ft_pad(pr->precision_field, len);
	pr->var.width = ft_pad(pr->width_field, len + pr->var.precision);
	if (pr->flag.plus == true || pr->flag.space == true || s[0] == '-')
		if (pr->var.width > 0)
			pr->var.width--;
	if (pr->flag.zero == true && pr->var.width >= 0)
		ft_strcat_loop(s, pr->var.width, "0");
	else if (pr->flag.zero == false && pr->flag.minus == false)
		append_to_buffer_loop(pr, pr->var.width, " ");
	else if (pr->flag.minus == true)
		ft_strcat_loop(t_s, pr->var.width, " ");
	if (pr->var.precision >= 0)
		ft_strcat_loop(s, pr->var.precision, "0");
	ft_strcat(s, t_s);
	append_to_buffer(pr, s);
}

void	collect_f(t_printf *pr)
{
	long double	nbr;
	char		s[ft_abs(pr->precision_field) + pr->width_field + 64];
	char		t_s[ft_abs(pr->precision_field) + pr->width_field + 64];

	nbr = 0;
	s[0] = 0;
	t_s[0] = 0;
	if (pr->length.uppercase_l == true)
		nbr = va_arg(pr->arguments, long double);
	else if (pr->length.uppercase_l == false)
		nbr = va_arg(pr->arguments, double);
	if (nbr < 0)
		ft_strcpy(s, "-");
	else if (nbr >= 0)
	{
		if (pr->flag.plus == true)
			ft_strcpy(s, "+");
		else if (pr->flag.space == true)
			ft_strcpy(s, " ");
	}
	ft_ftoa(nbr, t_s, pr->precision_field);
	if (pr->precision_field == 0 && pr->flag.hash == true)
		ft_strcat(t_s, ".");
	f_append_buffer(pr, s, t_s);
}
