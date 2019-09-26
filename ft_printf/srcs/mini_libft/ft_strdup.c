/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 19:16:40 by mbutt             #+#    #+#             */
/*   Updated: 2019/09/25 18:23:41 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_libft.h"
#include <stdio.h>

char	*ft_strdup(char *s1)
{
	char		*string2;
	int			i;

	i = 0;
	string2 = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!string2)
	{
		return (NULL);
	}
	while (s1[i])
	{
		string2[i] = s1[i];
		i++;
	}
	string2[i] = '\0';
	return (string2);
}

/*
**int main(void)
**{
**	char *str1 = "This is a test";
**	char *str2;
**	str2 = ft_strdup(str1);
**	printf("|%s|\n", str2);
**}
*/
