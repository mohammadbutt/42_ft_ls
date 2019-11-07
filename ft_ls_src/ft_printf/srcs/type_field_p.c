/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_field_p.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 22:39:47 by mbutt             #+#    #+#             */
/*   Updated: 2019/09/16 19:06:58 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	p_append_buffer(t_printf *pr, char *str, int re_width, int re_precision)
{
	if (pr->flag.minus == false)
	{
		if (pr->flag.zero == false)
		{
			append_to_buffer_loop(pr, re_width, " ");
			append_to_buffer(pr, "0x");
		}
		if (pr->precision_field > 0 && re_precision > 0)
			append_to_buffer_loop(pr, re_precision, "0");
		append_to_buffer(pr, str);
	}
	else if (pr->flag.minus == true)
	{
		append_to_buffer(pr, "0x");
		if (pr->precision_field > 0 && re_precision > 0)
			append_to_buffer_loop(pr, re_precision, "0");
		append_to_buffer(pr, str);
		append_to_buffer_loop(pr, re_width, " ");
	}
}

/*
** p type_field gives a number which goes over int max range of 2147483647, but
** it is upto 10 digits long. Because the pointer number cannot be stored in an
** int or int32_t, int_fast64_t is used which uses 8 bytes or 64 bits and has
** enough range to store the pointer value that is generated.
**
** When the pointer is converted to a hexadecimal value, it can be  upto
** 11 characters long + 1 for '\0', so allocating 12 bytes of memory would be
** sufficient, but 16 bytes of memory is allocated to stay consistent with the
** power of 2. Since memory is tied to cpu having a power of 2 requires less
** logic and computational power.
*/

void	collect_p(t_printf *pr)
{
	uint_fast64_t	pointer_value;
	char			str[ft_abs(pr->precision_field) + pr->width_field + 32];
	char			temp_s[ft_abs(pr->precision_field) + pr->width_field + 32];
	int				re_width;
	int				re_precision;

	str[0] = 0;
	temp_s[0] = 0;
	pointer_value = 0;
	pointer_value = (uint_fast64_t)va_arg(pr->arguments, void *);
	ft_itoa_base(pointer_value, FT_HEX, temp_s);
	re_width = ft_pad(pr->width_field, ft_strlen(temp_s) + 2);
	re_precision = ft_pad(pr->precision_field, ft_strlen(temp_s));
	if (pr->flag.zero == true && pr->flag.minus == false)
	{
		append_to_buffer(pr, "0x");
		append_to_buffer_loop(pr, re_width, "0");
	}
	if (pointer_value == 0 && pr->precision_field != 0)
		ft_strcpy(str, "0");
	else if (pointer_value == 0 && pr->precision_field == 0)
		ft_strcpy(str, NULL);
	else if (pr->precision_field != 0)
		ft_strcpy(str, temp_s);
	p_append_buffer(pr, str, re_width, re_precision);
}
