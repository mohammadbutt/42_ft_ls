/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_field_s.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 22:57:44 by mbutt             #+#    #+#             */
/*   Updated: 2019/09/16 19:17:26 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** s_append_buffer looks if the minus flag is true or false.
** If the minus flag is false which means it is 0, then we will look at the zero
** flag.
** 1. If the zero flag is true then we will store '0' as many times as the
** repeat value onto the buffer. Repeat is also called pad/padding.
** 2. If the zero flag is false then then we will store ' ' space as many times
** as the repeat value onto the buffer.
** 3. Finally we will append the str that was previously stored using va_arg.
**
** If the minus flag is true which means it is 1, we will do the following two
** things.
** 1. Append the string from str to buffer.
** 2. Then append ' ', space as any times as the repeat value, or the pad.
**
** Note: If the minus flag is true then the 0 zero flag is ignored.
*/

void	s_append_buffer(t_printf *pr, char *str, int repeat)
{
	if (pr->flag.minus == false)
	{
		if (pr->flag.zero == true)
			append_to_buffer_loop(pr, repeat, "0");
		else if (pr->flag.zero == false)
			append_to_buffer_loop(pr, repeat, " ");
		append_to_buffer(pr, str);
	}
	else if (pr->flag.minus == true)
	{
		append_to_buffer(pr, str);
		append_to_buffer_loop(pr, repeat, " ");
	}
}

/*
** collect_s function does two things:
** 1. Looks at the precision_field value to determine how many characters will
** have to be appended so we store those in str variable.
** 2. Looks at the width_field to calculate the repeat value. This repeat value
** will be used to determine how much padding will be placed in the beginning
** or end of the string.
** NOTE: Since we dont know how long a string will be that is entered by the
** user, 1 megabyte of memory is allocated which is equal to 1,048,576.
**
** s = str
*/

void	collect_s(t_printf *pr)
{
	char	*temp_s;
	char	s[pr->width_field + ft_abs(pr->precision_field) + FT_MEMORY];
	int		repeat;
	int		width;
	int		precision;

	s[0] = 0;
	width = pr->width_field;
	precision = pr->precision_field;
	repeat = 0;
	temp_s = va_arg(pr->arguments, char *);
	if (temp_s == NULL)
		temp_s = "(null)";
	if (pr->precision_field > 0)
		ft_strncpy(s, temp_s, pr->precision_field);
	else if (pr->precision_field == -1)
		ft_strcpy(s, temp_s);
	else if (pr->precision_field == 0)
		(ft_strcpy(s, NULL));
	repeat = ft_pad(pr->width_field, ft_strlen(s));
	s_append_buffer(pr, s, repeat);
}
