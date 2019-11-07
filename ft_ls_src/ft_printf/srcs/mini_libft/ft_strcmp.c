/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 20:50:19 by mbutt             #+#    #+#             */
/*   Updated: 2019/11/07 02:05:21 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_libft.h"
#include <string.h>
#include <stdio.h>

/*
** ft_strcmp takes two strings as parameter and returns the Ascii difference.
** Return Values:
** If the string matches then it will return 0. Otherwise whatever the ascii
** difference will be returned in numerical value.
**
** Below notes are for sorting algorithms:
**
** If the returned number is negative, it means string1 will appear first in
** lexical order.
**
** If the returned number is positive, it means string1 will appear first in
** lexical order.
**
** ft_strcmp(ft_atoi.c, utiltiy.c), will return -15 and will be printed as:
** ft_atoi.c, utility.c
**
** ft_strcmp(utility.c, ft_atoi.c), will return 15 and will be printed as:
** ft_atoi.c, utility.c
*/

int	ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	if (s1 && s2)
		while ((s1[i] == s2[i]) && (s1[i] != '\0'))
			i++;
	return ((unsigned const char)s1[i] - (unsigned const char)s2[i]);
}

/*
**int ft_strcmp(const char *str1, const char *str2)
**{
**	int i;
**
**	i = 0;
**	if(str1 && str2)
**	{
**		if(str1[i] == str2[i] && str1[i + 1] == '\0' && str2[i + 1] == '\0')
**			return(str1[i] - str2[i]);
**		while(str1[i] && str2[i])
**		{
**			if(str1[i] != str2[i])
**				return(str1[i] - str2[i]);
**			else if(str1[i + 1] != str2[i + 1])
**				return(str1[i + 1] - str2[i + 1]);
**			else if(str1[i + 2] != str2[i + 2])
**				return(str1[i + 2] - str2[i + 2]);
**			else if(str1[i + 3] != str2[i + 3])
**				return(str1[i + 3] - str2[i + 3]);
**			else
**				i = i + 4;
**		}
**	}
**	return(str1[i] - str2[i]);
**}
*/
