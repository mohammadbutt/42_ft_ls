/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_field_d_i.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 22:38:52 by mbutt             #+#    #+#             */
/*   Updated: 2019/09/16 16:12:16 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** length_field_d determines what data type is the in the given argument for d.
** Type casts to 'char' for 'hh'. Type casts to 'short' for 'h'.
*/

int_fast64_t	length_field_d(t_printf *pr)
{
	int_fast64_t num;

	num = 0;
	if (pr->length.hh == true)
		num = (char)va_arg(pr->arguments, int);
	else if (pr->length.h == true)
		num = (short)va_arg(pr->arguments, int);
	else if (pr->length.l == true)
		num = va_arg(pr->arguments, long);
	else if (pr->length.ll == true)
		num = va_arg(pr->arguments, long long);
	else
		num = va_arg(pr->arguments, int);
	return (num);
}

/*
** s = str, t_s = temp_str
*/

void			d_append_buffer(t_printf *pr, char s[], char t_s[])
{
	int len;

	len = ft_strlen(t_s);
	pr->var.precision = ft_pad(pr->precision_field, len);
	if (s[0] == '-')
		pr->var.width = ft_pad(pr->width_field, len + pr->var.precision + 1);
	else
		pr->var.width = ft_pad(pr->width_field, len + pr->var.precision);
	if (pr->flag.plus == true || pr->flag.space == true)
		if (pr->var.width > 0 && s[0] != '-')
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

/*
** n = num or number, s = str, t_s = temp_str
*/

/*
** For d type_field, 'll' length_field can print a 19 digits number with a range
** from -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807.
** This would require 21 bytes of memory to account for negative sign and '\0'
** null termination, but 32 bytes are allocated to stay consistent with power of
** 2.
** Since 'll' is the biggest length_field for d type_field, all other
** length fields 'hh','h', 'l' will be safely covered are stored with 32 bytes.
**
** Note: 'l' long and 'll' long long has the same value range.
** .0 means there's 0 precision_field, which is a valid precision .1 means
** there's 1 precision_field, which is also a valid precision. This is why
** precision_field is initialized to -1 which would means precision was not
** invoked.
** If there is precision and the precision value is equal to 0 or greater than
** 0, it would cancel out the zero flag and make it false.
**
** precision is stored first and then width is calculated. precision over width.
** Precision does not count the negative sign in the length of the number:
** printf("|%.5hhd|\n", -128) will give output of |-00128|
** printf("|%.5hhd|\n",  127) will give output of |00127|
**
** Width counts the negative sign in the length of the number:
** printf("|%5hhd|\n", -128) will give output of | -128|
** printf("|%5hhd|\n",  127) will give output of |  127|
*/

void			collect_d(t_printf *pr)
{
	int_fast64_t	n;
	char			s[ft_abs(pr->precision_field) + pr->width_field + 32];
	char			t_s[ft_abs(pr->precision_field) + pr->width_field + 32];

	s[0] = 0;
	t_s[0] = 0;
	ft_bzero(&pr->var, sizeof(pr->var));
	n = 0;
	n = length_field_d(pr);
	if (n < 0)
	{
		ft_strcpy(s, "-");
		ft_itoa_min(pr, n, t_s);
	}
	else
	{
		if (pr->flag.plus == true)
			ft_strcpy(s, "+");
		else if (pr->flag.space == true)
			ft_strcpy(s, " ");
		ft_itoa_base(n, FT_DECIMAL, t_s);
	}
	(pr->precision_field != -1) && (pr->flag.zero = false);
	(pr->precision_field == 0 && n == 0) && (ft_strcpy(t_s, NULL));
	d_append_buffer(pr, s, t_s);
}
