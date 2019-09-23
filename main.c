/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 13:24:55 by mbutt             #+#    #+#             */
/*   Updated: 2019/09/23 14:33:30 by mbutt            ###   ########.fr       */
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

void ls_start_parsing(t_ls *ls, int argument_count, char **str)
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
				ls_collect_flags(ls, str[i][j]);
//				printf("flag.l|%d|\n", ls->flags.l);
			}
			j++;
		}
		j = 0;
		i++;
	}
}

void initialize_ls_values(t_ls *ls)
{
	ft_bzero(&ls->flags, sizeof(ls->flags));
}

/*
** Linked List functions just to store file and folder names when argc is 1
** ./ft_ls
*/

t_ls	*create(char *file_name)
{
	t_ls *new_node;

	new_node = malloc(sizeof(t_ls));
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


int print_file_name(t_ls *ls)
{
	int i;
	char *str;
	

	i = 0;
	while(ls)
	{
		str = ls->file_name;
		printf("|%s|\n", str);
		ls = ls->next;
	}
	return(0);
}

void	single_argument(t_ls *ls)
//t_ls	*single_argument(t_ls *ls)
{
	struct dirent	*data;
	DIR				*dir;

	dir = opendir(".");
	while((data = readdir(dir)) != NULL)
	{
		if(data->d_name[0] != '.')
		{
			if(ls == NULL)
				ls = create(data->d_name);
			else
			{
				ls = append(ls, data->d_name);
//				append(ls, data->d_name);
//				ft_printf("%s\n", ls->file_name);
			}
		}
	}
	ft_printf("\n\n");
	print_file_name(ls);
//	return(ls);
}


int main(int argc, char **argv)
{
	t_ls *ls;

	ls = NULL;
	ft_bzero(&ls,sizeof(&ls));
//	ls = malloc(sizeof(ls));
	if(argc == 1)
	{
		single_argument(ls);
//		ls = single_argument(ls);
	}
	else if(argv[0][1] != '\0')
		ft_printf("Just filling in to silence Wall Wextra Werror flag\n");
	
	print_file_name(ls);
//	ft_printf("|%s|\n", ls.file_name);
}

/*
int main(int argc, char **argv)
{
	t_ls	ls;
	int		i;

	i = 0;
	initialize_ls_values(&ls);
	if(argc > 1)
	{
		ls_start_parsing(&ls, argc, argv);
//		printf("flag.l|%d|\n", ls.flags.l);
//		printf("flag.a|%d|\n", ls.flags.a);
//		printf("flag.t|%d|\n", ls.flags.t);
//		printf("flag.r|%d|\n", ls.flags.r);
//		printf("flag.uppercase_r|%d|\n", ls.flags.uppercase_r);
	}
//	printf("argument counter:|%d|\n", argc);
//	if(argc >= 2)
//		ft_printf("argument counter\n");
//	if(argv[1])
//		ft_printf("argument vector\n");
}
*/
/*
int main(void)
{
	char *str1 = "Test";
	char str2 = 't';

	printf("|%s|\n", strchr(str1, str2));
}
*/
