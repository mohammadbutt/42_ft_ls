/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:59:19 by mbutt             #+#    #+#             */
/*   Updated: 2019/11/01 23:15:28 by mbutt            ###   ########.fr       */
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


void ft_exit_illegal_option(char c)
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

void ft_permission_denied(char *str)
{
	ft_printf("ft_ls: ");
	perror(str);
}
/*
void	ft_no_dir(char *dir_path_str)
{
	ft_printf("ft_ls: ");
	perror(dir_path_str);
}
*/
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

t_ls	*create(char *valid_file_path_str)
{
	t_ls *new_node;

	new_node = malloc(sizeof(t_ls));
//	new_node = NULL;
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

// Storing file names in a linked list with slash index

t_ls	*create_with_index(char *valid_file_path_str, int index)
{
	t_ls *new_node;

	new_node = malloc(sizeof(t_ls));
	if(new_node == NULL)
		exit(EXIT_SUCCESS);
	new_node->file_name = ft_strdup(valid_file_path_str);
	new_node->slash_index = index;
	new_node->next = NULL;
	return(new_node);
}

t_ls *append_with_index(t_ls *head, char *valid_file_path_str, int index)
{
	t_ls *cursor;
	t_ls *new_node;

	cursor = head;
	while(cursor->next != NULL)
		cursor = cursor->next;
	new_node = create_with_index(valid_file_path_str, index);
	cursor->next = new_node;
	return(head);
}


t_ls	*store_file_name_with_index(t_ls *ls, char *file_name, int index)
{
	if(ls == NULL)
		ls = create_with_index(file_name, index);
	else
		ls = append_with_index(ls, file_name, index);
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

/*
** Only one merge sort is created because invalid files are always sorted in
** lexical order regardless of what flags there are.
*/

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

/*
** Only one merge sort is created because invalid files are always sorted in
** lexical order regardless of what flags there are.
*/

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


void	delete_list_file_name(t_ls **head_ref);

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
		if(file_status == -1)
			ls = store_file_name(ls, arg_str[i]);
		i++;
	}

//	ft_printf("i:|%s|\n", i);
//	ft_printf("info->vari.i|%d|\n", info->var.i);
	if(ls != NULL)
	{
		merge_sort(&ls);
		print_invalid_file_name(ls);
		delete_list_file_name(&ls);
		info->print_path_name = true;
		info->no_dot_slash = true;
	}
//	ft_printf("Does it come here\n");
}

/*
** In function process_valid_file.
** If a directory/folder has permission denied, it will still be able to go
** through the below if statement
** 	if((stat(arg_str[i], &meta) == 0) && (opendir(arg_str[i]) == NULL))
** which is why an additional if statement will be placed:
** 	if(S_ISREG(meta.st_mode))
** This if statement will determine if a file is a regular file or not.
** 
** The below one liner can also check if its a valid file as well as a directory:
**
** if((stat(arg_str[i], &meta) == 0) && (S_ISREG(meta.st_mode))); 
*/
void	delete_list_file_name(t_ls **head_ref);

void	process_valid_file(t_ls *ls, t_info *info)
{
	struct stat		meta;
	char			**arg_str;
	int				arg_count;
	int 			i;

	arg_str = info->argv;
	arg_count = info->argc;
	i = info->var.i;
	while(i < arg_count)
	{
//		if((stat(arg_str[i], &meta) == 0) && (opendir(arg_str[i]) == NULL))
//			if(S_ISREG(meta.st_mode))
//	If below if statement breaks, replace it with the above if statement
		if((stat(arg_str[i], &meta) == 0) && (S_ISREG(meta.st_mode)))
			ls = store_file_name(ls, arg_str[i]);
		i++;
	}
//	if(ls != NULL)
//	{
//		info->var.new_line = true;
//		info->print_path_name = true;
//		info->no_dot_slash = true;
//	}
//	else if(ls == NULL)
//	{
//		info->var.new_line = false;
//		info->print_path_name = false;
//	}
	if(ls != NULL)
	{
		merge_sort(&ls);
		print_file_name(ls, info);
//		delete_list(&ls);
		delete_list_file_name(&ls);
		info->var.new_line = true;
		info->print_path_name = true;
		info->no_dot_slash = true;
	}
}

/*
t_ls	*recursive_for_reference(t_ls *temp_ls, t_info *info, char *path)
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
				temp_ls = store_valid_dir(temp_ls, full_path);
				recursive_for_reference(temp_ls, info, full_path);
			}
		}
	}
	closedir(dir);
	return(temp_ls);
}
*/
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
** Return Values of (stat(full_path, &meta):
** 0 for both valid file and directory.
**
** Return Values of (S_ISDIR(meta.st_mode):
** 1 means it is a directory.
** 0 means it is a file.
** -1 mean it is an invalid file.
** _POSIX_PATH_MAX can store upto 256 characters
*/


//t_ls *store_dir_recursively(char *path, t_ls *temp_ls, t_info *info)
/*
int	store_dir_recursively(t_ls *temp_ls, t_info *info, char *path)
{
	struct dirent	*dr;
	struct stat		meta;
	DIR *dir;
	char full_path[_POSIX_PATH_MAX];

//	if((dir = opendir(path)) == NULL)
//		return(1);
//	while(((dr = readdir(dir)) != NULL) && (temp_ls))
	while(temp_ls)
	{
		if((dir = opendir(path)) == NULL)
			return(1);
		while((dr = readdir(dir)) != NULL)

		dr = readdir(dir);
		ft_strcpy(full_path, path);
		(full_path[ft_strlen(path) - 1] != '/')	&& (ft_strcat(full_path, "/"));
		ft_strcat(full_path, dr->d_name);
		if((stat(full_path, &meta) == 0) && (S_ISDIR(meta.st_mode) == 1))
		{
			if(dr->d_name[0] != '.')
			{

//				temp_ls = store_valid_dir(temp_ls, full_path);  // Changing
//				store_dir_recursively(temp_ls, info, full_path); // Changing
				temp_ls = store_file_name(temp_ls, temp_ls->file_name);
				merge_sort(&temp_ls);
//				single_argument(temp_ls, info, full_path);
				single_argument(temp_ls, info, temp_ls->file_name);
//				store_dir_recursively(temp_ls, info, temp_ls->file_name);
				delete_list(&temp_ls);
			}
		}
		temp_ls = temp_ls->next;
	}
	if(dir != NULL)
		closedir(dir);
	return(0);
}
*/

void	free_inner_dir(t_ls *ls)
{
	t_ls *temp_ls;

//	if(ls == NULL)
//		return;
	while(ls != NULL)
	{
		if(ls->file_name)
			free(ls->file_name);
		if(ls->dir_path)
			free(ls->dir_path);
		temp_ls = ls->next;
		free(ls);
		ls = temp_ls;
	}
}

void	delete_list(t_ls **head_ref)
{
	t_ls *current_node;
	t_ls *next_node;

	current_node = *head_ref;
//	if(current == NULL)
//		return;
	while(current_node != NULL)
	{
		next_node = current_node->next;
		free(current_node);
		current_node = next_node;
	}
	*head_ref = NULL;
}

void delete_list_file_name(t_ls **head_ref)
{
	t_ls *current_node;
	t_ls *next_node;

	current_node = *head_ref;
//	if(current == NULL)
//		return;
	while(current_node != NULL)
	{
		next_node = current_node->next;
		if(current_node->file_name)
			free(current_node->file_name);
		if(current_node)
			free(current_node);
		current_node = next_node;
	}
	*head_ref = NULL;
}

void	delete_list_dir_path(t_ls **head_ref)
{
	t_ls *current_node;
	t_ls *next_node;

	current_node = *head_ref;
	while(current_node != NULL)
	{
		next_node = current_node->next;
		free(current_node->dir_path);
		free(current_node);
		current_node = next_node;
	}
	*head_ref = NULL;
}

int		start_recursive_call(t_ls *temp_ls, t_info *info);
t_ls	*store_root_files(t_ls *ls, t_info *info, char *dir_path_str);


/*
** function find_last_slash, returns the index of the last slash that occurs in
** a file path.
** Functions is used in permission denied case, so slashes can be truncated
** from the beginning of the file path, so just the name is returned.
*/

int find_last_slash(char *file_path_with_slash)
{
	int len;

	len = 0;
	len = ft_strlen(file_path_with_slash) - 1;

//	ft_printf("find_last_index|%d|\n", len);
	if(len <= 0)
		return(0);
	while(len)
	{
		if(file_path_with_slash[len] == '/')
			return(len + 1);
		len--;
	}
	return(0);
}

/*
** is_directory returns 1 if a file path is a directory. If file path is not a
** directory, it returns a 0.
*/

/*
int is_directory(char *parent, char *name)
{
	DIR *dir;
	char final_path[_POSIX_PATH_MAX];

	ft_strcpy(final_path, parent);
	ft_strcat(final_path, "/");
	ft_strcat(final_path, name);
	dir = opendir(final_path);
	if(dir == NULL)
		return(0);
	closedir(dir);
	return(1);
}
*/
/*
char *is_directory(char *parent, char *name, char final_path[])
{
	DIR *dir;
	int i;
	int j;

	i = 0;
	j = 0;
//	char final_path[_POSIX_PATH_MAX];

//	if(parent)
//	{
//		while(parent[j])
//			final_path[i++] = parent[j++];
//		final_path[i++] = '/';
//	}
//	j = 0;
//	if(name)
//		while(name[j])
//			final_path[i++] = name[j++];
//	final_path[i] = '\0';


// Try to optemize the below
	ft_strcpy(final_path, parent);
	ft_strcat(final_path, "/");
	ft_strcat(final_path, name);

	dir = opendir(final_path);
	if(dir == NULL)
		return(name);
//		return(0);
	closedir(dir);
	return(final_path);
//	return(1);
}
*/
t_ls	*append_slash(t_ls *new_ls, t_ls *temp_ls, char *path)
{
//	char full_path[_POSIX_PATH_MAX];
//	int	path_len;
	char *full_path;
	int i;
	int j;
	int temp_i;

//	ft_printf(BGREEN"---------Enters append_slash-------\n", NC);
//	path_len = ft_strlen(path) - 1;
//	if(ft_strcmp(temp_ls->file_name, ".") && ft_strcmp(temp_ls->file_name, ".."))
//		return(NULL);
	full_path = malloc(sizeof(char) * (_POSIX_PATH_MAX));
//	full_path = malloc(sizeof(char) * (ft_strlen(path) + 1));
	i = 0;
	j = 0;
	temp_i = 0;
//	new_ls->slash_index = 0;
//	ft_strcpy(full_path, path);
//	(full_path[path_len] != '/') && (ft_strcat(full_path, "/"));
	full_path[0] = 0;
	if(path)
		while(path[j])
			full_path[i++] = path[j++];
	(full_path[i] != '/') && (full_path[i++] = '/');
	temp_i = i;
//	new_ls->slash_index = i;
	while(temp_ls)
	{
		i = temp_i;
//		i = new_ls->slash_index;
		j = 0;
		if(temp_ls->file_name)
//		if((ft_strcmp(temp_ls->file_name, ".")) && (ft_strcmp(temp_ls->file_name, "..")))
			while(temp_ls->file_name[j])
				full_path[i++] = temp_ls->file_name[j++];
	   	full_path[i] = '\0';
//		new_ls = store_file_name(new_ls, full_path);
//		ft_printf("temp_i|%d|\n", temp_i);
		new_ls = store_file_name_with_index(new_ls, full_path, temp_i);
		temp_ls = temp_ls->next;
	}

/*
 deprecated because improved it by retaining index
	while(temp_ls)
	{
//		ft_strcpy(full_path, path);
//		(full_path[path_len] != '/') && (ft_strcat(full_path, "/"));
//		ft_strcat(full_path, temp_ls->file_name);
//		new_ls = store_file_name(new_ls, full_path);
//		temp_ls = temp_ls->next;

	}
*/
/*
	while(temp_ls)
	{
		if(path)
			while(path)
				full_path[i++] = path[j++];
		(full_path[i] != '/') && (full_path[i] = "/");
		if(temp_ls->file_name)
			while(temp_ls->file_name)
				full_path[i]
	}
*/
//	if (full_path != NULL)
	free(full_path);
	return(new_ls);
}

/*
** Just to test how file_names are stored in the linked list.
*/
void print_stored_file_names(t_ls *ls)
{
	while(ls)
	{
		printf("|%s|\n", ls->file_name);
		ls = ls->next;
	}
}

t_ls	*store_file_recursively(t_info *info ,char *path) // -> store inner_dir
{
	struct dirent	*dr;
//	struct stat		meta;
	DIR *dir;
//	char full_path[_POSIX_PATH_MAX];
	t_ls *temp_ls;
	t_ls *new_ls;

	temp_ls = NULL;
	new_ls = NULL;
	if((dir = opendir(path)) == NULL)
	{
		(info->no_dot_slash == false) && (ft_printf("\n./%s\n", path));
		(info->no_dot_slash == true) && (ft_printf("\n%s\n", path));
//		ft_permission_denied(path);
		ft_permission_denied(path + find_last_slash(path));
		return(NULL);
	}
	else if(info->skip_print == false || info->print_path_name == true)
	{
//		if(ft_strcmp(path, ".") && ft_strcmp(path, ".."))
//		{
		if(info->flag.a == false && path[0] != '.')
		{
//			ft_printf(BRED"\n|%s|\n"NC, path);
			(info->no_dot_slash == false) && (ft_printf("\n./%s:\n", path));
			(info->no_dot_slash == true) && (ft_printf("\n%s:\n", path));
		}
	}

//	int len;
//	len = ft_strlen(path) - 1;
	while((dr = readdir(dir)) != NULL)
	{
		if(info->flag.a == true)
			temp_ls = store_file_name(temp_ls, dr->d_name);
		else if(info->flag.a == false && dr->d_name[0] != '.')
		{
//			is_directory(path, dr->d_name, full_path);
//			temp_ls = store_file_name(temp_ls, full_path);
			temp_ls = store_file_name(temp_ls, dr->d_name);
		}
	}
	merge_sort(&temp_ls);

//	print_stored_file_names(temp_ls);

/*
	if(dir != NULL)
		closedir(dir);
	if(temp_ls)
		new_ls = append_slash(new_ls, temp_ls, path);
*/
	(dir != NULL) && (closedir(dir));
//	ft_printf(BGREEN"---Enters store_file_recursively---\n");
	(temp_ls != NULL) && (new_ls = append_slash(new_ls, temp_ls, path));
	delete_list_file_name(&temp_ls);
//	delete_list(&temp_ls);
//	append_slash(&temp_ls)

//	while(temp_ls)
//	{
//		full_path[0] = 0;
//		ft_strcpy(full_path, path);
//		(full_path[ft_strlen(path) - 1] != '/')	&& (ft_strcat(full_path, "/"));
//		ft_strcat(full_path, dr->d_name);
//		temp_ls = store_file_name(temp_ls, full_path);

//	}
//	single_argument(temp_ls, info, full_path);
//	if(temp_ls != NULL)
//		merge_sort(&temp_ls);
//	printf("segimprove\n");
//	printf("========Does it come here========\n");
//	return(temp_ls);
	return(new_ls);
}
/*
// Prints files with Recursion, but speed is slow
	while((dr = readdir(dir)) != NULL)
	{
		if(dr->d_name[0] != '.')
		{
			if((is_directory(path, dr->d_name)) == 1)
			{
				ft_strcpy(full_path, path);
				(full_path[len] != '/') && (ft_strcat(full_path, "/"));
				ft_strcat(full_path, dr->d_name);
				temp_ls = store_file_name(temp_ls, full_path);
			}
			else
				temp_ls = store_file_name(temp_ls, dr->d_name);
		}
	}
*/

/*
// Prints all files but appends slashes with file_names
	int len;
	len = ft_strlen(path) - 1;

	while((dr = readdir(dir)) != NULL)
	{
		if(dr->d_name[0] != '.')
		{
				ft_strcpy(full_path, path);
				(full_path[len] != '/') && (ft_strcat(full_path, "/"));
				ft_strcat(full_path, dr->d_name);
				temp_ls = store_file_name(temp_ls, full_path);
		}
	}
*/
//		if(stat(full_path, &meta) == 0)
/*
			if(dr->d_name[0] != '.')
			{
				if(S_ISDIR(meta.st_mode) == 1)
					temp_ls = store_file_name(temp_ls, full_path);
				else if(S_ISDIR(meta.st_mode) == 0)
					temp_ls = store_file_name(temp_ls, dr->d_name);
			}
*/


/*
	while((dr = readdir(dir)) != NULL)
	{
		if((stat(dr->d_name, &meta) == 0) && (dr->d_name[0] != 0))
		{
			if(S_ISDIR(meta.st_mode))
			{
//			if(dr->d_name[0] != '.')
//			{
				full_path[0] = 0;
				ft_strcpy(full_path, path);
				(full_path[ft_strlen(path) - 1] != '/')	&& (ft_strcat(full_path, "/"));
				ft_strcat(full_path, dr->d_name);
				temp_ls= store_file_name(temp_ls, full_path);
			}
//			}
			else
				temp_ls= store_file_name(temp_ls, dr->d_name);
		}
	}
//	if(dir != NULL)
//		temp_ls = store_root_files(temp_ls, info, path);
	
*/
/*
	if(dir != NULL)
	{
		full_path[0] = 0;
		ft_strcpy(full_path, path);
		(full_path[ft_strlen(path) - 1] != '/')	&& (ft_strcat(full_path, "/"));
		ft_strcat(full_path, dr->d_name);
		single_argument(temp_ls, info, full_path);
		if(stat(full_path, &meta))
			if(dr->d_name[0] != '.')
				temp_ls = store_root_files(temp_ls, info, full_path);
//		print_file_name(temp_ls);
	}
*/
//	printf("(%s)\n", path);
//	printf("Comes here1\n");
//	ft_strcpy(full_path, path);
//	(full_path[ft_strlen(path) - 1] != '/')	&& (ft_strcat(full_path, "/"));
//	ft_strcat(full_path, dr->d_name);


	// 0 means have not found, 1 means found, -1  dont search
/*
	while((dr = readdir(dir)) != NULL)
	{
		if (dr->d_name[0] != '.')
		{
			if(stat(dr->d_name, &meta) == 0)
			{
//				if(S_ISDIR(meta.st_mode))
//				{
//					printf("Does it ever come here\n\n\n\n");
//					full_path[0] = 0;
//					ft_strcpy(full_path, path);
//					(full_path[ft_strlen(path) - 1] != '/')	&& (ft_strcat(full_path, "/"));
//					ft_strcat(full_path, dr->d_name);
//					temp_ls= store_file_name(temp_ls, full_path);
//				}
				if(S_ISREG(meta.st_mode))
				{
//					printf("here2\n\n");
					temp_ls = store_file_name(temp_ls, dr->d_name);
				}
				else
				{
					temp_ls = store_file_name(temp_ls, dr->d_name);
				}
			}
		}
	}
*/
	
/*
	while((dr = readdir(dir)) != NULL)
	{
		if (dr->d_name[0] != '.')
		{
//			if(stat(dr->d_name, &meta) == 0)
//			{
//				if(S_ISDIR(meta.st_mode))
//				{
//					printf("Does it ever come here\n\n\n\n");
					full_path[0] = 0;
					ft_strcpy(full_path, path);
					(full_path[ft_strlen(path) - 1] != '/')	&& (ft_strcat(full_path, "/"));
					ft_strcat(full_path, dr->d_name);
					temp_ls= store_file_name(temp_ls, full_path);
//				}
//				if (S_ISDIR(meta.st_mode))
//					temp_ls = store_file_name(temp_ls, dr->d_name);
//			}
		}
	}
*/
/*
	while((dr = readdir(dir)) != NULL)
	{
		if (dr->d_name[0] != '.')
			temp_ls = store_file_name(temp_ls, dr->d_name);
	}
*/	
/*	
	while((dr = readdir(dir)) != NULL)
	{
		if(stat(dr->d_name, &meta) == 0 && (S_ISDIR(meta.st_mode) == 1))
			if(found_dir == 0)
				found_dir = 1;
		if(found_dir != 1 && dr->d_name[0] != '.')
		{
			if(S_ISDIR(meta.st_mode) == 1) // If it is a folder
				temp_ls = store_file_name(temp_ls, dr->d_name + find_last_slash(dr->d_name));
			else
				temp_ls = store_file_name(temp_ls, dr->d_name);
		}
		else if(found_dir == 1 && dr->d_name[0] != '.')
		{
			full_path[0] = 0;
			ft_strcpy(full_path, path);
			(full_path[ft_strlen(path) - 1] != '/')	&& (ft_strcat(full_path, "/"));
			ft_strcat(full_path, dr->d_name);
			temp_ls = store_file_name(temp_ls, full_path);
			found_dir = -1;
//			found_dir = -1;
		}
*/
//		if(stat(full_path, &meta) == 0)
/*
			if(dr->d_name[0] != '.')
			{
//				if(S_ISDIR(meta.st_mode) == 1)
				if(found_dir == 1)
				{
					temp_ls = store_file_name(temp_ls, full_path);
					found_dir = -1;
				}
				else
					temp_ls = store_file_name(temp_ls, dr->d_name);
			}
*/
//				if(S_ISDIR(meta.st_mode) == 1)	// 1 means its a directory
//					temp_ls = store_file_name(temp_ls, full_path);
//				else if(S_ISDIR(meta.st_mode) == 0) // 0 means its a file
//					temp_ls = store_file_name(temp_ls, dr->d_name);
//				else if(S_ISDIR(meta.st_mode) == 0)
//					temp_ls = store_file_name(temp_ls, full_path + find_last_slash(full_path));
//			}

/*
	while((dr = readdir(dir)) != NULL)
	{
//		full_path[0] = 0;
		ft_strcpy(full_path, path);
		(full_path[ft_strlen(path) - 1] != '/')	&& (ft_strcat(full_path, "/"));
		ft_strcat(full_path, dr->d_name);
		if(stat(full_path, &meta) == 0)
			if(dr->d_name[0] != '.')
			{
//				if(S_ISDIR(meta.st_mode) == 1)
					temp_ls = store_file_name(temp_ls, full_path);
//				else if(S_ISDIR(meta.st_mode) == 0)
//					temp_ls = store_file_name(temp_ls, full_path + find_last_slash(full_path));
			}
	}
*/

/*
	while((dr = readdir(dir)) != NULL)
	{
		if((stat(dr->name, &meta) == 0) && S_ISDIR(meta.st_mode) == 1)
		{
			full_path[0] = 0;
			ft_strcpy(full_path, path);
			(full_path[ft_strlen(path) - 1] != '/')	&& (ft_strcat(full_path, "/"));
			ft_strcat(full_path, dr->d_name);
		}
//		if(stat(full_path, &meta) == 0)
			if(dr->d_name[0] != '.')
			{
				if(S_ISDIR(meta.st_mode) == 1)
					temp_ls = store_file_name(temp_ls, full_path);
				else if(S_ISDIR(meta.st_mode) == 0)
					temp_ls = store_file_name(temp_ls, dr->d_name);
			}
	}
*/
/*

		if((stat(dr->d_name, &meta) == 0) && (S_ISDIR(meta.st_mode) == 1))
		{
		ft_strcpy(full_path, path);
		(full_path[ft_strlen(path) - 1] != '/')	&& (ft_strcat(full_path, "/"));
		}
		ft_strcat(full_path, dr->d_name);
//		{
			if(dr->d_name[0] != '.')
//			if(ft_strcmp(dr->d_name, ".") && ft_strcmp(dr->d_name, ".."))
			{
				temp_ls = store_file_name(temp_ls, dr->d_name);
//				temp_ls = store_file_name(temp_ls, dr->d_name);
//				temp_ls = store_file_name(temp_ls, full_path);
			}
//		}
}
*/
/*
** I had initially decided to store the inner directories on stack as below:
** char full_path[_POSIX_PATH_MAX]
** _POSIX_PATH_MAX which allocates 256 bytes, so I decided to find out the total
** number of files on my current system to get an approximate idea how much
** memory will be reseverd on stack.
** running the below command gave me the total number of files at the root:
** ls -R | wc -l
** This was 45,238.
** 45,238 * 256 = 11,580,928.
** When I allocated this much memory on stack, well it didn't work, but malloc
** will allow memory allocation of upto INT_MAX, which is 2,147,483,647.
** Now there are two nice things about malloc in this case:
** 1. We are able to allocate more memory than stack.
** 2. Memory allocated using malloc can be used again when it's free, but that's
** not the case when memory is allocated on stack, when memory is allocated on
** stack, it can not be freed, the only way would be to reuse that variable
** that has memory on stack.
** Ran a few more test. Might be able to store file names on stack.
** Each occurence can have upto 26,000 recursivce calls.
** skip_first_print is used because when valid directory names are entered,
** they get stored in a linked list: to avoid printing the valid directory
** name right in the beginning skip_first_print is set to true for the first
** time, but when it enters second recursion false is passed in.
** for ./ft_ls -R skip_first_print is set to false because in that case, root
** files and directories need to be printed.
*/

//int		start_recursive_call(t_ls *temp_ls, t_info *info);
/*
t_ls	*store_inner_dir(char *file_path)
{
	char 
}
*/
int		start_recursive_call(t_ls *temp_ls, t_info *info)
{
	t_ls			*inner_dir;
//	t_ls			*new_inner_dir;
	struct	stat	meta;

	inner_dir = NULL;	
	if(temp_ls != NULL && temp_ls->file_name && info->skip_print == false)
		print_file_name(temp_ls, info);

//	if(temp_ls != NULL)
//	{
	while(temp_ls != NULL)
	{
		if(stat(temp_ls->file_name, &meta) == 0 && S_ISDIR(meta.st_mode))
		{
//			ft_printf(BGREEN"----Entering start_recursive_call----\n"NC);
			if(info->flag.a == true)
			{
//				if(ft_strcmp(temp_ls->file_name, ".") && ft_strcmp(temp_ls->file_name, ".."))
//				{
					inner_dir = store_file_recursively(info, temp_ls->file_name);
					info->skip_print = false;
//				}
			}
			else if(info->flag.a == false && temp_ls->file_name[0] != '.')
			{
				inner_dir = store_file_recursively(info, temp_ls->file_name);
				info->skip_print = false;
			}
//			ft_printf(BRED"|%s|\n"NC, temp_ls->file_name);
			if(inner_dir != NULL)
			{
				start_recursive_call(inner_dir, info);
				delete_list_file_name(&inner_dir);
			}
		}
		temp_ls = temp_ls->next;
	}
//	}
//	while(inner_dir)
//	{
//	if(inner_dir->file_name)
//		printf("-------|%s|-----\n", inner_dir->file_name);
//	else
//		printf("-------|Empty|-------\n\n");
//		inner_dir = inner_dir->next;
//	}
/*
	if(temp_ls != NULL)
	{
		printf("----------Working 2-------\n");
		print_file_name(temp_ls);
	}
	else if(temp_ls == NULL)
	{
		printf("<<<<<<<<<<Finished 2>>>>>>>>\n");
		return(1);
	}
*/
	return(0);
}
/*
** info->var.i = i
** info->argv = arg_string
** info->argc = arg_count
** When storing valid directories, all the directories are stored including the
** ones that have permission denied.
** if(dir != NULL)
**		temp_ls = store_valid_dir(temp)
** Above if statement will work, but it will not store directories that have
** permission denied, which is why the below if statement is used to store the
** directories, including the ones that have permission denied:
**
** 	if(stat(info->argv[info->var.i], &meta) == 0)
**		if(S_ISDIR(meta.st_mode) == 1)
**			temp_ls = store_valid_dir(temp);
** This if statement 
*/


/*
** Functions store_dir_path_regular and store_dir_path_for_recurssion
** are really similar. The only difference is:
** 1. store_dir_path_without_flag stores directory in linked list in dir_path.
** 2. store_dir_path_for_recurssion stores directory in linked list in file_name
*/
t_ls	*store_dir_path_regular(t_ls *temp_ls, t_info *info)
{
	struct stat meta;
	DIR 	*dir;

//	while((info->var.i < info->argc) && (info->flag.uppercase_r == false))
	while(info->var.i < info->argc)
	{
		dir = opendir(info->argv[info->var.i]);
		if(stat(info->argv[info->var.i], &meta) == 0)
			if(S_ISDIR(meta.st_mode) == 1)
				temp_ls = store_valid_dir(temp_ls, info->argv[info->var.i]);
//		ft_printf("|%d|", stat(info->argv[info->var.i], &meta));
//		ft_printf("|%d|", S_ISDIR(meta.st_mode));
//		ft_printf("|%s|\n", info->argv[info->var.i]);
//		if(S_ISDIR(meta.st_mode))
//			temp_ls = store_valid_dir(temp_ls, info->argv[info->var.i]);
		(dir != NULL) && (closedir(dir));
		info->var.i++;
	}
	return(temp_ls);
}

t_ls *store_dir_path_recurssion(t_ls *temp_ls, t_info *info)
{
	struct stat meta;
	DIR	*dir;

	while(info->var.i < info->argc)
	{
		dir = opendir(info->argv[info->var.i]);
		if(stat(info->argv[info->var.i], &meta) == 0)
			if(S_ISDIR(meta.st_mode) == 1)
				temp_ls = store_file_name(temp_ls, info->argv[info->var.i]);
		(dir != NULL) && (closedir(dir));
		info->var.i++;
	}
	return(temp_ls);
}

//void print_recursively_stored_dir(t_ls *ls, t_info *info, char *current_dir);

void files_from_stored_dir_path(t_ls *ls, t_ls *temp_ls, t_info *info)
{
	while(temp_ls)
	{
		(info->var.new_line == true) && (ft_printf("\n"));
		(info->argc >= 2) && (ft_printf("%s:\n", temp_ls->dir_path));
		single_argument(ls, info, temp_ls->dir_path);
		info->var.new_line = true;
		temp_ls = temp_ls->next;
	}
}

int start_recursive_call(t_ls *temp_ls, t_info *info);

/*
void files_from_stored_dir_path_recurssion(t_ls *temp_ls, t_info *info)
{
//	t_ls *temp_ls_new;
//	while(temp_ls)
//	{
//		(info->var.new_line == true) && (ft_printf("\n"));
//		(info->argc >= 2) && (ft_printf("%s:\n", temp_ls->file_name));
		start_recursive_call(temp_ls, info);
//		temp_ls = temp_ls->next;
//		(info->var.new_line == true) && (ft_printf("\n"));
//		(info->argc >= 2) && (ft_printf("%s:\n", (temp_ls->file_name));
//		temp_ls_new = store_root_files(temp_ls_new, info, temp_ls->file_name);
//		start_recursive_call(temp_ls_new, info);
//		if(temp_ls_new)
//			delete_list_file_name(&temp_ls_new);
//		info->var.new_line = true;
//		temp_ls = temp_ls->next;
//	}

//	while(temp_ls_new)
//	{
//		printf("|%s|\n", temp_ls_new->file_name);
//		temp_ls_new = temp_ls_new->next;
//	}
}
*/
void process_dir_valid(t_ls *ls, t_info *info)
{
	t_ls			*temp_ls;
//	char			*current_dir_path;

	temp_ls = NULL;
//	current_dir_path = info->argv[info->var.i];
//	if(flag_status(info) == false)
	if(info->flag.uppercase_r == false)
	{
		temp_ls = store_dir_path_regular(temp_ls, info);
		merge_sort_dir(&temp_ls);
		files_from_stored_dir_path(ls, temp_ls, info);
		delete_list_dir_path(&temp_ls);
	}
	else if(info->flag.uppercase_r == true)
	{
		temp_ls = store_dir_path_recurssion(temp_ls, info);
		merge_sort(&temp_ls);
		start_recursive_call(temp_ls, info);
		delete_list_file_name(&temp_ls);
	}
/*
		while(temp_ls)
		{
			ls = store_root_files(ls, info, temp_ls->file_name);
			start_recursive_call(ls, info);
			delete_list_file_name(&ls);
			temp_ls = temp_ls->next;
		}
		delete_list_file_name(&temp_ls);
*/
//		printf("Does it come to process_dir_valid\n");
//		merge_sort_dir(&temp_ls);
/*
	else if(flag_status(info) == true)
	{
//		temp_ls = store_dir_path_without_flag(temp_ls, info);
//		merge_sort_dir(&temp_ls);
//		while(temp_ls)
//		{
			print_recursively_stored_dir(ls, info, info->argv[info->var.i]);
//			temp_ls = temp_ls->next;
//		}
//		delete_list(&temp_ls);
	}
*/
}
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
			single_argument(ls, info, temp_ls->dir_path);
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
//ft_printf("cp1\n");
	info->var.new_line = false;
	info->print_path_name = false;
//	info->no_dot_slash = false;
	info->var.i = info->var.temp_i;
	process_invalid_file(ls, info);

//ft_printf("cp2\n");
	info->var.i = info->var.temp_i;
	process_valid_file(ls, info);

//ft_printf("cp3\n");

	info->var.i = info->var.temp_i;
	process_dir_valid(ls, info);

//	if(info->flag.uppercase_r == true)
//	{
//		while()
//	}
//ft_printf("cp4\n");
//	exit(EXIT_SUCCESS);
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

/*
** Function flag status returns 1 or true if one of the flags are active.
** If there are no flags, then it returns false or 0.
*/

bool	flag_status(t_info *info)
{
	if(info->flag.l == true || info->flag.a == true || info->flag.t == true)
		return(true);
	else if(info->flag.r == true || info->flag.uppercase_r == true)
		return(true);
	return(false);
}

/*
** If a flag is not valid at any point. The program will end and by giving the
** illegal option message.
*/

void	ls_collect_flag_and_illegal_option(t_info *info, int i, int j)
{
	if(is_flag_valid(info->argv[i][j]) == true)
		ls_collect_flags(info, info->argv[i][j]);
	else if(is_flag_valid(info->argv[i][j]) == false)
		ft_exit_illegal_option(info->argv[i][j]);
}

int	set_up_environment_to_collect_flags(t_info *info, int i, int j)
{
	while(i < info->argc)
	{
		info->var.str_len = ft_strlen(info->argv[i]);
		while(j < info->var.str_len)
		{
			if(info->argv[i][0] == '-')
			{
				(j == 0) && (j = 1);
				ls_collect_flag_and_illegal_option(info, i ,j);
			}
			else if(info->argv[i][0] != '-')
				return(i);
			j++;
		}
		j = 0;
		i++;
	}
	return(i);
}

void	initialize_t_info_struct_variables(t_info *info)
{
	ft_bzero(&info->flag, sizeof(info->flag));
	info->var.temp_i = 1;
	info->var.str_len = 0;
	info->var.double_break = false;
	info->pad_size = 0;
	info->pad_nlink = 0;
	info->total_blocks = 0;
}

/*
void	print_recursively_stored_dir(t_ls *ls, t_info *info, char *current_dir)
{
	t_ls *temp_ls;

	temp_ls = NULL;
	single_argument(ls, info, current_dir);
	write(1, "\n", 1);
//	temp_ls = store_dir_recursively(temp_ls, info, current_dir);	
	store_dir_recursively(temp_ls, info, current_dir);
	merge_sort_dir(&temp_ls);
	get_files_from_stored_dir_path(ls, temp_ls, info);
	if(temp_ls != NULL)
		delete_list(&temp_ls);
}
*/

t_ls *store_root_files(t_ls *ls, t_info *info, char *dir_path_str)
{
	struct dirent	*data;
	DIR				*dir;

	dir = opendir(dir_path_str);
	if(dir == NULL)
		return(ls);
	while((data = readdir(dir)) != NULL)
	{
		if(info->flag.a == true)
			ls = store_file_name(ls, data->d_name);
		else if(info->flag.a == false && data->d_name[0] != '.')
//		if(ft_strcmp(data->d_name, ".") && ft_strcmp(data->d_name, ".."))
			ls = store_file_name(ls, data->d_name);
	}
	if(dir != NULL)
		closedir(dir);
	merge_sort(&ls);
	return(ls);
}

void	ls_start_parsing(t_ls *ls, t_info *info)
{
	t_ls			*temp_ls;
	int				i;
	int				j;
	char			current;

	i = 1;
	j = 1;
	current = info->argv[i][0];
	temp_ls = NULL;
//	ls->slash_index = 0;
//	ft_printf("ls->slash_index|%d|\n", ls->size_padding);
	initialize_t_info_struct_variables(info);
	if((current != '-') || (current == '-' && info->argv[i][1] == '\0'))
		handle_improper_usage_of_dash(ls, info);
	else if(info->argv[i][0] == '-' && info->argv[i][1] != '\0')
	{
		i = set_up_environment_to_collect_flags(info, i, j);
//		ft_printf("flag_status:|%d|\n", flag_status(info));
//		ft_printf("|%d|\n", i);
//		ft_printf("|%d|\n", info->argc);
		if(i == info->argc && (flag_status(info) == false))
		{
//			ft_printf("|%d|\n", info->flag.a);
			single_argument(ls, info, ".");
		}
//		else if(i == 2 && info->argc == 2 && info->flag.upp)
/*
// Gives directory names recursively // placing this inside process_dir_valid
		else if(i == info->argc && info->flag.uppercase_r == true)
		{
//			ls = store_dir_recursively(".", ls, info);
			ls = store_dir_recursively(ls, info, ".");
			merge_sort(&ls);
			print_file_name(ls);
		}
*/
/*
	while(ls)
	{
		(info->var.new_line == true) && (ft_printf("\n"));
		(info->argc > 2) && (ft_printf("%s:\n", ls->dir_path));
		if(info->flag.uppercase_r == false)
			single_argument(ls, info, ls->dir_path);
		info->var.new_line = true;
		ls = ls->next;
	}
	delete_list(&ls);
*/
//		printf("i:|%d|\n", i);
//		printf("info->argc:|%d|\n", info->argc);
		else if(i == 2 && info->argc == 2 && flag_status(info) == true)
		{
			if(info->flag.a == true && info->flag.uppercase_r == false)
				single_argument(ls, info, ".");
			else if(info->flag.l == true)
				single_argument(ls, info, ".");

			else if(i == 2 && info->argc == 2 && info->flag.uppercase_r == true)
				{
//					print_recursively_stored_dir(ls, info, ".");
//					temp_ls = store_root_files(temp_ls, info, ".");
//					print_file_name(temp_ls);
//					store_dir_recursively(temp_ls, info, ".");
					temp_ls = store_root_files(temp_ls, info, ".");
//					temp_ls = store_file_name(temp_ls, ".");
//					print_file_name(temp_ls);
					info->skip_print = false;
					start_recursive_call(temp_ls, info);
					delete_list_file_name(&temp_ls);
//					delete_list(&temp_ls);
/*
					if(temp_ls == NULL)
					ft_printf("|Successfully deleted all nodes|\n");
					if(temp_ls != NULL)
					ft_printf("Left over\n");
*/
				}
//			ft_printf(BRED"\n------Does it come here---------\n");
			return;
		}

//		ft_printf("i:|%i|\n", i);
//		ft_printf("info->argc:|%i|\n", info->argc);

// Put it back on if something breaks
	if	(i < info->argc)
		{
//			ft_printf(BGREEN"\n----Comes inside this if statement---\n"NC);
			info->skip_print = true;
			info->no_dot_slash = true;
			info->var.temp_i = i;
			process_dir(ls, info);
		}

	}

/*	
		while(i < info->argc)
		{
			printf("Does it come here?\n");
			info->var.temp_i = i;
			process_dir(ls, info);
			i++;
		}
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


/*
** Function print_file_name will print contents, files and folders, of the
** current directory.
*/

void print_file_name_notes(t_ls *ls)
{
//	int i;
//	char *str;


// Good to run this to see data in raw form

/*
	while(ls)
	{
		str = ls->file_name;
		ft_printf("%s\n", str);
		ls = ls->next;
	}
*/

/*
 Deprecated because len is calculated outside the while loop
	while(ls)
	{
		str = ls->file_name + find_last_slash(ls->file_name);
		ft_printf("%s\n", str);
		ls = ls->next;
	}
*/
/*
// skips slash
	int file_path_len;
	file_path_len = 0;
	if(ls)
		file_path_len = find_last_slash(ls->file_name);

	while(ls)
	{
		str = ls->file_name + file_path_len;
		ft_printf("%s\n", str);
		ls = ls->next;
	}
*/
//	int slash_index;
//	slash_index = ls->slash_index;
	while(ls)
	{
//		str = ls->file_name + ls->slash_index;
//		ft_printf("%s\n", str);
		ft_printf("%s\n", ls->file_name + ls->slash_index);
		ls = ls->next;
	}
//	delete_list(&ls);
}
/*
// Original without stat
void print_file_name(t_ls *ls)
{
	char *str;

	while(ls)
	{
		str = ls->file_name + ls->slash_index;
		ft_printf("%s\n", str);
		ls = ls->next;
	}
}
*/

/*
** Returns a substring
*/
char *ft_substring(char *dest, char *source, int start)
{
    int i;

    i = 0;
    if(source)
        while(source[start])
            dest[i++] = source[start++];
    dest[i] = '\0';
    return(dest);
}

char *ft_substr_start_end(char *dest, char *source, int start, int end)
{
	int i;

	i = 0;

	if(source)
		while(end && source[start])
		{
			dest[i++] = source[start++];
			end--;
		}
	dest[i] = '\0';
	return(dest);
}


void get_total_for_long_listing(t_ls *ls)
{
	struct stat meta;
	int total;

	total = 0;
	while(ls)
	{
		stat(ls->file_name, &meta);
		total = total + meta.st_blocks;
//		ft_printf(BCYAN"%d "NC, meta.st_blocks); // These need to be removed
//		ft_printf(BCYAN"%s \n"NC, ls->file_name);  // These need to be removed
		ls = ls->next;
	}
	ft_printf("total %d\n", total);
}

char permission_file_type(int file_mode)
{
	char type;
	
	if(S_ISDIR(file_mode))
		type = 'd';
	else if(S_ISCHR(file_mode))
		type = 'c';
	else if(S_ISBLK(file_mode))
		type = 'b';
	else if(S_ISFIFO(file_mode))
		type = 'p';
	else if(S_ISLNK(file_mode))
		type = 'l';
	else if(S_ISSOCK(file_mode))
		type = 's';
	else
		type = '-';
	return(type);

}

//char extended_attributes(struct stat meta, char *file_name)
char 	extended_attributes(char *file_name)
{
	ssize_t xattr;
	char character;

	xattr = 0;
	xattr = listxattr(file_name, NULL, 0, XATTR_NOFOLLOW);
//	(xattr < 0) && (xattr = 0);
	if(xattr > 0)
		character = '@';
	else
		character = ' ';
	return(character);
}

void permission_column(struct stat meta, char *file_name)
{
	int i;
	char extended_character;
	char permission[12];

	i = 0;
//	extended_character = extended_attributes(meta, file_name);
	extended_character = extended_attributes(file_name);
	permission[i++] = permission_file_type(meta.st_mode);
	permission[i++] = (meta.st_mode & S_IRUSR) ? 'r' : '-';
	permission[i++] = (meta.st_mode & S_IWUSR) ? 'w' : '-';
	permission[i++] = (meta.st_mode & S_IXUSR) ? 'x' : '-';
	permission[i++] = (meta.st_mode & S_IRGRP) ? 'r' : '-';
	permission[i++] = (meta.st_mode & S_IWGRP) ? 'w' : '-';
	permission[i++] = (meta.st_mode & S_IXGRP) ? 'x' : '-';
	permission[i++] = (meta.st_mode & S_IROTH) ? 'r' : '-';
	permission[i++] = (meta.st_mode & S_IWOTH) ? 'w' : '-';
	permission[i++] = (meta.st_mode & S_IXOTH) ? 'x' : '-';
	permission[i++] = extended_character;
	permission[i] = '\0';
	ft_printf("%s ", permission);
}

void link_column(struct stat meta, int pad_nlink)
{
//	int link;

//	link = meta.st_nlink;
/*
	if(link <= 9)
		ft_printf(" %d ", link);
	else if(link >= 10)
		ft_printf("%d ", link);
*/
	ft_printf("%*d ", pad_nlink, meta.st_nlink);
}

void owner_and_group_column(struct stat meta)
{
//	char *owner_name;
//	char *group_name;

//	owner_name = getpwuid(meta.st_uid)->pw_name;
//	group_name = getgrgid(meta.st_gid)->gr_name;



//	ft_printf(BGREEN"---Enters owner_and_group_column---\n"NC);
	
	if(getpwuid(meta.st_uid)->pw_name)
		ft_printf("%s  ", getpwuid(meta.st_uid)->pw_name);
//	ft_printf(BGREEN"---Got user name in owner_and_group_column---\n"NC);
	if(getgrgid(meta.st_gid)->gr_name)
		ft_printf("%s  ", getgrgid(meta.st_gid)->gr_name);
//	ft_printf(BGREEN"---Finished with owner_and_group_column---\n"NC);



//	printf("%s  ", owner_name);
//	printf("%s  ", group_name);
}


void size_column(struct stat meta, int pad_size)
{
	ft_printf("%*d ", pad_size, meta.st_size);
}

/*
** skip_day_and_space = 4 because time string's first three characters are to
** represent a day + 1 for space.
** To calulate time in years, take time in seconds and divide it by 86,400 sec
** per day and divide it by 365 days, so to convert 1,572,511,743 seconds into
** years, we would do:
** (1572511743 seconds / 86400 seconds per day) / 365 days = 49.86 years.
*/


void month_date_time_column(struct stat meta)
{
	struct timespec last_modified;
	time_t seconds_since_epoch;
	char *month_date;
	char *time_or_year;
	char *time_str;
	
	last_modified = meta.st_mtimespec;
	seconds_since_epoch = time(&seconds_since_epoch);
	time_str = ctime(&meta.st_mtimespec.tv_sec);
	month_date = malloc(sizeof(char) * (8));
	time_or_year = malloc(sizeof(char) * (8));
	if(month_date == NULL || time_or_year == NULL)
		return;
	month_date[0] = 0;
	time_or_year[0] = 0;
// Just to see what dates are printed below
//	ft_printf(BBLUE"\natime    |%s|\n"NC, ctime(&meta.st_atimespec.tv_sec));
//	ft_printf(BBLUE"birthtime|%s|\n"NC, ctime(&meta.st_birthtimespec.tv_sec));
//	ft_printf(BBLUE"ctime    |%s|\n"NC, ctime(&meta.st_ctimespec.tv_sec));
//	ft_printf(BBLUE"mtime    |%s|\n"NC, ctime(&meta.st_mtimespec.tv_sec));


// Just to see what dates are printed above

	ft_printf("%s ", ft_substr_start_end(month_date, time_str, 4, 6));	
	if((seconds_since_epoch - last_modified.tv_sec) < SIX_MONTH)
		ft_printf("%s ", ft_substr_start_end(time_or_year, time_str, 11, 5));
	else if((seconds_since_epoch - last_modified.tv_sec) >= SIX_MONTH)
		ft_printf("%5s ", ft_substr_start_end(time_or_year, time_str, 20, 4));
	free(month_date);
	free(time_or_year);
}


/*
// Works trying to improve dates to capture year for files that are older than
// 6 months
void month_date_time_column(struct stat meta)
{
	int skip_day_and_space;
	char *month_date_time;
	
	month_date_time = malloc(sizeof(char) * (32));
	if(month_date_time == NULL)
		return;
	skip_day_and_space = 4;
	ft_strncpy (month_date_time, ctime(&meta.st_mtimespec.tv_sec), 16);

// Below can be deleted later - For testing puporses to get time


	ft_printf(BBLUE"\natime    |%ld|\n"NC, &meta.st_atimespec.tv_sec);
	ft_printf(BBLUE"\nbirthtime|%ld|\n"NC, &meta.st_birthtimespec.tv_sec);
	ft_printf(BBLUE"\nctime    |%ld|\n"NC, &meta.st_ctimespec.tv_sec);
	ft_printf(BBLUE"\nmtime    |%ld|\n"NC, &meta.st_mtimespec.tv_sec);

//	ft_printf(BBLUE"\natime    |%ld|\n"NC, ctime(&meta.st_atimespec.tv_sec));
//	ft_printf(BBLUE"\nbirthtime|%ld|\n"NC, ctime(&meta.st_birthtimespec.tv_sec));
//	ft_printf(BBLUE"\nctime    |%ld|\n"NC, ctime(&meta.st_ctimespec.tv_sec));
//	ft_printf(BBLUE"\nmtime    |%ld|\n"NC, ctime(&meta.st_mtimespec.tv_sec));
	
// Above can be deleted later - For testing purposes to get time
	
	
	ft_printf("%s ", month_date_time + skip_day_and_space);	
//	ft_printf("|%s |", month_date_time + skip_day_and_space);

	free(month_date_time);
}
*/


//void long_file_listing(struct stat meta, char *file_name, int link_padding,
//		int size_padding)
void	long_file_listing(struct stat meta, char *file_name, t_info *info)
{
//	int pad_size;
//	int pad_nlink;

//	pad_size = info->pad_size;

	permission_column(meta, file_name);
	link_column(meta, info->pad_nlink);
//	link_column(meta, link_padding);
	owner_and_group_column(meta);
//	size_column(meta, size_padding);
	size_column(meta, info->pad_size);
	month_date_time_column(meta);

}

int get_link_padding(t_ls *ls)
{
	struct stat meta;
	int padding;
	int numlen;

	padding = 0;
	numlen = 0;
	while (ls)
	{
		lstat(ls->file_name, &meta);
		numlen = ft_numlen(meta.st_nlink, FT_DECIMAL);
		(numlen > padding) && (padding = numlen);
		ls = ls->next;
	}
	return(padding);
}

int get_size_padding(t_ls *ls)
{
	struct stat meta;
	int padding;
	int numlen;

	padding = 0;
	numlen = 0;
	while(ls)
	{
		lstat(ls->file_name, &meta);
		numlen = ft_numlen(meta.st_size, FT_DECIMAL);
		(numlen > padding) && (padding = numlen);
		ls = ls->next;
	}
	return(padding);
}

int find_max(int num1, int num2)
{
	if(num1 > num2)
		return(num1);
	return(num2);
}

void padding_and_blocks_total(t_ls *ls, int *pad_nlink, int *pad_size)
{
	struct stat meta;
	int numlen_nlink;
	int numlen_size;
	int total;

	numlen_nlink = 0;
	numlen_size = 0;
	total = 0;
	while(ls)
	{
		stat(ls->file_name, &meta);
		total = total + meta.st_blocks;
//		nlink_numlen = ft_numlen(meta.st_nlink, FT_DECIMAL);
//		(nlink_numlen > nlink_pad) && (nlink_pad = nlink_numlen);
		*pad_nlink = find_max(ft_numlen(meta.st_nlink, FT_DECIMAL), *pad_nlink);
		*pad_size = find_max(ft_numlen(meta.st_size, FT_DECIMAL), *pad_size);
//		size_numlen = ft_numlen(meta.st_size, FT_DECIMAL);
//		(size_numlen > size_pad) && (size_pad = size_numlen);

		ls = ls->next;
	}
	ft_printf("total %d\n", total);
}

/*
** stat(2) is an incredibly powerful functions that provides information about
** a filepath. However, it is not good at determining a symbolike link.
** 
** In order to know if a file is a symoblik link, lstat(2) is used instead.
** man 2 stat and man 2 lstat has some really good information and it also
** mentions members of stat struct family and time struct.
*/

void file_is_link(char *link_str, char *ls_file_name, char *str)
{
	ft_bzero(link_str, _POSIX_PATH_MAX);
	readlink(ls_file_name, link_str, _POSIX_PATH_MAX);
	ft_printf("%s -> %s\n", str, link_str);
}

void print_file_name(t_ls *ls, t_info *info)
{
//	t_info		info;
	struct stat meta;
	char *str;
	char *link_str;
//	int link_padding;
//	int size_padding;
	
//	info.pad_size = 0;
//	info.pad_nlink = 0;
//	info.total_blocks = 0;
//	link_padding = 0;
//	size_padding = 0;
//	ft_printf("slash_index: |%d|\n", ls->slash_index);
	str = malloc(sizeof(char) * (_POSIX_PATH_MAX));
	if(info->flag.l == true)
	{
		link_str = malloc(sizeof(char) * (_POSIX_PATH_MAX));
//		padding_and_blocks_total(ls, &link_padding, &size_padding);
		padding_and_blocks_total(ls, &info->pad_nlink, &info->pad_size);
	}
//	ft_printf("nlink_padding:|%d|\n", link_padding);
//	ft_printf("size_padding:|%d|\n", size_padding);

//	get_total_for_long_listing(ls);
//	link_padding = get_link_padding(ls);
//	size_padding = get_size_padding(ls);
	while(ls)
	{	
//		ft_printf(BGREEN"\nls->file_name|%s|\n"NC, ls->file_name);
//		ft_printf(BBLUE"------------------1------------------------\n"NC);
//		ft_printf("sizeof:|%ld|\n", sizeof(str));
		str[0] = 0;
//		ft_printf(BBLUE"-------------------2------------------------\n"NC);
//		link_str[0] = 0;
		if(ls->slash_index >= 0)
			ft_substring(str, ls->file_name, ls->slash_index);
		else if(ls->slash_index < 0)
			ft_strcpy(str, ls->file_name);
		if(info->flag.l == true)
		{
			lstat(ls->file_name, &meta);
//			long_file_listing(meta, ls->file_name, link_padding, size_padding);
//			long_file_listing(meta, ls->file_name, info->pad_nlink, info->pad_size);
			long_file_listing(meta, ls->file_name, info);
		}

//		lstat(ls->file_name, &ls->stat);
//		long_file_listing(ls->stat, ls->file_name, link_padding, size_padding);



//		ft_printf("------|%s|---\n", ls->file_name);

/*
		ft_printf("|%d|", meta.st_size); 5th column
		ft_printf("|%d|", meta.st_blocks); Use this to get total
		ft_printf("|%s|", getpwuid(meta.st_uid)->pw_name); Owner
		ft_printf("|%s|", getgrgid(meta.st_gid)->gr_name); Group_id
		ft_printf("|%s|", ctime(&meta.st_ctimespec.tv_sec)); // Date time
		ft_printf((S_ISDIR(meta.st_mode)) ? "d": "-");
		permission[i++] = (S_ISDIR(meta.st_mode)) ? 'd' : '-';
		mode = meta.st_mode;

		permission[i++] = permission_file_type(meta.st_mode);
		permission[i++] = (meta.st_mode & S_IRUSR) ? 'r' : '-';
		permission[i++] = (meta.st_mode & S_IWUSR) ? 'w' : '-';
		permission[i++] = (meta.st_mode & S_IXUSR) ? 'x' : '-';
		permission[i++] = (meta.st_mode & S_IRGRP) ? 'r' : '-';
		permission[i++] = (meta.st_mode & S_IWGRP) ? 'w' : '-';
		permission[i++] = (meta.st_mode & S_IXGRP) ? 'x' : '-';
		permission[i++] = (meta.st_mode & S_IROTH) ? 'r' : '-';
		permission[i++] = (meta.st_mode & S_IWOTH) ? 'w' : '-';
		permission[i++] = (meta.st_mode & S_IXOTH) ? 'x' : '-';
		permission[i] = '\0';
		ft_printf("%s  ", permission);
*/
		if(S_ISLNK(meta.st_mode) && info->flag.l == true)
		{
			file_is_link(link_str, ls->file_name, str);
//			ft_bzero(link_str, _POSIX_PATH_MAX);
//			readlink(ls->file_name, link_str, _POSIX_PATH_MAX);
//			ft_printf("%s -> %s\n", str, link_str);
		}
		else
				ft_printf("%s\n", str);
		ls = ls->next;
	}

	free(str);
//	ft_printf(BWHITE"\ninfo->flag.a|%d|\n", info->flag.a);
	if(info->flag.l == true)
		free(link_str);
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
** Might end up creating one universal merge sort with multiple features to sort
** with:
** 1. "lexical".
** 2. "reverse".
** 3. "time".
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
//	if(ft_strcmp(a->file_name, b->file_name) < 0)
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

// Works trying to add stat to this
void	single_argument(t_ls *ls, t_info *info, char *dir_path_str)
{
	struct dirent	*data;
	DIR				*dir;
	t_ls 			*new_ls;
//	int				count;

	new_ls = NULL;
	dir = opendir(dir_path_str);
	if(dir == NULL)
		ft_permission_denied(dir_path_str);
	else if(dir != NULL)
	{
		while((data = readdir(dir)) != NULL)
		{
			if(info->flag.a == true)
				ls = store_file_name_with_index(ls, data->d_name, 0);
			else if(info->flag.a == false && data->d_name[0] != '.')
				ls = store_file_name_with_index(ls, data->d_name, 0);



// Works, changing it to use store_file_name_index
/*
			if(info->flag.a == true)
				ls = store_file_name(ls, data->d_name);
			else if(info->flag.a == false && data->d_name[0] != '.')
				ls = store_file_name(ls, data->d_name);
*/
		}
	}

	if(dir != NULL)
	{
		closedir(dir);
		merge_sort(&ls);
//		if(info->flag.l == true && ls != NULL)
		if(ls != NULL)
			new_ls = append_slash(new_ls, ls, dir_path_str);
		delete_list_file_name(&ls);
		print_file_name(new_ls, info);
		delete_list_file_name(&new_ls);

//		print_file_name(ls, info); // Commenting this to append slash for -l flag
//		delete_list(&ls);
//		if(ls && ls->file_name)
//			delete_list(&ls);
	}
//	delete_list(&ls);
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
	{
		closedir(dir);
		merge_sort(&ls);
//	count = get_count(ls); // Will be used later when alligning columns
		print_file_name(ls, info);
		multiple_argument(ls, info, dir_path_str);
//	process_dir_valid(ls, info); //
		delete_list(&ls);
	}

}

/*
** **ft_double_strdup takes the number of arguments and the a 2D array to create
** a 2 dimensional array.
** This function is used to obtain a 2d string that will be stored in the struct
** so fewer parameters are passed around
*/

void free_double_array(char **double_array)
{
	int i;

	i = 0;

	if(double_array)
		while(double_array[i])
		{
			free(double_array[i]);
			i++;
		}
	free(double_array);
//	double_array = NULL;
}

char **ft_double_strdup(int argc, char **source)
{
	char **dest;
	int i;

	i = 0;
	ft_printf("dest:|%ld|\n", sizeof(dest));
	dest = malloc(sizeof (char *) * (argc + 1));
	ft_printf("dest after malloc:|%ld|\n", sizeof(dest));
	if (dest == NULL || source == NULL)
		return (NULL);
	ft_bzero(dest, argc +1);
	while (i < argc)
	{
		ft_printf("while_loop sizeof(dest[i])|%ld|\n", sizeof(dest[i]));
		ft_printf("while_loop sizeof(dest)   |%ld|\n", sizeof(dest));
		dest[i] = ft_strdup(source[i]);
		i++;
	}
	dest[i] = NULL;
	ft_printf("i:|%d|\n", i);
	ft_printf("sizeof(dest) right before return|%ld|\n", sizeof(dest));
	return (dest);
}

/*
void	set_info_flag_to_zero(t_info *info)
{
//	ft_bzero(&info->flag, sizeof(info->flag));
	ft_bzero(info, sizeof(info));
}
*/
int main(int argc, char *argv[])
{
	t_ls	*ls;
	t_info	info;
	

//	ft_printf("sizeof info.argv:|%lu|\n", info.argv);
	ls = NULL;
//	ls = malloc(sizeof(t_ls));

//	ft_printf("|%d|\n", ls->slash_index);
//	set_info_flag_to_zero(&info);
	ft_bzero(&info, sizeof(&info));
	info.argc = argc;
	info.argv = argv;

//	ft_printf(BGREEN"%d\n"NC, info.pad_size);
//	ft_printf(BGREEN"%d\n"NC, info.total_blocks);
//	ft_printf(BGREEN"%d\n"NC, info.pad_nlink);
//	info.argv = ft_double_strdup(argc, argv);
//	ft_printf("sizeof info.argc:|%lu|\n", info.argc);
//	ft_printf("sizeof info.argv:|%lu|\n", info.argv);
	
//	ft_printf("sizeof info.argv|%ld|\n", info.argv);
//	ft_printf("sizeof argv|%ld|\n", argv);
//	ls->slash_index = 0;
//	info.pad_size = 0;
//	info.pad_nlink = 0;
//	info.total_blocks = 0;

//	ft_printf("|%d|\n", ls->slash_index);
/*
// To test stored string
	int i = 0;
	while(i < argc)
		printf("|%s|\n", info->argv[i++]);
	return(0);
*/
//	return (-1);
	if(argc == 1)
	{
//		printf("1\n");
		single_argument(ls, &info, ".");

	}
	else if(argc > 1)
	{
//		printf("2\n");
		ls_start_parsing(ls, &info);
	}
//	if(&ls)
	if(ls)
		delete_list_file_name(&ls);
//		free(ls);	
//	free_double_array(info.argv);
//	while(1);

	return(0);

}
