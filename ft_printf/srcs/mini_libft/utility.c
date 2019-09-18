/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 17:48:36 by mbutt             #+#    #+#             */
/*   Updated: 2019/09/12 18:23:05 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_libft.h"

/*
** ft_abs performs the same function as abs(3) function found in stdlib.h
** Converts a value into an absolute value, so a negative values becomes
** positive.
** Return Value: Returns a postive value.
*/

int_fast64_t	ft_abs(int_fast64_t num)
{
	if (num < 0)
		num = -1 * num;
	return (num);
}

int				ft_numlen_uint64(uint_fast64_t nbr)
{
	int i;

	i = 0;
	if (nbr == 0)
		return (0);
	while (nbr)
	{
		nbr = nbr / 10;
		i++;
	}
	return (i);
}

uint_fast64_t	ft_pow10(uint_fast64_t num)
{
	uint_fast64_t i;

	i = 1;
	if (num)
		while (num--)
			i = i * 10;
	return (i);
}

void			ft_swap(char *a, char *b)
{
	char temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

/*
** var_to_zero sets variables to zero
*/

int				var_to_zero(int_fast64_t *a, int *b, int *c, int *d)
{
	*a = 0;
	*b = 0;
	*c = 0;
	*d = 0;
	return (0);
}
