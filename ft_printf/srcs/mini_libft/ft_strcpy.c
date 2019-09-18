/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 20:57:42 by mbutt             #+#    #+#             */
/*   Updated: 2019/09/12 18:17:18 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_libft.h"

char	*ft_strcpy(char *dest, char *source)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (source)
		while (source[i])
			dest[j++] = source[i++];
	dest[j] = '\0';
	return (dest);
}

char	*ft_strncpy(char *dest, char *source, int len)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (source && len)
		while (len-- && source[i])
			dest[j++] = source[i++];
	dest[i] = '\0';
	return (dest);
}
