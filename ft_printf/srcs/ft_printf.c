/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 12:54:07 by mbutt             #+#    #+#             */
/*   Updated: 2019/09/17 14:32:58 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** In field parameter width_field or precision_field will be passed in whichever
** one is being calculated. In string_length field, len of string is passed,
** along with precision field if the precision field has a effect on a type
** field.
**
** Return Value: If the string length is greater than precision or width, then
** 0 is returned which means there would be no padding.
*/

int		ft_pad(int precision_or_width, int string_length)
{
	int padding;

	padding = 0;
	padding = ft_abs(precision_or_width) - ft_abs(string_length);
	if (padding <= 0)
		return (0);
	return (padding);
}

void	pr_struct_to_zero(t_printf *pr)
{
	pr->i = 0;
	pr->buffer_i = 0;
	pr->refresh_buffer_i = 0;
}

void	refresh_buffer(t_printf *pr)
{
	pr->refresh_buffer_i += write(1, pr->buffer, pr->buffer_i);
	pr->buffer_i = 0;
	pr->buffer[pr->buffer_i] = 0;
}

int		ft_printf_driver(va_list args, const char *str)
{
	t_printf pr;

	pr_struct_to_zero(&pr);
	va_copy(pr.arguments, args);
	pr.string = str;
	while (pr.string[pr.i])
	{
		if (pr.string[pr.i] == '%')
		{
			start_parsing(&pr);
			if (pr.string[pr.i] == '\0')
			{
				pr.refresh_buffer_i += write(1, pr.buffer, pr.buffer_i);
				return (pr.refresh_buffer_i);
			}
		}
		else
			pr.buffer[pr.buffer_i++] = pr.string[pr.i];
		if (pr.buffer_i >= FT_32_KILOBYTE)
			refresh_buffer(&pr);
		pr.i++;
	}
	va_end(pr.arguments);
	pr.refresh_buffer_i += write(1, pr.buffer, pr.buffer_i);
	return (pr.refresh_buffer_i);
}

int		ft_printf(const char *str, ...)
{
	va_list	args;
	int		ft_printf_return;

	ft_printf_return = 0;
	va_start(args, str);
	ft_printf_return = ft_printf_driver(args, str);
	va_end(args);
	return (ft_printf_return);
}
