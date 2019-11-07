/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_field_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 21:54:38 by mbutt             #+#    #+#             */
/*   Updated: 2019/09/16 20:28:07 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** For flags pr->flag.plus, and pr->flag.hash:
** true = 1
** false = 0
** Placing 1 instead of true due to norminette
*/

void	b_append_buffer(t_printf *pr, char s[], char t_s[])
{
	int len;

	len = ft_strlen(t_s);
	if (s[0] == '0')
		pr->var.precision = ft_pad(pr->precision_field, len + 1);
	else
		pr->var.precision = ft_pad(pr->precision_field, len);
	pr->var.width = ft_pad(pr->width_field, len + pr->var.precision);
	if (pr->flag.plus == 1 || pr->flag.hash == 1)
		if (pr->var.width > 0)
			pr->var.width--;
	if (pr->flag.zero == true && pr->var.width >= 0)
		ft_strcat_loop(s, pr->var.width, "0");
	else if (pr->flag.zero == false && pr->flag.minus == false)
		append_to_buffer_loop(pr, pr->var.width, " ");
	else if (pr->flag.minus == true)
		ft_strcat_loop(t_s, pr->var.width, " ");
	if (pr->var.precision >= 0)
		ft_strcat_loop(s, pr->var.precision, "0");
	ft_strcat(s, t_s);
	append_to_buffer(pr, s);
}

void	check_flags_for_b(t_printf *pr, char s[])
{
	if (pr->flag.hash == true)
		ft_strcpy(s, "0");
}

void	collect_b(t_printf *pr)
{
	uint_fast64_t	n;
	char			s[ft_abs(pr->precision_field) + pr->width_field + 128];
	char			t_s[ft_abs(pr->precision_field) + pr->width_field + 128];

	s[0] = 0;
	t_s[0] = 0;
	ft_bzero(&pr->var, sizeof(&pr->var));
	n = 0;
	n = length_field_uox(pr);
	check_flags_for_o(pr, s);
	ft_itoa_base_u(n, FT_BINARY, t_s);
	if (t_s[0] == '0' && s[0] == '0' && pr->precision_field == -1)
		(pr->flag.zero == false) && (ft_strcpy(s, " "));
	if (s[0] == ' ' && t_s[0] == '0' && pr->flag.minus == true)
		ft_swap(&s[0], &t_s[0]);
	else if (n == 0 && pr->width_field == 0 && pr->precision_field == -1)
		ft_strcpy(s, NULL);
	if (n == 0 && pr->width_field > 1 && pr->flag.zero == true)
		(pr->flag.hash == true) && (ft_strcpy(s, "0"));
	(pr->precision_field != -1) && (pr->flag.zero = false);
	(pr->precision_field == 0 && n == 0) && (ft_strcpy(t_s, NULL));
	o_append_buffer(pr, s, t_s);
}
