/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 15:21:17 by mbutt             #+#    #+#             */
/*   Updated: 2019/11/07 02:01:53 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "./mini_libft/mini_libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdbool.h>
# include <limits.h>

/*
** <unistd.h>	write(2)
** <stdlib.h>	malloc(3), free(3), exit(3), uint64_t,and uint_fast64_t
** <stdarg.h>	va_start, va_arg, va_copy, va_end(3)
** <stdbool.h> 	bool data type
** <limits.h>	For MIN MAX macros such as: CHAR_MIN, SHRT_MIN, LONG_MIN
*/

/*
** One megabyte = 1024 * 1024 bytes
** 1024 bytes    1024 kb
** __________ x _________
**    1 kb        1 mb
**
** 1024 x 1024 bytes / 1 mb
**
** 1048576 bytes = 1 mb
**
** macros FT_CHAR_STR, FT_SHORT_STR, FT_INT_STR, FT_LONG_STR, FT_LONG_LONG_STR
** their values go over the max range, that's because the negative sign from
** these values will get appended to the buffer first and the values without
** the negative sign will get stored in temp_str.
*/

# define FT_ONE_MEGABYTE 1048576
# define FT_ONE_KILOBYTE 1024
# define FT_TWO_KILOBYTE 2048
# define FT_FOUR_KILOBYTE 4096
# define FT_32_KILOBYTE 32768
# define FT_MEMORY FT_FOUR_KILOBYTE
# define FT_VALID_TYPE "cspdiouxXfb%"
# define FT_HEX 16
# define FT_DECIMAL 10
# define FT_OCTAL 8
# define FT_BINARY 2
# define FT_CHAR_STR "128"
# define FT_SHORT_STR "32768"
# define FT_INT_STR "2147483648"
# define FT_LONG_STR "9223372036854775808"
# define FT_LLONG_STR "9223372036854775808"

/*
** -----------------------------Font Color Scheme-------------------------------
** -----------------------------------------------------------------------------
*/

/*
** Regular font Color
*/

# define NC "\33[0m"
# define BLACK "\33[0;30m"
# define RED "\33[0;31m"
# define GREEN "\33[0;32m"
# define YELLOW "\33[0;33m"
# define BLUE "\33[0;34m"
# define PURPLE "\33[0;35m"
# define CYAN "\33[0;36m"
# define WHITE "\33[0;37m"

/*
** Bold font Color
*/

# define BBLACK "\33[1;30m"
# define BRED "\33[1;31m"
# define BGREEN "\33[1;32m"
# define BYELLOW "\33[1;33m"
# define BBLUE "\33[1;34m"
# define BPURPLE "\33[1;35m"
# define BCYAN "\33[1;36m"
# define BWHITE "\33[1;37m"

/*
** Background Colors
*/

# define ON_BLACK "\033[40m"
# define ON_RED "\033[41m"
# define ON_GREEN "\033[42m"
# define ON_YELLOW "\033[43m"
# define ON_BLUE "\033[44m"
# define ON_PURPLE "\033[45m"
# define ON_CYAN "\033[46m"
# define ON_WHITE "\033[47m"

/*
** Colon ':' in structs is called a bit field
** 1 bool data type uses 1 bytes. 1 byte = 8 bits. This means a bool will ask
** for 1 byte of memory which will have 8 bits as shown below:
**  _ _ _ _ _ _ _ _
** |_|_|_|_|_|_|_|_|
**
** Unless se specify this entire 1 byte will be reserved and used for a single
** variable.
** We can ask for one single bit from a byte and it will look as following:
**  _
** |_|
**
** When we specify by using colon : a bool variable will only
** use the specified number of bits of the byte, which means we can have 7 more
** bits that can be used.
*/

typedef struct	s_variables
{
	int			width;
	int			precision;
}				t_variables;

typedef struct	s_flag
{
	bool		hash : 1;
	bool		zero : 1;
	bool		minus : 1;
	bool		plus : 1;
	bool		space : 1;
}				t_flag;

typedef struct	s_length
{
	bool		hh : 1;
	bool		h : 1;
	bool		l : 1;
	bool		ll : 1;
	bool		uppercase_l : 1;
}				t_length;

typedef struct	s_printf
{
	t_variables var;
	t_flag		flag;
	t_length	length;
	char		buffer[FT_MEMORY];
	va_list		arguments;
	const char	*string;
	int			i;
	int			buffer_i;
	int			width_field;
	int			precision_field;
	int			length_field;
	int			type_field;
	int			refresh_buffer_i;
}				t_printf;

/*
** append_to_buffer.c
*/

void			append_to_buffer(t_printf *pr, char *source);
void			append_to_buffer_loop(t_printf *pr, int x_times, char *str);

/*
** type_field_b.c
*/

void			b_append_buffer(t_printf *pr, char s[], char t_s[]);
void			check_flags_for_b(t_printf *pr, char s[]);
void			collect_b(t_printf *pr);

/*
** type_field_f.c
*/

void			collect_f(t_printf *pr);
void			f_append_buffer(t_printf *pr, char s[], char t_s[]);

/*
** type_field_d_i.c
*/

int_fast64_t	length_field_d(t_printf *pr);
void			collect_d(t_printf *pr);
void			d_append_buffer(t_printf *pr, char s[], char t_s[]);

/*
** type_field_p.c
** In p_append_buffer, last parameter, int p, p stands for precision
*/

void			collect_p(t_printf *pr);
void			p_append_buffer(t_printf *pr, char *str, int width, int p);

/*
** type_field_s.c
*/

void			collect_s(t_printf *pr);
void			s_append_buffer(t_printf *pr, char *str, int repeat);

/*
** type_field_c.c
*/

void			collect_c(t_printf *pr);

/*
** type_field_percent.c
*/

void			collect_percent(t_printf *pr);

/*
** type_field_u.c
*/

void			collect_u(t_printf *pr);
uint_fast64_t	length_field_uox(t_printf *pr);
void			u_append_buffer(t_printf *pr, char s[], char t_s[]);

/*
** type_field_o.c
*/

void			collect_o(t_printf *pr);
void			check_flags_for_o(t_printf *pr, char s[]);
void			o_append_buffer(t_printf *pr, char s[], char t_s[]);

/*
** type_field_x.c
*/
void			collect_x(t_printf *pr);
void			x_width_n_precision_n(t_printf *pr, uint_fast64_t n);
void			x_width_n_precision_y(t_printf *pr, uint_fast64_t n);
void			check_flags_for_x(t_printf *pr, char s[], uint_fast64_t n);

/*
** type_field_x_remaining_conditions.c
** s = str
*/
void			x_width_y_precision_n(t_printf *pr, uint_fast64_t n);
void			x_width_y_precision_y(t_printf *pr, uint_fast64_t n);
void			x_width_y_precision_n2(t_printf *pr, char s[], char str_hex[]);
void			x_width_y_precision_y2(t_printf *pr, char s[], char str_hex[]);

/*
** parsing.c
*/

void			initialize_flag_and_field_values(t_printf *pr);
void			start_collecting_flags(t_printf *pr);
void			collect_data(t_printf *pr);
void			start_parsing(t_printf *pr);

/*
** collect_and_cancel_flags.c
*/

int				collect_flags(t_printf *pr);
void			cancel_flags(t_printf *pr);

/*
** collect_width_precision_length_type.c
*/

void			collect_width(t_printf *pr);
void			collect_precision(t_printf *pr);
void			collect_length(t_printf *pr);
void			collect_type_field(t_printf *pr);

/*
** ft_itoa_min_handler.c
*/

char			*ft_itoa_min(t_printf *pr, int_fast64_t num, char temp_str[]);
char			*ft_itoa_min_hh(char num, char temp_str[]);
char			*ft_itoa_min_h(short num, char temp_str[]);
char			*ft_itoa_min_l(int_fast64_t num, char temp_str[]);
char			*ft_itoa_min_ll(int_fast64_t num, char temp_str[]);

/*
** ft_printf.c
*/

int				ft_pad(int precision_or_width, int string_length);
void			pr_struct_to_zero(t_printf *pr);
void			refresh_buffer(t_printf *pr);
int				ft_printf_driver(va_list args, const char *str);
int				ft_printf(const char *str, ...);

typedef void	t_ft_print_functions(t_printf *pr);

static	t_ft_print_functions *g_ft_dispatch_table[] =
{
	collect_c,
	collect_s,
	collect_p,
	collect_d,
	collect_d,
	collect_o,
	collect_u,
	collect_x,
	collect_x,
	collect_f,
	collect_b,
	collect_percent
};

#endif
