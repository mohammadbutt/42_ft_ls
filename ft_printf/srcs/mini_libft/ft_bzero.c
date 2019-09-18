/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 17:52:38 by mbutt             #+#    #+#             */
/*   Updated: 2019/09/12 17:57:52 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_libft.h"

void	ft_bzero(void *s, size_t len)
{
	unsigned char	*str;
	size_t			i;

	str = s;
	i = 0;
	while (i < len)
		str[i++] = 0;
}

/*
** I have conducted some tests on ft_bzero_no_len and they passed.
** But it could be dangerous to run ft_bzero_no_len without explicitly passing
** in the size/length of the string.
*/

void	ft_bzero_no_len(void *s)
{
	unsigned char	*str;
	size_t			i;

	str = s;
	i = 0;
	if (str)
		while (str[i])
			str[i++] = 0;
}
