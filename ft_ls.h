/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 21:19:42 by mbutt             #+#    #+#             */
/*   Updated: 2019/11/06 18:35:29 by mbutt            ###   ########.fr       */
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
#include <sys/xattr.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

/*
** Notes about headers that are included
**
** <dirent.h>		to access struct dirent
** <sys/stat.h>		to access struct stat
** <sys/xattr.h> 	to access listxattr
** <stdbool.h>		to access bool data type
** <pwd.h>			to access getpwuid
** <grp.h>			to access getgrgid
** <time.h>			to access ctime
*/

/*
** Macros----------------------------------------------------------------------
** FT_PATH_MAX is equal to 1024 because macro __DARWIN_MAXPATHLEN and PATH_MAX
** can hold upto 1024 characters.
** To get 6 months in seconds:
** Divide 365 days / 2 = 182.5 days = 6 months
** multiply 182 by 86,400 because there are 86,400 seconds in one day, which
** is equal to 15,768,000.
**
** Another way to calculate this is to:
** multiply 60 seconds with 60 minutes with 24 hours = 86,400 seconds in a day
** multiply 86,400 with 182.5 days(6 months) is equal to 15,768,000.
*/

# define VALID_FLAG "latrRG" // Added G
# define FT_PATH_MAX 1024
# define SIX_MONTH 15768000

/*
** Structs---------------------------------------------------------------------
*/

typedef struct s_ls_flag
{
	bool l;// : 1;
	bool a;// : 1;
	bool t;// : 1;
	bool r;// : 1;
	bool uppercase_r;// : 1;
	bool uppercase_g;
	bool uppercase_a;
}	t_ls_flag;

/*
** PATH_MAX macros = __DARWIN_MAXPATHLEN, which is equal to 1024
*/


typedef struct s_ls
{
//	struct	stat	meta; // Added
	struct stat stat;
	char 			*file_name;
	char			*invalid_file_name;
	char			*dir_path; // Added
	int				slash_index; // Added
//	int				link_padding;
//	int				size_padding;
	
	struct	s_ls	*next;
}					t_ls;

typedef struct	s_ls_var
{
	int			i;
	int			temp_i;
//	int			j;
	bool		valid_dir;
	bool		new_line;
	bool		double_break;
	int			str_len;
}				t_ls_var;

typedef struct s_info
{
//	struct	dirent	data;
//	struct	stat	*meta;
//	struct	winsize	*ws;
	t_ls_flag		flag;
	t_ls_var		var;
	int				argc;
	char			**argv;
	bool			skip_print;
	bool			print_path_name;
	bool			no_dot_slash;
	int				pad_size;
	int				pad_nlink;
	int				total_blocks;
}					t_info;

/*
** Function Prototypes---------------------------------------------------------
*/

/*
** -------------------------ls_collect_flags.c---------------------------------
*/

bool	is_flag_valid(char c);
void	ls_collect_flags(t_info *info, char c);
void	handle_improper_usage_of_dash(t_ls *ls, t_info *info);
bool	flag_status(t_info *info);


//int		is_flag_valid(char c);
//bool	is_flag_valid(char c);
//void	ls_collect_flag(t_ls *ls, char c);
//void	ls_collect_flags(t_info *info, char c);
//void	ls_start_parsing(t_ls *ls, int argument_count, char **str);
void	ls_start_parsing(t_ls *ls, t_info *info);
//void	process_dir(t_ls *ls, t_info **info, int argument_count, char **str);
//void	process_dir(t_ls *ls, t_info *info, int argument_count, char **str);
void	process_dir(t_ls *ls, t_info *info);
//void	ls_start_parsing(t_info *info, int argument_count, char **str);
//void	ls_start_parsing(t_ls *ls, t_info *info, int arg_count, char **str);
//void	initialize_ls_values(t_ls *ls);
void	initialize_info_values(t_info *info);
void	ft_exit(char c);
void	ft_exit_no_dir(char *str);
void	ft_no_dir(char *str);
void	delete_list(t_ls **head_ref);


// Creating for multiple arguments to handle -R flag
void	multiple_argument(t_ls *ls, t_info *info, char *dir_path_str);
t_ls	*create_list_for_dir(char *dir_path_str);
t_ls	*append_list_for_dir(t_ls *head, char *dir_path_str);

t_ls	*sorted_merge_dir(t_ls *a, t_ls *b);
void	merge_sort_dir(t_ls **head_ref);
t_ls	*store_dir(t_ls *ls, char *dir_path_str);
// Created for multiple arguments to handle -R flag

void	handle_improper_usage_of_dash(t_ls *ls, t_info *info);
t_ls	*create_list_for_invalid(char *invalid_dir_path_str);
t_ls	*append_list_for_invalid(t_ls *head, char *invalid_dir_path_str);
t_ls	*sorted_merge_invalid_file_name(t_ls *a, t_ls *b);
void	merge_sort_invalid_file_name(t_ls **head_ref);
void	print_invalid_file_name(t_ls *ls);
t_ls	*create(char *file_name);
t_ls	*append(t_ls *head, char *file_name);
void	print_file_name(t_ls *ls, t_info *info);
t_ls	*sorted_merge(t_ls *a, t_ls *b);
void	front_back_split(t_ls *source, t_ls **front_ref, t_ls **back_ref);
void	merge_sort(t_ls **head_ref, t_info *info);
int		get_count(t_ls *ls);
bool	flag_status(t_info *info);
void	print_file_name(t_ls *ls, t_info *info); // Will be used after the list is sorted
//void	single_argument(t_ls *ls, t_info *info, char *dir_path);
//void	single_argument(t_ls *ls);
void	single_argument(t_ls *ls, t_info *info, char *dir_path_str);
//void	single_argument(t_ls *ls, DIR *dir);
//t_ls	*single_argument(t_ls *ls);

#endif
