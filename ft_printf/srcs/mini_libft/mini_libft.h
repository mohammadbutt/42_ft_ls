/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_libft.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 15:50:24 by mbutt             #+#    #+#             */
/*   Updated: 2019/09/12 18:47:17 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_LIBFT_H
# define MINI_LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <stdint.h>

/*
** ---------------------mini_libft function prototypes--------------------------
*/

/*
** ---------------------------------Macros--------------------------------------
** Below t_unit128_t doesn't work, but leaving it for reference
*/

typedef	__uint128_t	t_uint128_t;

/*
** ------------------------------Struct for ftoa--------------------------------
*/

typedef struct		s_floats
{
	char			new_string[64];
	long double		temp_nbr;
	long double		difference;
	uint_fast64_t	whole_nbr;
	uint_fast64_t	fraction_nbr;
	int				pad_zeros;
	int				fraction_nbr_len;
	int				whole_nbr_len;
	bool			negative_sign;
}					t_float;

/*
** ----------------------------------ft_ftoa.c----------------------------------
** p = precision
*/

void				get_whole_fraction_diff(t_float *f, long double n, int p);
void				ft_ftoa_roundup(t_float *f, long double nbr, int p);
void				extract_precision_nbr(t_float *f, char str[], int p);
void				extract_whole_nbr(t_float *f, char str[], int p);
char				*ft_ftoa(long double nbr, char str[], int p);

/*
** ----------------------------------ft_atoi.c----------------------------------
*/

int					ft_atoi(const char *str);
int					ft_isspace(int c);

/*
** --------------------------------ft_bzero.c-----------------------------------
*/

void				ft_bzero(void *str, size_t len);
void				ft_bzero_no_len(void *str);

/*
** ---------------------------------ft_hex.c------------------------------------
*/

char				*ft_hex(uint_fast64_t value, char c, char str[]);
int					ft_hex_numlen(uint_fast64_t value, int base);

/*
** -------------------------------ft_strcpy.c-----------------------------------
*/

char				*ft_strcpy(char *dest, char *source);
char				*ft_strncpy(char *dest, char *source, int len);

/*
** -------------------------------ft_strcat.c-----------------------------------
*/

char				*ft_strcat(char *dest, char *source);
char				*ft_strcat_loop(char *dest, int x_times, char *source);

/*
** ------------------------------ft_isdigit.c-----------------------------------
*/

int					ft_isdigit(char c);
int					ft_isdigit1(char c);

/*
** ------------------------------ft_strlen.c------------------------------------
*/

int					ft_strlen(char *str);
int_fast32_t		ft_strlen_fast(char *str);

/*
** -----------------------------ft_itoa_base.c----------------------------------
*/

int					ft_numlen(int_fast64_t value, int base);
char				*ft_itoa_base(int_fast64_t value, int base, char str[]);
int					ft_numlen_u(uint_fast64_t value, int base);
char				*ft_itoa_base_u(uint_fast64_t value, int base, char str[]);

/*
** --------------------------------utility.c------------------------------------
*/

int_fast64_t		ft_abs(int_fast64_t num);
int					ft_numlen_uint64(uint_fast64_t nbr);
uint_fast64_t		ft_pow10(uint_fast64_t num);
void				ft_swap(char *a, char *b);
int					var_to_zero(int_fast64_t *a, int *b, int *c, int *d);

#endif
