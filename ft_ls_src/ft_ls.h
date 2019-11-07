/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 21:19:42 by mbutt             #+#    #+#             */
/*   Updated: 2019/11/07 01:59:45 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "ft_printf/srcs/ft_printf.h"
# include "ft_printf/srcs/mini_libft/mini_libft.h"
# include <dirent.h>
# include <stdio.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>

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

# define VALID_FLAG "latrRG"
# define FT_PATH_MAX 1024
# define SIX_MONTH 15768000

/*
** Structs---------------------------------------------------------------------
*/

typedef struct	s_ls_flag
{
	bool		l : 1;
	bool		a : 1;
	bool		t : 1;
	bool		r : 1;
	bool		uppercase_r : 1;
	bool		uppercase_g : 1;
	bool		uppercase_a : 1;
}				t_ls_flag;

/*
** PATH_MAX macros = __DARWIN_MAXPATHLEN, which is equal to 1024
*/

typedef struct	s_ls
{
	struct stat	stat;
	char		*file_name;
	char		*invalid_file_name;
	char		*dir_path;
	int			slash_index;
	struct s_ls	*next;
}				t_ls;

typedef struct	s_ls_var
{
	int			i;
	int			temp_i;
	bool		valid_dir;
	bool		new_line;
	bool		double_break;
	int			str_len;
}				t_ls_var;

typedef struct	s_info
{
	t_ls_flag	flag;
	t_ls_var	var;
	int			argc;
	char		**argv;
	bool		skip_print;
	bool		print_path_name;
	bool		no_dot_slash;
	int			pad_size;
	int			pad_nlink;
	int			total_blocks;
}				t_info;

/*
** Function Prototypes----------------------------------------------------------
*/

/*
** ls_collect_flags.c-----------------------------------------------------------
*/

bool			is_flag_valid(char c);
void			ls_collect_flags(t_info *info, char c);
void			handle_improper_usage_of_dash(t_ls *ls, t_info *info);
bool			flag_status(t_info *info);
int				set_up_environment_to_collect_flags(t_info *info, int i, int j);

/*
** merge_sort_alpha.c-----------------------------------------------------------
*/

t_ls			*sorted_merge_alpha(t_ls *a, t_ls *b);
t_ls			*sorted_merge_alpha_reverse(t_ls *a, t_ls *b);
void			front_back_split(t_ls *source, t_ls **font, t_ls **back);
void			merge_sort(t_ls **head_ref, t_info *info);

/*
** merge_sort_time.c------------------------------------------------------------
*/

t_ls			*sorted_merge_time_nano_second(t_ls *a, t_ls *b);
t_ls			*sorted_merge_time(t_ls *a, t_ls *b);
t_ls			*sorted_merge_time_reverse(t_ls *a, t_ls *b);
t_ls			*sorted_merge_time_nano_second_reverse(t_ls *a, t_ls *b);

/*
** merge_sort_invalid_file.c----------------------------------------------------
*/

t_ls			*sorted_merge_invalid_file_name(t_ls *a, t_ls *b);
void			merge_sort_invalid_file_name(t_ls **head_ref);

/*
** store_file_name.c------------------------------------------------------------
*/

t_ls			*store_file_name(t_ls *ls, char *file_name);
t_ls			*create(char *valid_file_path);
t_ls			*append(t_ls *head, char *valid_file_path);

/*
** store_file_name_with_index.c-------------------------------------------------
*/

t_ls			*store_file_name_with_index(t_ls *ls, char *file, int i);
t_ls			*create_with_index(char *valid_file_path, int index);
t_ls			*append_with_index(t_ls *head, char *file_path, int index);

/*
** delete_linked_list.c---------------------------------------------------------
*/

void			delete_list_file_name(t_ls **head_ref);

/*
** process_dir_valid.c----------------------------------------------------------
*/

t_ls			*store_dir_path(t_ls *temp_ls, t_info *info);
void			files_from_stored_dir_path(t_ls *ls, t_ls *ls2, t_info *info);
void			process_dir_valid(t_ls *ls, t_info *info);
void			process_dir(t_ls *ls, t_info *info);

/*
** process_valid_and_invalid_file.c---------------------------------------------
*/

void			process_invalid_file(t_ls *ls, t_info *info);
void			process_valid_file(t_ls *ls, t_info *info);

/*
** ls_recursive_call.c----------------------------------------------------------
*/

void			print_dir_path_for_recursion(t_info *info, char *path);
t_ls			*sotre_inner_recursive_files(t_ls *tmp_ls, t_info *inf, DIR *d);
t_ls			*store_file_recursively(t_info *info, char *path);
void			handle_inner_dir(t_ls *inner_dir, t_info *info, char *ref_str);
int				start_recursive_call(t_ls *temp_ls, t_info *info);

/*
** usage_and_permission_denied.c------------------------------------------------
*/

void			ft_exit_illegal_option(char c);
void			ls_collect_flag_and_illegal_option(t_info *info, int i, int j);
void			ft_permission_denied(char *str);

/*
** padding_and_blocks_totals.c--------------------------------------------------
*/

int				get_link_padding(t_ls *ls);
int				get_size_padding(t_ls *ls);
int				find_max(int num1, int num2);
void			padding_and_blocks_total(t_ls *ls, int *pad_link, int *pad_sze);

/*
** long_file_listing.c----------------------------------------------------------
*/

char			permission_file_type(int file_mode);
char			extended_attributes(char *file_name);
void			permission_column(struct stat meta, char *file_name);
void			month_date_time_column(struct stat meta);
void			long_file_listing(struct stat meta, char *file, t_info *info);

/*
** ls_parsing.c-----------------------------------------------------------------
*/

void			two_arguments(t_ls *ls, t_ls *ls2, t_info *info, char *path);
void			more_than_two_arguments(t_ls *ls, t_info *info, int i);
void			ls_start_parsing(t_ls *ls, t_info *info);
void			merge_delete_append_slash(t_ls *ls, t_info *info, char *path);
void			single_argument(t_ls *ls, t_info *info, char *dir_path_str);

/*
** append_slash.c---------------------------------------------------------------
*/

int				find_last_slash(char *file_path_woth_slash);
t_ls			*append_slash(t_ls *new_ls, t_ls *temp_ls, char *path);
t_ls			*get_new_ls(t_ls *new_ls, t_ls *ls, char *path, int slash_i);

/*
** print_file_name.c------------------------------------------------------------
*/

void			print_invalid_file_name(t_ls *ls);
void			format_and_print(t_ls *ls, t_info *info, char *s, char *link_s);
void			print_file_name(t_ls *ls, t_info *info);
void			print_uppercase_g(char *str, struct stat meta);

/*
** formatting.c-----------------------------------------------------------------
*/

char			*ft_substring(char *dest, char *source, int start);
char			*ft_substr_start_end(char *dest, char *source, int start,
				int end);
void			get_total_for_long_listing(t_ls *ls);
void			file_is_link(char *link_str, char *ls_file_name, char *str);
int				get_count(t_ls *ls);

/*
**	main.c----------------------------------------------------------------------
*/

void			initialize_t_info_struct_variables(t_info *info);
t_ls			*store_root_files(t_ls *ls, t_info *info, char *path_str);
int				main(int argc, char *argv[]);

#endif
