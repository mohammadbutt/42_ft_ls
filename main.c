/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 13:24:55 by mbutt             #+#    #+#             */
/*   Updated: 2019/09/20 18:49:34 by mbutt            ###   ########.fr       */
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
** This function willl be modified later, to account for if the string is a
** directory then we should be able to open the directory
*/

void ft_exit_no_dir(char *str)
{
//	ft_printf("ls: %s: No such file or directory\n", str);
//	exit(EXIT_SUCCESS);
	perror(str);
	exit(EXIT_SUCCESS);
}

void ls_start_parsing(t_ls *ls, int argument_count, char **str)
{
	int i;
	int j;
	DIR *directory;
	struct dirent *dir;

	i = 1;
	j = 0;
	
	while(i < argument_count)
	{
		if(str[i][j] != '-')
		{
			directory = opendir(str[i]);
			if(directory == NULL)
			{
				ft_exit_no_dir(str[i]);
//				perror("ls");
//				exit(EXIT_SUCCESS);
			}
			//	ft_printf("Folder does not exist\n");
			else
			{
				dir = readdir(directory);
				ft_printf("Folder exists\n");
			}
//			printf("|%d|\n", directory);
//			ft_exit_no_dir(str[i]);
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

int main(int argc, char **argv)
{
	t_ls	ls;
	int		i;

	i = 0;
	initialize_ls_values(&ls);
	if(argc > 1)
	{
		ls_start_parsing(&ls, argc, argv);
		printf("flag.l|%d|\n", ls.flags.l);
		printf("flag.a|%d|\n", ls.flags.a);
		printf("flag.t|%d|\n", ls.flags.t);
		printf("flag.r|%d|\n", ls.flags.r);
		printf("flag.uppercase_r|%d|\n", ls.flags.uppercase_r);
	}
//	printf("argument counter:|%d|\n", argc);
//	if(argc >= 2)
//		ft_printf("argument counter\n");
//	if(argv[1])
//		ft_printf("argument vector\n");
}
/*
int main(void)
{
	char *str1 = "Test";
	char str2 = 't';

	printf("|%s|\n", strchr(str1, str2));
}
*/