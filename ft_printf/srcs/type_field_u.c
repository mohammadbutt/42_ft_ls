/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_field_u.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 11:26:13 by mbutt             #+#    #+#             */
/*   Updated: 2019/09/16 19:43:12 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Function length_field_uox determines what data type is in given argument.
** Type casts to 'unsigned char' for 'hh'.
** Type casts to 'unsigned short' for 'h'.
*/

uint_fast64_t	length_field_uox(t_printf *pr)
{
	uint_fast64_t num;

	num = 0;
	if (pr->length.hh == true)
		num = (unsigned char)va_arg(pr->arguments, unsigned int);
	else if (pr->length.h == true)
		num = (unsigned short)va_arg(pr->arguments, unsigned int);
	else if (pr->length.l == true)
		num = va_arg(pr->arguments, unsigned long);
	else if (pr->length.ll == true)
		num = va_arg(pr->arguments, unsigned long long);
	else
		num = va_arg(pr->arguments, unsigned int);
	return (num);
}

void			u_append_buffer(t_printf *pr, char s[], char t_s[])
{
	int len;

	len = ft_strlen(t_s);
	pr->var.precision = ft_pad(pr->precision_field, len);
	pr->var.width = ft_pad(pr->width_field, len + pr->var.precision);
	if (pr->flag.plus == true && pr->var.width > 0)
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

void			collect_u(t_printf *pr)
{
	uint_fast64_t	n;
	char			s[ft_abs(pr->precision_field) + pr->width_field + 32];
	char			t_s[ft_abs(pr->precision_field) + pr->width_field + 32];

	s[0] = 0;
	t_s[0] = 0;
	ft_bzero(&pr->var, sizeof(&pr->var));
	n = 0;
	n = length_field_uox(pr);
	ft_itoa_base_u(n, FT_DECIMAL, t_s);
	(pr->precision_field != -1) && (pr->flag.zero = false);
	(pr->precision_field == 0 && n == 0) && (ft_strcpy(t_s, NULL));
	u_append_buffer(pr, s, t_s);
}
