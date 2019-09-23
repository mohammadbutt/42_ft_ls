/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 21:19:42 by mbutt             #+#    #+#             */
/*   Updated: 2019/09/23 16:26:47 by mbutt            ###   ########.fr       */
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
** FT_PATH_MAX is equal to 1024 because macro __DARWIN_MAXPATHLEN and PATH_MAX
** can hold upto 1024 characters.
*/

# define VALID_FLAG "latrR"
# define FT_PATH_MAX 1024


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

/*
** PATH_MAX macros = __DARWIN_MAXPATHLEN, which is equal to 1024
*/

typedef struct s_ls
{
	t_flags flags;
//	struct	dirent	*data;
	struct	stat	*meta;
//	char			file_name[FT_PATH_MAX];
	char 			*file_name;
	struct	s_ls	*next;
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
t_ls	*create(char *file_name);
t_ls	*append(t_ls *head, char *file_name);
void	print_file_name(t_ls *ls);
t_ls	*sorted_merge(t_ls *a, t_ls *b);
void	front_back_split(t_ls *source, t_ls **front_ref, t_ls **back_ref);
void	merge_sort(t_ls **head_ref);
int		get_count(t_ls *ls);
void	print_file_name(t_ls *ls); // Will be used after the list is sorted
void	single_argument(t_ls *ls);
//t_ls	*single_argument(t_ls *ls);

#endif
