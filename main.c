/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 13:24:55 by mbutt             #+#    #+#             */
/*   Updated: 2019/10/02 12:11:31 by mbutt            ###   ########.fr       */
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
// Below functions are created to handle dir -R flag
t_ls *sorted_merge_dir(t_ls *a, t_ls *b)
{
	t_ls *result;

	result = NULL;
	if(a == NULL)
		return(b);
	else if(b == NULL)
		return(a);
	if(ft_strcmp(a->dir_path, b->dir_path) <= 0)
	{
		result = a;
		result->next = sorted_merge_dir(a->next, b);
	}
	else
	{
		result = b;
		result->next = sorted_merge_dir(a, b->next);
	}
	return(result);
}

void	merge_sort_dir(t_ls **head_ref)
{
	t_ls *head;
	t_ls *a;
	t_ls *b;

	head = *head_ref;
	if(head == NULL || head->next == NULL)
		return;
	front_back_split(head, &a, &b);
	merge_sort_dir(&a);
	merge_sort_dir(&b);
	*head_ref = sorted_merge_dir(a, b);
}

t_ls	*store_valid_dir(t_ls *ls, char *dir_path_str)
{
	if(ls == NULL)
		ls = create_list_for_dir(dir_path_str);
	else
		ls = append_list_for_dir(ls, dir_path_str);
	return(ls);
}

t_ls	*store_file_name(t_ls *ls, char *file_name)
{
	if(ls == NULL)
		ls = create(file_name);
	else
		ls = append(ls, file_name);
	return(ls);
}

// Above functions are created to handle dir -R flag

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

t_ls	*store_invalid_file_name(t_ls *ls,  char *invalid_path_str)
{

	if(ls == NULL)
		ls = create_list_for_invalid(invalid_path_str);
	else
		ls = append_list_for_invalid(ls, invalid_path_str);
	return(ls);
}


void print_invalid_file_name(t_ls *ls)
{
	int i;
	char *invalid_str;
	
	i = 0;
	while(ls)
	{
//		invalid_str = ls->invalid_file_name;
		invalid_str = ls->file_name;
		ft_printf("ft_ls: ");
		perror(invalid_str);
		ls = ls->next;
	}
}
/*
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
			ls = store_invalid_file_name(ls, arg_str[i]);
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
*/

/*
** process_dir_invalid will process invalid files names
** stat is used which takes in the file name and the stat struct and returns a
** a number.
** If stat returns 0, it means file exists and it is a valid file.
** If stat return -1, it means file does not exist and it is an invalid file.
**
** Note: Both Valid files and folders will have a value of 0, which is why in
** function process_valid_file, in the if statement additional statement is
** included to check if (opendir(file_name_str) == NULL) if it is NULL and it is
** 0 it means, the selected item will only be a file.
*/
void process_invalid_file(t_ls *ls, t_info *info)
{
	struct stat		meta;
	int				file_status;
	char			**arg_str;
	int				arg_count;
	int 			i;

	arg_str = info->argv;
	arg_count = info->argc;
	i = info->var.i;
	while(i < arg_count)
	{
		file_status = stat(arg_str[i], &meta);
		if(file_status < 0)
			ls = store_file_name(ls, arg_str[i]);
		i++;
	}
	if(ls != NULL)
	{
		merge_sort(&ls);
		print_invalid_file_name(ls);
		delete_list(&ls);
	}
}

void	process_valid_file(t_ls *ls, t_info *info)
{
	struct stat		meta;
	int				file_status;
	char			**arg_str;
	int				arg_count;
	int 			i;

	arg_str = info->argv;
	arg_count = info->argc;
	i = info->var.i;
	while(i < arg_count)
	{
		file_status = stat(arg_str[i], &meta);
		if((file_status == 0) && (opendir(arg_str[i]) == NULL))
			ls = store_file_name(ls, arg_str[i]);
		i++;
	}
	if(ls != NULL)
		info->var.new_line = true;
	else if(ls == NULL)
		info->var.new_line = false;
	if(ls != NULL)
	{
		merge_sort(&ls);
		print_file_name(ls);
		delete_list(&ls);
	}
}

/*
** 1. stat(dirent->d_name, &stat) has to be called first
** 2. S_ISDIR(stat.st_mode) is used to idetify if a given file is directory.
** Since the above order matters: in the below if statement stat has to appear
** first:
** if((stat(full_path, &meta) == 0) && (S_ISDIR(meta.st_mode) == 1))
**
** swapping the order of stat with S_ISDIR as shown below will not work:
** if((S_ISDIR(meta.st_mode) == 1) && (stat(full_path, &meta) == 0))
**
** Return Values:
** 1 means it is a directory.
** 0 means it is a file.
** -1 mean it is an invalid file.
** _POSIX_PATH_MAX can store upto 256 characters
*/
t_ls *implement_recurssion(char *path, t_ls *temp_ls, t_info *info)
{
	struct dirent	*dr;
	struct stat		meta;
	DIR *dir;
	char full_path[_POSIX_PATH_MAX];

	if((dir = opendir(path)) == NULL)
		return(temp_ls);
	while((dr = readdir(dir)) != NULL)
	{
		ft_strcpy(full_path, path);
		(full_path[ft_strlen(path) - 1] != '/')	&& (ft_strcat(full_path, "/"));
		ft_strcat(full_path, dr->d_name);
		if((stat(full_path, &meta) == 0) && (S_ISDIR(meta.st_mode) == 1))
		{
			if(dr->d_name[0] != '.')
			{
//				ft_printf("%s\n", full_path);
				temp_ls = store_file_name(temp_ls, full_path);
				implement_recurssion(full_path, temp_ls, info);

//				ft_printf("|%s|\n", temp_ls->file_name);
//				temp_ls = store_file_name(temp_ls, info->argv[info->var.i]);

//				merge_sort(&temp_ls);
//				print_file_name(temp_ls);
//				delete_list(&temp_ls);
			}
		}
	}
//	ft_printf("1:\n");
//	ft_printf("|%s|\n", temp_ls->file_name);
//	merge_sort(&temp_ls);
//	printf("|%s\n", temp_ls->file_name);
//	print_file_name(temp_ls);
//	delete_list(&temp_ls);

	closedir(dir);
	return(temp_ls);
}
void process_dir_valid(t_ls *ls, t_info *info)
{
	t_ls			*temp_ls;
	DIR				*dir;

	temp_ls = NULL;
	if(info->flag.uppercase_r == false)
	{
		while((info->var.i < info->argc) && (info->flag.uppercase_r == false))
		{
			dir = opendir(info->argv[info->var.i]);
			if (dir != NULL)
				temp_ls = store_valid_dir(temp_ls, info->argv[info->var.i]);
			(dir != NULL) && (closedir(dir));
			info->var.i++;
		}
	}
	ft_printf("l:|%d|\n", info->flag.l);
	ft_printf("a:|%d|\n", info->flag.a);
	ft_printf("t:|%d|\n", info->flag.t);
	ft_printf("r:|%d|\n", info->flag.r);
	ft_printf("R:|%d|\n", info->flag.uppercase_r);

//	else if(info->flag.uppercase_r == true)
//	{
//		ft_printf("|%d|\n", info->argc);
//		implement_recurssion(info->argv[info->var.i], temp_ls, info);
//	}

	merge_sort_dir(&temp_ls);
	while(temp_ls)
	{
		(info->var.new_line == true) && (ft_printf("\n"));
		(info->argc > 2) && (ft_printf("%s:\n", temp_ls->dir_path));
		if(info->flag.uppercase_r == false)
			single_argument(ls, temp_ls->dir_path);
		info->var.new_line = true;
		temp_ls = temp_ls->next;
	}
	delete_list(&temp_ls);
}

/*
** info->var.i = i
** info->argv = arg_string
** info->argc = arg_count
*/

/*
// Adding recurssion;
void process_dir_valid(t_ls *ls, t_info *info)
{
	t_ls			*temp_ls;
	DIR				*dir;

	temp_ls = NULL;
	while(info->var.i < info->argc)
	{
		dir = opendir(info->argv[info->var.i]);
		if(dir != NULL)
			temp_ls = store_valid_dir(temp_ls, info->argv[info->var.i]);
		(dir != NULL) && (closedir(dir));
		info->var.i++;
	}
	merge_sort_dir(&temp_ls);
	while(temp_ls)
	{
		(info->var.new_line == true) && (ft_printf("\n"));
		(info->argc > 2) && (ft_printf("%s:\n", temp_ls->dir_path));
		if(info->flag.uppercase_r == false)
			single_argument(ls, temp_ls->dir_path);
		info->var.new_line = true;
		temp_ls = temp_ls->next;
	}
	delete_list(&temp_ls);
}
*/



/*
** function process_dir does the below three things and the order matters.
** which is why the functions is split into three parts.
** 1. process_invalid_file is called to store names of files that do not
** exist, to store them in a linked list, sort them in lexical order and then
** invalid file names are printed.
** 2. process_valid_file is then called to store names of files that are
** actually valid, these are files they may not have a file extension and may
** simply just be a file called file_1, or they may have a file extension,
** such as file_1.c, file_1.o file_1.txt. As long as the file is valid, it is
** stored in a linked list, sorted via merge sort, and then printed.
** 3. process_dir_valid is then called to store the names of folders. Names of
** the folders are stored in a linked list, sorted using merge sort.
** Then names of sorted folders are passed through so the contents of each folder
** can be printed.
*/

void	process_dir(t_ls *ls, t_info *info)
{
	info->var.i = info->var.temp_i;
	process_invalid_file(ls, info);

	info->var.i = info->var.temp_i;
	process_valid_file(ls, info);

	info->var.i = info->var.temp_i;
	process_dir_valid(ls, info);
	exit(EXIT_SUCCESS);
}

/*
** Function handle_improper_usage_of_dash handles the edge cases with dash.
** 1. If the 0th character of the 1st argument is not a '-', dash.
** 2. If the 0th character of the 1st argument is a '-', dash, but 1st character
** is '\0', which means '-', dash, is the only chracter present.
** Below are some of the commands it will handle:
** ./ft_ls abc
** If abc folder does not exist, it will print:
** "ft_ls: abc: No such file or directory"
**
** ./ft_ls abc
** If abc folder exists it will will print contents of that folder.
** 
** ./ft_ls
** It will print contents of the current/root directory.
**
** For the second if statement:
** ./ft_ls -
** It will print conetns of the folder if there is a directory named '-'. But
** if a directory does not exist with the name of '-', then it will print the
** following message.
** ft_ls: -: No such file or directory
*/

void	handle_improper_usage_of_dash(t_ls *ls, t_info *info)
{
	int i;
	i = 1;
	if(info->argv[i][0] != '-')
		process_dir(ls, info);
	else if(info->argv[i][0] == '-' && info->argv[i][1] == '\0')
		process_dir(ls, info);
}

int		flag_status(t_info *info)
{
	if(info->flag.l == true || info->flag.a == true || info->flag.t == true)
		return(1);
	else if(info->flag.r == true || info->flag.uppercase_r == true)
		return(1);
	return(0);
}

void	ls_start_parsing(t_ls *ls, t_info *info)
{
	int				i;
	int				j;
	int				strlen;
	bool			double_break;
	char			current;

	i = 1;
	j = 1;
	strlen = 0;
	info->var.temp_i = 1;
	double_break = false;
	current = info->argv[i][0];
	if((current != '-') || (current == '-' && info->argv[i][1] == '\0'))
		handle_improper_usage_of_dash(ls, info);
// Above works fine.
	else if(info->argv[i][0] == '-' && info->argv[i][1] != '\0')
	{
//		handle_dash_arguments(ls, info);		
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
/*	
	ft_printf("i:|%d|\n", i);
	ft_printf("info->argc|%d|\n", info->argc);
	ft_printf("l:|%d|\n", info->flag.l);
	ft_printf("a:|%d|\n", info->flag.a);
	ft_printf("t:|%d|\n", info->flag.t);
	ft_printf("r:|%d|\n", info->flag.r);
	ft_printf("R:|%d|\n", info->flag.uppercase_r);
*/	
		
	if(i == info->argc && (flag_status(info) == 0))
		single_argument(ls, ".");
	else if(i == info->argc && info->flag.uppercase_r == true)
	{
//		ls = implement_recurssion(".", ls, info);
//		merge_sort_dir(&ls);
		ls = implement_recurssion(".", ls, info);
		merge_sort(&ls);
		print_file_name(ls);
	}
/*
	while(ls)
	{
		(info->var.new_line == true) && (ft_printf("\n"));
		(info->argc > 2) && (ft_printf("%s:\n", ls->dir_path));
		if(info->flag.uppercase_r == false)
			single_argument(ls, ls->dir_path);
		info->var.new_line = true;
		ls = ls->next;
	}
	delete_list(&ls);
*/

	while(i < info->argc)
	{
		info->var.temp_i = i;
		process_dir(ls, info);
		i++;
	}

	}

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
// Below functions are created to handle dir for -R flag
t_ls	*create_list_for_dir(char *dir_path_str)
{
	t_ls *new_node;

	new_node = malloc(sizeof(t_ls));
	if(new_node == NULL)
		exit(EXIT_SUCCESS);

	new_node->dir_path = ft_strdup(dir_path_str);
	new_node->next = NULL;
	return(new_node);
}

t_ls	*append_list_for_dir(t_ls *head, char *dir_path_str)
{
	t_ls *cursor;
	t_ls *new_node;

	cursor = head;
	while(cursor->next != NULL)
		cursor = cursor->next;
	new_node = create_list_for_dir(dir_path_str);
	cursor->next = new_node;
	return(head);
}

// Above functions are created to handle dir for -R flag

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
** Function print_file_name will print contents, files and folders, of the
** current directory.
*/

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


/*
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
*/

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

/*
** if statement:
** if(data->d_name[0] != '.') -> will help ignore hidden files which begin with
** '.', dot, '..', and dot dot.
** And then it will start storing names of all files and folders in a linked
** list, and as mentioned earlier, but ignore hidden files which begin with '.'
*/
void	single_argument(t_ls *ls, char *dir_path_str)
{
	struct dirent	*data;
	DIR				*dir;
//	int				count;

	dir = opendir(dir_path_str);
	while((data = readdir(dir)) != NULL)
	{
		if(data->d_name[0] != '.')
			ls = store_file_name(ls, data->d_name);
	}
	if(dir != NULL)
		closedir(dir);
	merge_sort(&ls);
//	count = get_count(ls); // Will be used later when alligning columns
	print_file_name(ls);
	delete_list(&ls);
}

/*
** In multiple_argument, single_argument gets called first and then directoreis
** will be stored in a linked list and then the function will be called onto
** itself.
** Process for storing directories is similar to how files and folders are
** stored in single_argument function. But multiple_argument function does two
** addtional things.
** 1. Stores folders in a linked list.
** 2. Calls onto itself for recursion.
**
*/

void	multiple_argument(t_ls *ls, t_info *info, char *dir_path_str)
{
	struct dirent	*data;
	DIR				*dir;
//	int				count;

	dir = opendir(dir_path_str);
	while((data = readdir(dir)) != NULL)
	{
		if(data->d_name[0] != '.')
			ls = store_file_name(ls, data->d_name);
	}
	if(dir != NULL)
		closedir(dir);
	merge_sort(&ls);
//	count = get_count(ls); // Will be used later when alligning columns
	print_file_name(ls);
	multiple_argument(ls, info, dir_path_str);
//	process_dir_valid(ls, info); //
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
