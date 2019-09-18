/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_and_cancel_flags.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 12:18:08 by mbutt             #+#    #+#             */
/*   Updated: 2019/09/13 15:30:44 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Function collect_flags gets called in a while loop and it will run as long as
** the return value is not -1.
** Function will return -1 if the character is not '#' '0' '-' '+' ' '.
*/

int		collect_flags(t_printf *pr)
{
	if (pr->string[pr->i] == '#')
		return (pr->flag.hash = true);
	else if (pr->string[pr->i] == '0')
		return (pr->flag.zero = true);
	else if (pr->string[pr->i] == '-')
		return (pr->flag.minus = true);
	else if (pr->string[pr->i] == '+')
		return (pr->flag.plus = true);
	else if (pr->string[pr->i] == ' ')
		return (pr->flag.space = true);
	return (-1);
}

/*
** Function cancel_flags cancels/ignores the below flags:
** 1. Flag ' ' is ignored when flag '+' is present. So when flag_plus is true,
** we set flag_space to false.
**
** 2. Flag '0' is ignored when flag '-' is present. So when flag_minus is true,
** we set flag_zero to false.
*/

void	cancel_flags(t_printf *pr)
{
	if (pr->flag.plus == true)
		pr->flag.space = false;
	if (pr->flag.minus == true)
		pr->flag.zero = false;
}
