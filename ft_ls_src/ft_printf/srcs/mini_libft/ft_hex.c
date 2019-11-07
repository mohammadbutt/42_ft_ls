/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 18:27:57 by mbutt             #+#    #+#             */
/*   Updated: 2019/09/12 18:07:48 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_libft.h"
#include <stdio.h>

/*
** ft_hex takes in a number and a upper or lower case x to turns in into
** hexadecimal.
*/

int		ft_hex_numlen(uint_fast64_t value, int base)
{
	int				i;
	uint_fast64_t	u_value;

	i = 0;
	u_value = (uint_fast64_t)value;
	if (value == 0)
		return (0);
	if (u_value)
		while (base && u_value)
		{
			u_value = u_value / base;
			i++;
		}
	return (i);
}

char	*ft_hex(uint_fast64_t value, char c, char str[])
{
	int				base;
	int				len;
	uint_fast64_t	u_value;
	char			placeholder[17];

	if (value == 0)
		return (ft_strcpy(str, "0"));
	if (c == 'x')
		ft_strcpy(placeholder, "0123456789abcdef");
	else if (c == 'X')
		ft_strcpy(placeholder, "0123456789ABCDEF");
	base = 16;
	len = ft_hex_numlen(value, base);
	u_value = (uint_fast64_t)value;
	str[len] = '\0';
	len--;
	while (base && u_value)
	{
		str[len] = placeholder[u_value % base];
		u_value = u_value / base;
		len--;
	}
	return (str);
}
