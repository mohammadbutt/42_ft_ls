/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:59:19 by mbutt             #+#    #+#             */
/*   Updated: 2019/11/06 18:55:12 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** If a flag is not valid at any point. The program will end and by giving the
** illegal option message.
*/

void ft_exit_illegal_option(char c)
{
	ft_printf("ft_ls: illegal option -- %c\n", c);
	ft_printf("usage: ft_ls [-latrRG] [file ...]\n");
	exit(EXIT_SUCCESS);
}


void	ls_collect_flag_and_illegal_option(t_info *info, int i, int j)
{
	if(is_flag_valid(info->argv[i][j]) == true)
		ls_collect_flags(info, info->argv[i][j]);
	else if(is_flag_valid(info->argv[i][j]) == false)
		ft_exit_illegal_option(info->argv[i][j]);
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


void ft_permission_denied(char *str)
{
	ft_printf("ft_ls: ");
	perror(str);
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
	if(ft_strcmp(a->file_name, b->file_name) <= 0)
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
//		merge_sort(&ls, info); // Can create one sepeate merge_sort for invalid
		merge_sort_invalid_file_name(&ls);
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
		merge_sort(&ls, info);
		print_file_name(ls, info);
//		delete_list(&ls);
		delete_list_file_name(&ls);
		info->var.new_line = true;
		info->print_path_name = true;
		info->no_dot_slash = true;
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
** Return Values of (stat(full_path, &meta):
** 0 for both valid file and directory.
**
** Return Values of (S_ISDIR(meta.st_mode):
** 1 means it is a directory.
** 0 means it is a file.
** -1 mean it is an invalid file.
** _POSIX_PATH_MAX can store upto 256 characters
*/

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

t_ls	*append_slash(t_ls *new_ls, t_ls *temp_ls, char *path)
{
	char *full_path;
	int i;
	int j;
	int reset_i;
	char *ref_str;
	
	full_path = malloc(sizeof(char) * (_POSIX_PATH_MAX));
	i = 0;
	j = 0;
	reset_i = 0;
	full_path[0] = 0;
	if(path)
	{
		while(path[j])
			full_path[i++] = path[j++];
		(full_path[i - 1] != '/') && (full_path[i++] = '/');
		full_path[i] = '\0';
	}
	reset_i = i;
	while(temp_ls && temp_ls->file_name)
	{
		ref_str = temp_ls->file_name;
		i = reset_i;
		j = 0;

		if(ft_strcmp(ref_str, ".") == 0 || ft_strcmp(ref_str, "..") == 0)
		{
			new_ls = store_file_name_with_index(new_ls, ref_str, 0);
		}
		else
		{
			while(ref_str[j])
				full_path[i++] = ref_str[j++];
			full_path[i] = '\0';
			new_ls = store_file_name_with_index(new_ls, full_path, reset_i);
		}
		temp_ls = temp_ls->next;
	}
	free(full_path);
	return(new_ls);
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
//	ft_printf(BGREEN"|%s|\n"NC, path);

//	if(ft_strcmp(path, ".") != 0 && ft_strcmp(path, "..") != 0)
//		return(new_ls);
	if((dir = opendir(path)) == NULL)
	{
		(info->no_dot_slash == false) && (ft_printf(BRED"\n./%s\n"NC, path));
		(info->no_dot_slash == true) && (ft_printf(BRED"\n%s\n"NC, path));
//		ft_permission_denied(path);
		ft_permission_denied(path + find_last_slash(path));
		return(NULL);
	}
	else if(info->skip_print == false )//|| info->print_path_name == true)
	{
			(info->no_dot_slash == false) && (ft_printf("\n./%s:\n", path));
			(info->no_dot_slash == true) && (ft_printf("\n%s:\n", path));
	}
	else if(info->print_path_name == true)
		ft_printf("%s:\n", path);
//	else if (info->print)

//	int len;
//	len = ft_strlen(path) - 1;
/*
// Works. Refactoring and improving the if statment slightly
	while((dr = readdir(dir)) != NULL)
	{
		if(info->flag.a == true)
			temp_ls = store_file_name(temp_ls, dr->d_name);
		else if(info->flag.a == false && dr->d_name[0] != '.')
		{
			temp_ls = store_file_name(temp_ls, dr->d_name);
		}
	}
*/

	if(info->flag.a == true)
	{
		while((dr = readdir(dir)) != NULL)
		{
//			ft_printf(BCYAN"|%s|\n", dr->d_name);
//			if(ft_strcmp(dr->d_name, ".") != 0 && ft_strcmp(dr->d_name, "..") != 0)
//			{
//				ft_printf(BCYAN"|%s|\n", dr->d_name);
				temp_ls = store_file_name(temp_ls, dr->d_name);
//			}
		}
	}
	else if(info->flag.a == false)
	{
		while((dr = readdir(dir)) != NULL)
			if(dr->d_name[0] != '.')
			{
//				ft_printf(BCYAN"|%s|\n"NC, dr->d_name);
				temp_ls = store_file_name(temp_ls, dr->d_name);
			}
	}
//	merge_sort(&temp_ls, info);
//	// Commenting this because if a file is going to
//	be sorted by time then it needs to have a full path with slash appended to
//	it. Just having the file name does not give meta information.

	(dir != NULL) && (closedir(dir));
	(temp_ls != NULL) && (new_ls = append_slash(new_ls, temp_ls, path));	
	delete_list_file_name(&temp_ls);
	merge_sort(&new_ls, info);

	return(new_ls);
}

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
	char	*ref_str;

	inner_dir = NULL;	
	if(temp_ls != NULL && temp_ls->file_name && info->skip_print == false)
	{
//		ft_printf("Comes here\n");
		print_file_name(temp_ls, info);
	}


	while(temp_ls != NULL)
	{
		ref_str = temp_ls->file_name;
		if(ft_strcmp(ref_str, ".") != 0 && ft_strcmp(ref_str, "..") != 0)
		{
			if(stat(ref_str, &meta) == 0 && S_ISDIR(meta.st_mode))
			{
//				info->skip_print = false;
				if(info->flag.a == false && ref_str[0] != '.')
					inner_dir = store_file_recursively(info, ref_str);
				else if(info->flag.a == true)
					inner_dir = store_file_recursively(info, ref_str);
				info->skip_print = false;
				if(inner_dir != NULL)
				{
					start_recursive_call(inner_dir, info);
					delete_list_file_name(&inner_dir);
				}
			}
		}
		temp_ls = temp_ls->next;
	}
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
				temp_ls = store_file_name(temp_ls, info->argv[info->var.i]);
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

void files_from_stored_dir_path(t_ls *ls, t_ls *temp_ls, t_info *info)
{
	int number_of_nodes;

	number_of_nodes = get_count(temp_ls);
	while(temp_ls)
	{
		(info->var.new_line == true) && (write(1, "\n", 1));
//		(info->argc >= 2) && (ft_printf("%s:\n", temp_ls->file_name));
//		(get_count(temp_ls) == 2)
		(number_of_nodes == 2) && (ft_printf("%s:\n", temp_ls->file_name));
		single_argument(ls, info, temp_ls->file_name);
		info->var.new_line = true;
		temp_ls = temp_ls->next;
	}
}

int start_recursive_call(t_ls *temp_ls, t_info *info);

void process_dir_valid(t_ls *ls, t_info *info)
{
	t_ls			*temp_ls_dir;

//	char			*current_dir_path;

	temp_ls_dir = NULL;
//	current_dir_path = info->argv[info->var.i];
//	if(flag_status(info) == false)
	if(info->flag.uppercase_r == false)
	{
		temp_ls_dir = store_dir_path_regular(temp_ls_dir, info);
		merge_sort(&temp_ls_dir, info);
//		merge_sort_dir(&temp_ls);
		files_from_stored_dir_path(ls, temp_ls_dir, info);
		delete_list_file_name(&temp_ls_dir);
//		delete_list_dir_path(&temp_ls);
	}
	else if(info->flag.uppercase_r == true)
	{
//		ft_printf(BGREEN"Comes inside this"NC);
		info->var.new_line = false;
		temp_ls_dir = store_dir_path_recurssion(temp_ls_dir, info);
		merge_sort(&temp_ls_dir, info);
		
		if (get_count(temp_ls_dir) == 2)
			info->print_path_name = true;
		else
			info->print_path_name = false;
//		ft_printf("|%d|\n", info->print_path_name);
//		ft_printf("|%d|\n", info->skip_print);
		start_recursive_call(temp_ls_dir, info);
		delete_list_file_name(&temp_ls_dir);
	}
}


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

t_ls *store_root_files(t_ls *ls, t_info *info, char *dir_path_str)
{
	struct dirent	*data;
	DIR				*dir;

	dir = opendir(dir_path_str);
	if(dir == NULL)
		return(ls);
	if(info->flag.a == true)
		while((data = readdir(dir)) != NULL)
			ls = store_file_name(ls, data->d_name);
	else if(info->flag.a == false)
		while((data = readdir(dir)) != NULL)
			if(data->d_name[0] != '.')
				ls = store_file_name(ls, data->d_name);
	if(dir != NULL)
		closedir(dir);
	merge_sort(&ls, info);
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
		else if(i == 2 && info->argc == 2 && flag_status(info) == true)
		{
			if(info->flag.uppercase_r == false)
				single_argument(ls, info, ".");
			else if(info->flag.uppercase_r == true)
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
//			ft_printf(BGREEN"----Comes inside this if statement---"NC);
			info->skip_print = true;
			info->no_dot_slash = true;
			info->var.temp_i = i;
			process_dir(ls, info);
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

	ft_printf("%s ", ft_substr_start_end(month_date, time_str, 4, 6));	
	if((seconds_since_epoch - last_modified.tv_sec) < SIX_MONTH)
		ft_printf("%s ", ft_substr_start_end(time_or_year, time_str, 11, 5));
	else if((seconds_since_epoch - last_modified.tv_sec) >= SIX_MONTH)
		ft_printf("%5s ", ft_substr_start_end(time_or_year, time_str, 20, 4));
	free(month_date);
	free(time_or_year);
}

void	long_file_listing(struct stat meta, char *file_name, t_info *info)
{
	permission_column(meta, file_name);
	link_column(meta, info->pad_nlink);
	owner_and_group_column(meta);
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
//		ft_printf(BGREEN"%s\n"NC, ls->file_name);
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
** a filepath. However, it is not good at determining a symbolik link.
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
	
	info->pad_size = 0;
	info->pad_nlink = 0;
//	info.total_blocks = 0;
//	link_padding = 0;
//	size_padding = 0;
//	ft_printf("slash_index: |%d|\n", ls->slash_index);
	str = malloc(sizeof(char) * (_POSIX_PATH_MAX));
	if(str == NULL)
		return;
	if(info->flag.l == true)
	{
		link_str = malloc(sizeof(char) * (_POSIX_PATH_MAX));
		padding_and_blocks_total(ls, &info->pad_nlink, &info->pad_size);
	}

//	get_total_for_long_listing(ls);
//	link_padding = get_link_padding(ls);
//	size_padding = get_size_padding(ls);
	while(ls)
	{

		lstat(ls->file_name, &meta);
//		ft_printf(BGREEN"\nls->file_name|%s|\n"NC, ls->file_name);
//		ft_printf(BBLUE"------------------1------------------------\n"NC);
//		ft_printf("sizeof:|%ld|\n", sizeof(str));
		str[0] = 0;
//		ft_printf(BBLUE"-------------------2------------------------\n"NC);
//		link_str[0] = 0;
		if(ls->slash_index >= 0)
			ft_substring(str, ls->file_name, ls->slash_index);
		else if(ls->slash_index <= 0)
			ft_strcpy(str, ls->file_name);
		if(info->flag.l == true)
		{
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
		else if(info->flag.uppercase_g == true)
		{
			if(S_ISDIR(meta.st_mode))
			{
				ft_printf(BLUE"%s\n"NC, str);
			}
			else if(meta.st_mode & S_IXUSR)
				ft_printf(RED"%s\n"NC, str);
			else
				ft_printf("%s\n", str);
		}
		else
		{
			ft_printf("%s\n", str);
		}
		ls = ls->next;
	}

	free(str);
//	ft_printf(BWHITE"\ninfo->flag.a|%d|\n", info->flag.a);
	if(info->flag.l == true)
		free(link_str);
}

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

t_ls *sorted_merge_reverse(t_ls *a, t_ls *b)
{
	t_ls *result;

	result = NULL;
	if(a == NULL)
		return(b);
	else if(b == NULL)
		return(a);
	if(ft_strcmp(b->file_name, a->file_name) > 0)
	{
		result = b;
		result->next = sorted_merge_reverse(a, b->next);
	}
	else
	{
		result = a;
		result->next = sorted_merge_reverse(a->next, b);
	}
	return(result);
}

t_ls *sorted_merge_time(t_ls *a, t_ls *b);


t_ls *sorted_merge_time_nano_second(t_ls *a, t_ls *b)
{
	t_ls *result;
	struct stat meta1;
	struct stat meta2;

	result = NULL;
	lstat(a->file_name, &meta1);
	lstat(b->file_name, &meta2);
	if(meta1.st_mtimespec.tv_nsec > meta2.st_mtimespec.tv_nsec)
	{
		result = a;
		result->next = sorted_merge_time(a->next, b);
	}
	else
	{
		result = b;
		result->next = sorted_merge_time(a, b->next);
	}
	return(result);
}


t_ls *sorted_merge_time(t_ls *a, t_ls *b)
{
	struct stat meta1;
	struct stat meta2;
//	struct timespec last_modified1;
//	struct timespec last_modified2;
	t_ls *result;

	result = NULL;
	if(a == NULL)
		return(b);
	else if(b == NULL)
		return(a);
	lstat(a->file_name, &meta1);
	lstat(b->file_name, &meta2);
//	last_modified1 = meta1.st_mtimespec;
//	last_modified2 = meta2.st_mtimespec;
//  if(last_modified1.tv_sec > last_modified2.tv_sec)
	if(meta1.st_mtimespec.tv_sec > meta2.st_mtimespec.tv_sec)
	{
		result = a;
		result->next = sorted_merge_time(a->next, b);
	}
	else if(meta1.st_mtimespec.tv_sec == meta2.st_mtimespec.tv_sec)
	{
		result = sorted_merge_time_nano_second(a, b);
	}
	else
	{
		result = b;
		result->next = sorted_merge_time(a, b->next);
	}
	return(result);
}

t_ls *sorted_merge_time_reverse(t_ls *a, t_ls *b);

t_ls *sorted_merge_time_reverse_nano_second(t_ls *a, t_ls *b)
{
	t_ls *result;
	struct stat meta1;
	struct stat meta2;

	result = NULL;
	lstat(a->file_name, &meta1);
	lstat(b->file_name, &meta2);
	if(meta1.st_mtimespec.tv_nsec < meta2.st_mtimespec.tv_nsec)
	{
		result = a;
		result->next = sorted_merge_time_reverse(a->next, b);
//		result = b;
//		result->next = sorted_merge_time_reverse(a, b->next);

	}
	else
	{
		result = b;
		result->next = sorted_merge_time_reverse(a, b->next);
//		result = a;
//		result->next = sorted_merge_time_reverse(a->next, b);

	}
	return(result);
}

t_ls *sorted_merge_time_reverse(t_ls *a, t_ls *b)
{
	struct stat meta1;
	struct stat meta2;
	t_ls *result;

	result = NULL;
	if(a == NULL)
		return(b);
	else if(b == NULL)
		return(a);
	lstat(a->file_name, &meta1);
	lstat(b->file_name, &meta2);
	if(meta1.st_mtimespec.tv_sec < meta2.st_mtimespec.tv_sec)
	{
		result = a;
		result->next = sorted_merge_time_reverse(a->next, b);
//		result = b;
//		result->next = sorted_merge_time_reverse(a, b->next);

	}
	else if(meta1.st_mtimespec.tv_sec == meta2.st_mtimespec.tv_sec)
	{
		result = sorted_merge_time_reverse_nano_second(a, b);
	}
	else
	{
		result = b;
		result->next = sorted_merge_time_reverse(a, b->next);
//		result = a;
//		result->next = sorted_merge_time_reverse(a->next, b);

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

void	merge_sort(t_ls **head_ref, t_info *info)
{
	t_ls *head;
	t_ls *a;
	t_ls *b;
//	struct stat meta1;
//	struct stat meta2;

	head = *head_ref;
	if(head == NULL || head->next == NULL)
		return;
	front_back_split(head, &a, &b);
	merge_sort(&a, info);
	merge_sort(&b, info);
//	ft_printf("info->flag.t|%d|\n", info->flag.t);
//	ft_printf("info->flag.r|%d|\n", info->flag.r);
	if(info->flag.r == false && info->flag.t == false)
		*head_ref = sorted_merge(a, b);
	else if(info->flag.r == true && info->flag.t == false)
		*head_ref = sorted_merge_reverse(a, b);
	else if(info->flag.t == true && info->flag.r == false)
		*head_ref = sorted_merge_time(a, b);
	else if(info->flag.t == true && info->flag.r == true)
		*head_ref = sorted_merge_time_reverse(a,b);
}

/*
** Get count function calculates how many nodes there are, used to determine
** if there are 2 nodes in a linked list, then it breaks and returns count
** if the count is 2 then path will be printed.
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
			if (count == 2)
				break;
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
		}
	}

	if(dir != NULL)
	{
		closedir(dir);
		if(ls != NULL)
			new_ls = append_slash(new_ls, ls, dir_path_str);
		delete_list_file_name(&ls);
		merge_sort(&new_ls, info);
		print_file_name(new_ls, info);
		delete_list_file_name(&new_ls);
	}
}

int main(int argc, char *argv[])
{
	t_ls	*ls;
	t_info	info;
	

	ls = NULL;
	ft_bzero(&info, sizeof(&info));
	info.argc = argc;
	info.argv = argv;
	if(argc == 1)
		single_argument(ls, &info, ".");
	else if(argc > 1)
		ls_start_parsing(ls, &info);
	if(ls)
		delete_list_file_name(&ls);
	return(0);
}
