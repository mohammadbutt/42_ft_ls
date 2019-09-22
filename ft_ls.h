/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 21:19:42 by mbutt             #+#    #+#             */
/*   Updated: 2019/09/21 19:25:26 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_LS_H
# define FT_LS_H

#include "ft_printf/srcs/ft_printf.h"
#include "ft_printf/srcs/mini_libft/mini_libft.h"
#include <dirent.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>

/*
** Notes aboue headers that are included
** 
** <stdbool.h> to have access to bool data type
*/

/*
** Macros----------------------------------------------------------------------
*/

# define VALID_FLAG "latrR"


/*
** Structs---------------------------------------------------------------------
*/

typedef struct s_flags
{
	bool l : 1;
	bool a : 1;
	bool t : 1;
	bool r : 1;
	bool uppercase_r : 1;
}	t_flags;


typedef struct s_ls
{
	t_flags flags;
	struct	dirent	*data;
	struct	stat	*meta;

} t_ls;


/*
** Function Prototypes---------------------------------------------------------
*/

int		is_flag_valid(char c);
void	ls_collect_flag(t_ls *ls, char c);
void	ls_start_parsing(t_ls *ls, int argument_count, char **str);
void	initialize_ls_values(t_ls *ls);
void	ft_exit(char c);
void	ft_exit_no_dir(char *str);
void	single_argument(t_ls *ls);

#endif
