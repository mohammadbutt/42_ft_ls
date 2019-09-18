/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_width_precision_length_type.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 12:31:32 by mbutt             #+#    #+#             */
/*   Updated: 2019/09/15 20:00:59 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Collect_width function collects width_field for each conversion
*/

void	collect_width(t_printf *pr)
{
	if (ft_isdigit(pr->string[pr->i]) == 1)
	{
		pr->width_field = ft_atoi(&pr->string[pr->i]);
		while (ft_isdigit(pr->string[pr->i]) == 1)
			pr->i++;
	}
	else if (pr->string[pr->i] == '*' && ft_isdigit(pr->string[pr->i + 1]) != 1)
	{
		pr->width_field = va_arg(pr->arguments, int);
		pr->i++;
		if (pr->width_field < 0)
		{
			pr->flag.zero = false;
			pr->flag.minus = true;
			pr->width_field = -1 * pr->width_field;
		}
	}
	else if (pr->string[pr->i] == '*' && ft_isdigit(pr->string[pr->i + 1]) == 1)
	{
		pr->width_field = va_arg(pr->arguments, int);
		pr->width_field = ft_atoi(&pr->string[pr->i + 1]);
		pr->i = pr->i + 2;
	}
}

void	collect_precision(t_printf *pr)
{
	int current;
	int next;

	current = pr->i;
	next = pr->i + 1;
	if (pr->string[current] == '.' && ft_isdigit(pr->string[next]) == 1)
	{
		pr->i++;
		pr->precision_field = ft_atoi(&pr->string[pr->i]);
		while (ft_isdigit(pr->string[pr->i]) == 1)
			pr->i++;
	}
	else if (pr->string[current] == '.' && pr->string[next] == '*')
	{
		pr->precision_field = va_arg(pr->arguments, int);
		pr->i = pr->i + 2;
		if (pr->precision_field < 0)
			pr->precision_field = -1;
	}
	else if (pr->string[current] == '.' && ft_isdigit(pr->string[next]) != 1)
	{
		pr->i++;
		pr->precision_field = 0;
	}
}

void	collect_length(t_printf *pr)
{
	char current;
	char next;

	current = pr->string[pr->i];
	next = pr->string[pr->i + 1];
	if ((current == 'h' && next == 'h') || (current == 'l' && next == 'l'))
	{
		if (current == 'h' && next == 'h')
			pr->length.hh = true;
		else if (current == 'l' && next == 'l')
			pr->length.ll = true;
		pr->i = pr->i + 2;
	}
	else if (current == 'h' || current == 'l' || current == 'L')
	{
		if (current == 'h')
			pr->length.h = true;
		else if (current == 'l')
			pr->length.l = true;
		else if (current == 'L')
			pr->length.uppercase_l = true;
		pr->i++;
	}
}

/*
** Function collect_type_field finds the index of the conversion symbols.
** Conversion symbols are: "cspdiouxXfb%" stored in macro FT_VALID_TYPE
** When the conversion symbol is found it's index is stored in type_field
** which can be used for dispatch table later.
**
** If type_field is equal to 0 that would represent 'c'.
** If type_field is equal to 1 that would represent 's'.
** If type_field is equal to 2 that would represetnt 'p'. and so on.
**
** If the conversion symbol is not found then the type_field will remain 0.
** simpler way to understand the below while loop:
**
**	while(FT_VALID_TYPE[j])
**	{
**		if(FT_VALID_TYPE[j] == pr->string[pr->i])
**		{
**			pr->type_field = j;
**			return;
**		}
**		j++;
**	}
*/

void	collect_type_field(t_printf *pr)
{
	char	*str;
	char	c;
	int		j;

	j = 0;
	str = FT_VALID_TYPE;
	c = pr->string[pr->i];
	while (str[j])
	{
		if (str[j] == c)
		{
			pr->type_field = j;
			return ;
		}
		j++;
	}
}
