/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 13:24:55 by mbutt             #+#    #+#             */
/*   Updated: 2019/09/27 16:03:26 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <string.h>
/*
// Simple ft_ls
int main(int argc, char **argv)
{
	struct dirent *pDirent;
	DIR *pDir;

	if(argc == 1)
	{
		argv[1][0] = '.';
		pDir = opendir(argv[1]);
	}
//	if(argc < 2)
//	{
//		ft_printf("Useage: testprog <dirname>\n");
//		return(1);
//	}
	else
		pDir = opendir(argv[1]);
	if(pDir == NULL)
	{
		ft_printf("Cannot open directory '%s'\n", argv[1]);
		return(1);
	}
	while((pDirent = readdir(pDir)) != NULL)
	{
		ft_printf("[%s]\n", pDirent->d_name);
//		ft_printf("%-15s", pDirent->d_name);
		}

	closedir(pDir);
	return(0);
}
*/



/*
** is_flag_valid takes a character and compares it with VALID_FLAG string,
** "latrR", if the character appears then it's valid and returns 1, if the
** character does nor appear in VALID_FLAG, "latrR", then the character is
** invalid and will return 0.
** Return Values: true for valid. false for invalid
*/

bool is_flag_valid(char c)
{
	int i;

	i = 0;
	while(VALID_FLAG[i])
	{
		if(VALID_FLAG[i] == c)
			return(true);
		i++;
	}
	return(false);
}

/*
void ls_collect_flags(t_ls *ls, char c)
{
	if(c == 'l')
		ls->flags.l = true;
	else if(c == 'a')
		ls->flags.a = true;
	else if(c == 't')
		ls->flags.t = true;
	else if(c == 'r')
		ls->flags.r = true;
	else if(c == 'R')
		ls->flags.uppercase_r = true;
}
*/
void ls_collect_flags(t_info *info, char c)
{
	if(c == 'l')
		info->flag.l = true;
	else if(c == 'a')
		info->flag.a = true;
	else if(c == 't')
		info->flag.t = true;
	else if(c == 'r')
		info->flag.r = true;
	else if(c == 'R')
		info->flag.uppercase_r = true;
}


void ft_exit(char c)
{
	ft_printf("ft_ls: illegal option -- %c\n", c);
	ft_printf("usage: ft_ls [-latrR] [file ...]\n");
	exit(EXIT_SUCCESS);
}

/*
** perror will handle following errors:
** 1. No such file or directory - Currently only works with directory. Need to
** make it work with files.
** 2. Permission denied.
** If a folder has permission denied via chmod 000 folder_name or file_name,
** then ls will not show contents of that folder. perror will print a message
** saying ... permission denied.
*/

void ft_exit_no_dir(char *str)
{
	ft_printf("ft_ls: ");
	perror(str);
	exit(EXIT_SUCCESS);
}

void	ft_no_dir(char *dir_path_str)
{
	ft_printf("ft_ls: ");
	perror(dir_path_str);
}

/*
void ls_start_parsing(t_info *info, int argument_count, char **str)
{
	int i;
	int j;
	DIR *directory;
//	struct dirent *dir_struct;
//	char str2[1024];
	struct stat fileinfo;
//	char str2[1024];

	i = 1;
	j = 0;
	
	while(i < argument_count)
	{
		if(str[i][j] != '-')
		{

			directory = opendir(str[i]);
//			ft_printf("CP1\n");
//			dir_struct = malloc(sizeof(directory));
//			ft_printf("CP2\n");
//			if(dir_struct == NULL)
//				ft_exit_no_dir(str[i]);


			directory = opendir(str[i]);
			stat(str[i], &fileinfo);
			ft_printf("%s\n", str[i]);
			return;

//			if(directory == NULL)
//				ft_exit_no_dir(str[i]);
//			else
//				dir_struct = readdir(directory);
		}
		j++;
		while(str[i][j])
		{
			if (is_flag_valid(str[i][j]) == 0)
			{
				ft_exit(str[i][j]);
//				ft_printf("Useage: Invalid flag2\n");
//				return;
			}
			else if(is_flag_valid(str[i][j]) == 1)
			{
//				ft_printf("Does it come here\n");
//				ft_printf("Valid:|%c|\n",str[i][j]);
				ls_collect_flags(info, str[i][j]);
//				ls_collect_flags(ls, str[i][j]);
//				printf("flag.l|%d|\n", ls->flags.l);
			}
			j++;
		}
		j = 0;
		i++;
	}
}
*/


t_ls	*sorted_merge_invalid_file_name(t_ls *a, t_ls *b)
{
	t_ls *result;

	result = NULL;
	if(a == NULL)
		return(b);
	else if(b == NULL)
		return(a);
	if(ft_strcmp(a->invalid_file_name, b->invalid_file_name) <= 0)
	{
		result = a;
		result->next = sorted_merge_invalid_file_name(a->next, b);
	}
	else
	{
		result = b;
		result->next = sorted_merge_invalid_file_name(a, b->next);
	}
	return(result);
}

void	merge_sort_invalid_file_name(t_ls **head_ref)
{
	t_ls *head;
	t_ls *a;
	t_ls *b;

	head = *head_ref;
	if(head == NULL || head->next == NULL)
		return;
	front_back_split(head, &a, &b);
	merge_sort_invalid_file_name(&a);
	merge_sort_invalid_file_name(&b);
	*head_ref = sorted_merge_invalid_file_name(a, b);
}



t_ls	*store_invalid_file_name(t_ls *ls,  t_info *info, char *dir_path_str)
{

	if(ls == NULL)
		ls = create_list_for_invalid(dir_path_str);
	else
		ls = append_list_for_invalid(ls, dir_path_str);
	return(ls);
}


void print_invalid_file_name(t_ls *ls)
{
	int i;
	char *invalid_str;
	
	i = 0;
	while(ls)
	{
		invalid_str = ls->invalid_file_name;
		ft_printf("ft_ls: ");
		perror(invalid_str);
		ls = ls->next;
	}
}

void process_dir_invalid(t_ls *ls, t_info *info)
{
	struct dirent	*data;
	DIR				*dir;
	char			**arg_str;
	int				arg_count;
	int 			i;

	arg_str = info->argv;
	arg_count = info->argc;
	i = info->var.i;
	while(i < arg_count)
	{
		dir = opendir(arg_str[i]);
		if(dir == NULL)
			ls = store_invalid_file_name(ls, info, arg_str[i]);
		(dir != NULL) && (closedir(dir));
		i++;
	}
	if(ls != NULL)
	{
		merge_sort_invalid_file_name(&ls);
		print_invalid_file_name(ls);
		delete_list(&ls);
	}
}

void process_dir_valid(t_ls *ls, t_info *info)
{
	struct dirent	*data;
	DIR				*dir;
	char			**arg_str;
	int				arg_count;
	int				i;

	arg_str	= info->argv;
	arg_count = info->argc;
	i = info->var.i;
	info->var.valid_dir = false;
	while(i < arg_count)
	{
		dir = opendir(arg_str[i]);
		if(dir != NULL)
		{
			(info->var.valid_dir == true) && (ft_printf("\n"));
			(arg_count > 2) && (ft_printf("%s:\n", arg_str[i]));
			single_argument(ls, arg_str[i]);
			info->var.valid_dir = true;
		}
		(dir != NULL) && (closedir(dir));
		i++;
	}
}

void	process_dir(t_ls *ls, t_info *info)
{
//	info->var.i = 1;
	info->var.i = info->var.temp_i;
	process_dir_invalid(ls, info);
//	info->var.i = 1;
	info->var.i = info->var.temp_i;
	process_dir_valid(ls, info);
	exit(EXIT_SUCCESS);
}

void	ls_start_parsing(t_ls *ls, t_info *info)
{
	struct dirent	*data;
	DIR				*dir;
	int				count;
	int				i;
	int				j;
	int				strlen;
	bool			double_break;

	i = 1;
	j = 1;
	strlen = 0;
	info->var.temp_i = 1;
	double_break = false;
	if(info->argv[i][0] != '-')
	{
		process_dir(ls, info);
	}
	else if(info->argv[i][0] == '-' && info->argv[i][1] == '\0')
	{
		process_dir(ls, info);
	}
// Above works fine.
	else if(info->argv[i][0] == '-' && info->argv[i][1] != '\0')
	{
		while(i < info->argc)
		{
			strlen = ft_strlen(info->argv[i]);
			while(j < strlen)
			{
				if(info->argv[i][0] == '-')
				{
					if(is_flag_valid(info->argv[i][j]) == true)
						ls_collect_flags(info, info->argv[i][j]);
					else if(is_flag_valid(info->argv[i][j]) == false)
						ft_exit(info->argv[i][j]);
				}
				else if(info->argv[i][0] != '-')
				{
					double_break = true;
					break;
				}
				j++;
			}
			if(double_break == true)
				break;
			j = 1;
			i++;
		}
		while(i < info->argc)
		{
			info->var.temp_i = i;
			process_dir(ls, info);
			i++;
		}
	}

/*
	while(i < argument_count)
	{
		if(str[i][j] != '-') // from now on has to be a folder
		{
			dir = opendir(str[i]);
			if(dir == NULL)
				ft_exit_no_dir(str[i]);
		}
		i++;
	}
*/

}

void	initialize_info_values(t_info *info)
{
	ft_bzero(&info->flag, sizeof(info->flag));
}

/*
** Linked List functions just to store file and folder names when argc is 1
** ./ft_ls
*/

void	delete_list(t_ls **head_ref)
{
	t_ls *current;
	t_ls *next;

	current = *head_ref;
	while(current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*head_ref = NULL;
}

t_ls	*create_list_for_invalid(char *invalid_dir_path_str)
{
	t_ls *new_node;

	new_node = malloc(sizeof(t_ls));
	if(new_node == NULL)
		exit(EXIT_SUCCESS);

	new_node->invalid_file_name = ft_strdup(invalid_dir_path_str);
	new_node->next = NULL;
	return(new_node);
}

t_ls *append_list_for_invalid(t_ls *head, char *invalid_dir_path_str)
{
	t_ls *cursor;
	t_ls *new_node;

	cursor = head;
	while(cursor->next != NULL)
		cursor = cursor->next;
	new_node = create_list_for_invalid(invalid_dir_path_str);
	cursor->next = new_node;
	return(head);
}

t_ls	*create(char *valid_file_path_str)
{
	t_ls *new_node;

	new_node = malloc(sizeof(t_ls));
	if(new_node == NULL)
		exit(EXIT_SUCCESS);

	new_node->file_name = ft_strdup(valid_file_path_str);
	new_node->next = NULL;
	return(new_node);
}

t_ls *append(t_ls *head, char *valid_file_path_str)
{
	t_ls *cursor;
	t_ls *new_node;

	cursor = head;
	while(cursor->next != NULL)
		cursor = cursor->next;
	new_node = create(valid_file_path_str);
	cursor->next = new_node;
	return(head);
}

/*
void print_file_name(t_ls *ls)
{
	int i;
	char *str;
	

	i = 0;
	while(ls)
	{
		str = ls->file_name;
		ft_printf("%s\n", str);
		ls = ls->next;
	}
}
*/


void print_file_name(t_ls *ls)
{
	struct stat meta;
	char *str;
	int i;
	
	i = 0;
	while(ls)
	{
		str = ls->file_name;
		stat(str, &meta);
		if(S_ISREG(meta.st_mode))
			ft_printf("%s\n", str);
		else if(S_ISDIR(meta.st_mode))
			ft_printf(BRED"%s\n"NC, str);
		else if(S_ISCHR(meta.st_mode))
			ft_printf(BGREEN"%s\n"NC, str);
		else
			ft_printf(BWHITE"%s\n"NC, str);
		ls = ls->next;
	}
}


/*
** Merge Sort
*/

t_ls	*sorted_merge(t_ls *a, t_ls *b)
{
	t_ls *result;

	result = NULL;
	if(a == NULL)
		return(b);
	else if(b == NULL)
		return(a);
	if(ft_strcmp(a->file_name, b->file_name) <= 0)
	{
		result = a;
		result->next = sorted_merge(a->next, b);
	}
	else
	{
		result = b;
		result->next = sorted_merge(a, b->next);
	}
	return(result);
}

void front_back_split(t_ls *source, t_ls **front_ref, t_ls **back_ref)
{
	t_ls *fast;
	t_ls *slow;
	slow = source;
	fast = source->next;

	while(fast != NULL)
	{
		fast = fast->next;
		if(fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*front_ref = source;
	*back_ref = slow->next;
	slow->next = NULL;
}

void	merge_sort(t_ls **head_ref)
{
	t_ls *head;
	t_ls *a;
	t_ls *b;

	head = *head_ref;
	if(head == NULL || head->next == NULL)
		return;
	front_back_split(head, &a, &b);
	merge_sort(&a);
	merge_sort(&b);
	*head_ref = sorted_merge(a, b);
}

/*
** Get count function calculates how many nodes/ files and folder there are in a
** given directory.
*/

int get_count(t_ls *ls)
{
	int count;

	count = 0;
	if(ls)
		while(ls)
		{
			ls = ls->next;
			count++;
		}
	return(count);
}

void	single_argument(t_ls *ls, char *dir_path_str)
{
	struct dirent	*data;
	DIR				*dir;
	int				count;

	dir = opendir(dir_path_str);
	while((data = readdir(dir)) != NULL)
	{
		if(data->d_name[0] != '.')
		{
			if(ls == NULL)
				ls = create(data->d_name);
			else
				ls = append(ls, data->d_name);
		}
	}
	merge_sort(&ls);
//	count = get_count(ls); // Will be used later when alligning columns
	print_file_name(ls);
	delete_list(&ls);
}

/*
** **ft_double_strdup takes the number of arguments and the a 2D array to create
** a 2 dimensional array.
** This function is used to obtain a 2d string that will be stored in the struct
** so fewer parameters are passed around
*/

char **ft_double_strdup(int argc, char *source[])
{
	char **dest;
	int i;

	i = 0;
	dest = malloc(sizeof (char *) * (argc + 1));
	if (dest == NULL || source == NULL)
		return (NULL);
	ft_bzero(dest, argc +1);
	while (i < argc)
	{
		dest[i] = ft_strdup(source[i]);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

int main(int argc, char *argv[])
{
	t_ls	*ls;
	t_info	info;

	ls = NULL;
	info.argc = argc;
	info.argv = ft_double_strdup(argc, argv);

/*
// To test stored string
	int i = 0;
	while(i < argc)
		printf("|%s|\n", info->argv[i++]);
	return(0);
*/

	if(argc == 1)
		single_argument(ls, ".");
	else if(argc > 1)
		ls_start_parsing(ls, &info);
	return(0);

}
