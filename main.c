/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 13:24:55 by mbutt             #+#    #+#             */
/*   Updated: 2019/09/25 18:28:54 by mbutt            ###   ########.fr       */
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
** Return Values: 1 for valid. 0 for invalid
*/

int is_flag_valid(char c)
{
	int i;

	i = 0;
	while(VALID_FLAG[i])
	{
		if(VALID_FLAG[i] == c)
			return(1);
		i++;
	}
	return(0);
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
	printf("Does it come here?1\n");
	if(c == 'l')
		info->flags.l = true;
	else if(c == 'a')
		info->flags.a = true;
	else if(c == 't')
		info->flags.t = true;
	else if(c == 'r')
		info->flags.r = true;
	else if(c == 'R')
		info->flags.uppercase_r = true;
	printf("Does it come here?2\n");
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

void	ft_no_dir(char *str)
{
	ft_printf("ft_ls: ");
	perror(str);
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


//void	process_dir(t_ls *ls, t_info *info, int arg_count, char **str)
void	process_dir(t_ls *ls, t_info **info, int arg_count, char **str)
{
	struct dirent	*data;
	DIR				*dir;
//	int				i;
//	bool			valid_dir;
	
//	i = 1;
//	valid_dir = false;
//	printf("Does it come here1?\n");
//	printf("|%d|\n", info->va.i);
	(*info)->va.i = 1;
//	printf("Does it come here2?\n");
	(*info)->va.valid_dir = false;
//	printf("Does it come here3?\n");
	while((*info)->va.i < arg_count)
	{
		dir = opendir(str[(*info)->va.i]);
		if(dir == NULL)
			ft_no_dir(str[(*info)->va.i]);
//		(dir == NULL) && (ft_no_dir(str[i]));
		(*info)->va.i++;
	}
	(*info)->va.i = 1;
	while((*info)->va.i < arg_count)
	{
		dir = opendir(str[(*info)->va.i]);
		if(dir != NULL)
		{
			((*info)->va.valid_dir == true) && (ft_printf("\n"));
			(arg_count > 2) && (ft_printf("%s:\n", str[(*info)->va.i]));
			single_argument(ls, str[(*info)->va.i]);
			(*info)->va.valid_dir = true;
		}
		(*info)->va.i++;
	}
	exit(EXIT_SUCCESS);
}


/*
void	process_dir(t_ls *ls, t_info *info, int arg_count, char **str)
{
	struct dirent	*data;
	DIR				*dir;
	int				i;
	bool			valid_dir;
	
	i = 1;
	valid_dir = false;
	while(i < arg_count)
	{
		dir = opendir(str[i]);
		if(dir == NULL)
			ft_no_dir(str[i]);
//		(dir == NULL) && (ft_no_dir(str[i]));
		i++;
	}
	i = 1;
	while(i < arg_count)
	{
		dir = opendir(str[i]);
		if(dir != NULL)
		{
			(valid_dir == true) && (ft_printf("\n"));
			(arg_count > 2) && (ft_printf("%s:\n", str[i]));
			single_argument(ls, str[i]);
			valid_dir = true;
		}
		i++;
	}
	exit(EXIT_SUCCESS);
}
*/




void	ls_start_parsing(t_ls *ls, t_info *info, int arg_count, char **str)
{
	struct dirent	*data;
	DIR				*dir;
	int				count;
	int				i;
	int				j;

	i = 1;
	j = 0;

	if(str[i][j] != '-')
	{
		process_dir(ls, &info, arg_count, str);
//		process_dir(ls, info, arg_count, str);
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


//void initialize_ls_values(t_ls *ls)
void	initialize_info_values(t_info *info)
{
//	ft_bzero(&ls->flags, sizeof(ls->flags));
	ft_bzero(&info->flags, sizeof(info->flags));
}

/*
** Linked List functions just to store file and folder names when argc is 1
** ./ft_ls
*/

t_ls	*create(char *file_name)
{
	t_ls *new_node;

	new_node = malloc(sizeof(t_ls));
//	new_node = malloc(sizeof(t_ls) + 1);
	if(new_node == NULL)
		exit(EXIT_SUCCESS);

	new_node->file_name = ft_strdup(file_name);
	new_node->next = NULL;
	return(new_node);
}

t_ls *append(t_ls *head, char *file_name)
{
	t_ls *cursor;
	t_ls *new_node;

	cursor = head;
	while(cursor->next != NULL)
		cursor = cursor->next;
	new_node = create(file_name);
	cursor->next = new_node;
	return(head);
}


void print_file_name(t_ls *ls)
{
	int i;
	char *str;
	

	i = 0;
	while(ls)
	{
		str = ls->file_name;
		printf("%s\n", str);
		ls = ls->next;
	}
//	return(0);
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


//void	single_argument(t_ls *ls)
//t_ls	*single_argument(t_ls *ls)
//void	single_argument(t_ls *ls)
void	single_argument(t_ls *ls, char *dir_path_str)
{
	struct dirent	*data;
	DIR				*dir;
	int				count;

//	dir = opendir(".");
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
//	return(ls);
}


/*
void	single_argument(t_ls *ls, t_info *info)
{
//	struct dirent	*data;
	DIR				*dir;
	int				count;

	dir = opendir(".");
	while((info->data = *(readdir(dir))) != NULL)
	{
		if(info->data.d_name[0] != '.')
		{
			if(ls == NULL)
				ls = create(info->data.d_name);
			else
			{
				ls = append(ls, info->data.d_name);
//				append(ls, data->d_name);
//				ft_printf("%s\n", ls->file_name);
			}
		}
	}
	ft_printf("\n\n");
	merge_sort(&ls);
	count = get_count(ls);
	ft_printf("|%d|\n", count);
	print_file_name(ls);
//	return(ls);
}
*/


char **ft_double_strdup(int argc, char *source[])
{
	char **dest;
	char temp[1024];
	int i;

	i = 0;
	dest = malloc(sizeof (char *) * (argc + 1));
	if(dest == NULL)
		return(NULL);
	ft_bzero(dest, sizeof(dest));
	if(source)
	{
		while(i < argc)
		{
			dest[i] = ft_strdup(source[i]);
			i++;
		}
	}
	dest[i] = NULL;
	return(dest);
}


int main(int argc, char *argv[])
{
	t_ls	*ls;
	t_info	info;

	ls = NULL;
	info.arg_count = argc;
	info.arg_str = ft_double_strdup(argc, argv);

/*
// To test stored string
	int i = 0;
	while(i < argc)
	{
		printf("|%s|\n", info.arg_str[i]);
		i++;
	}
*/
	if(argc == 1)
		single_argument(ls, ".");
	else if(argc > 1)
		ls_start_parsing(ls, &info, argc, argv);
	return(0);
}
