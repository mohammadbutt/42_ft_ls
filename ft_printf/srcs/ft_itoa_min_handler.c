/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_min_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 14:48:18 by mbutt             #+#    #+#             */
/*   Updated: 2019/09/12 19:17:23 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_itoa_min_hh(char num, char temp_str[])
{
	if (num == CHAR_MIN)
		ft_strcpy(temp_str, FT_CHAR_STR);
	else
	{
		num = ft_abs(num);
		ft_itoa_base(num, FT_DECIMAL, temp_str);
	}
	return (temp_str);
}

char	*ft_itoa_min_h(short num, char temp_str[])
{
	if (num == SHRT_MIN)
		ft_strcpy(temp_str, FT_SHORT_STR);
	else
	{
		num = ft_abs(num);
		ft_itoa_base(num, FT_DECIMAL, temp_str);
	}
	return (temp_str);
}

char	*ft_itoa_min_l(int_fast64_t num, char temp_str[])
{
	if (num == LONG_MIN)
		ft_strcpy(temp_str, FT_LONG_STR);
	else
	{
		num = ft_abs(num);
		ft_itoa_base(num, FT_DECIMAL, temp_str);
	}
	return (temp_str);
}

char	*ft_itoa_min_ll(int_fast64_t num, char temp_str[])
{
	if (num == LLONG_MIN)
		ft_strcpy(temp_str, FT_LLONG_STR);
	else
	{
		num = ft_abs(num);
		ft_itoa_base(num, FT_DECIMAL, temp_str);
	}
	return (temp_str);
}

char	*ft_itoa_min(t_printf *pr, int_fast64_t num, char temp_str[])
{
	if (pr->length.hh == true)
		ft_itoa_min_hh(num, temp_str);
	else if (pr->length.h == true)
		ft_itoa_min_h(num, temp_str);
	else if (pr->length.l == true)
		ft_itoa_min_l(num, temp_str);
	else if (pr->length.ll == true)
		ft_itoa_min_ll(num, temp_str);
	else
	{
		if (num == INT_MIN)
			ft_strcpy(temp_str, FT_INT_STR);
		else
		{
			num = ft_abs(num);
			ft_itoa_base(num, FT_DECIMAL, temp_str);
		}
	}
	return (temp_str);
}
