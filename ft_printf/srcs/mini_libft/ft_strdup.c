/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 19:16:40 by mbutt             #+#    #+#             */
/*   Updated: 2019/09/22 20:07:48 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_libft.h"
#include <stdio.h>

char *ft_strdup(const char *s1)
{
	int i;
	char *s2;

	i = 0;
	s2 = malloc(sizeof(char) * (ft_strlen((char *)s1)) + 1);
	if(s2 == NULL)
		return(NULL);
	ft_strcpy(s2, (char *)s1);
	return(s2);
}

/*
int main(void)
{
	char *str1 = "This is a test";
	char *str2;

	str2 = ft_strdup(str1);

	printf("|%s|\n", str2);
}
*/
