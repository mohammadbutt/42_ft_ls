/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 16:22:56 by mbutt             #+#    #+#             */
/*   Updated: 2019/09/12 18:16:19 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_libft.h"

char	*ft_strcat(char *dest, char *source)
{
	int i;
	int j;

	i = 0;
	j = ft_strlen(dest);
	if (source[i])
		while (source[i])
			dest[j++] = source[i++];
	dest[j] = '\0';
	return (dest);
}

char	*ft_strcat_loop(char *dest, int x_times, char *source)
{
	int i;
	int j;

	i = 0;
	j = ft_strlen(dest);
	if (x_times)
		while (x_times--)
		{
			if (source)
				while (source[i])
					dest[j++] = source[i++];
			i = 0;
		}
	dest[j] = '\0';
	return (dest);
}
