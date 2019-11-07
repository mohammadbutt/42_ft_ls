/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 15:40:38 by mbutt             #+#    #+#             */
/*   Updated: 2019/09/12 18:13:09 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_libft.h"

/*
** ft_itoa_base will work with any base, but if a base is of 2 and the value is
** either int min, this will produce a binary which will be 32 digits long + 1
** for '\0' making it 33 bits. Allocating memory of 5 bytes would be enough, but
** computationally it will be better if the allocated memory is a power of 2.
** So a buffer/stack of 8 bytes is used to allocate memory.
*/

int		ft_numlen(int_fast64_t value, int base)
{
	int				i;
	uint_fast64_t	u_value;

	i = 0;
	u_value = (uint_fast64_t)value;
	if (value == 0)
		return (0);
	if (value < 0 && base == 10)
		i++;
	while (base == 10 && value)
	{
		value = value / base;
		i++;
	}
	while (base != 10 && u_value)
	{
		u_value = u_value / base;
		i++;
	}
	return (i);
}

char	*ft_itoa_base(int_fast64_t value, int base, char str[])
{
	int				len;
	uint_fast64_t	u_value;
	char			placeholder[17];

	ft_strcpy(placeholder, "0123456789abcdef");
	if (value == 0)
		return (ft_strcpy(str, "0"));
	len = ft_numlen(value, base);
	u_value = (uint_fast64_t)value;
	(value < 0 && base == 10) && (str[0] = '-');
	str[len] = '\0';
	len--;
	while (base == 10 && value)
	{
		str[len] = placeholder[ft_abs(value % base)];
		value = value / base;
		len--;
	}
	while (base != 10 && u_value)
	{
		str[len] = placeholder[u_value % base];
		u_value = u_value / base;
		len--;
	}
	return (str);
}

/*
** ft_itoa_base_u is like ft_itoa_base, except base_u will turn all bases into
** unsigned including base of 10.
*/

int		ft_numlen_u(uint_fast64_t value, int base)
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

char	*ft_itoa_base_u(uint_fast64_t value, int base, char str[])
{
	int				len;
	uint_fast64_t	u_value;
	char			placeholder[17];

	ft_strcpy(placeholder, "0123456789abcdef");
	if (value == 0)
		return (ft_strcpy(str, "0"));
	len = ft_numlen_u(value, base);
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
