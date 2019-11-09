# 42_ft_ls - Purpose of the project is to recode ls(1).

ls, list directory contents, is a command to list computer files in Unix and Unix-like operating systems.

#### Project file: [ft_ls](https://github.com/mohammadbutt/42_ft_ls/blob/master/documents_and_media/doc_ft_ls.en.pdf)
Allowed C functions: opendir(3), readdir(3), closedir(3), getpwuid(3), getgrgid(3), time(3), ctime(3), malloc(3), free(3), perror(3), strerror(3), exit(3).

Justifiable C functions for bonus part: tcgetattr(3). Structs found in `man 4 tty`.

Allowed  System Calls:  write(2), stat(2)(struct), lstat(2)(struct), listxattr(2), getxattr(2), readlink(2)

---
# Table of Contents - Click a section to jump to it 


# Cloning Repository
```
https://github.com/mohammadbutt/42_ft_ls.git
```

# Installing ft_ls
```
make
```

# ft_ls Usage
```
./ft_ls
./ft_ls -l
./ft_ls -R
./ft_ls -a
./ft_ls -r
./ft_ls -t
```

/# Program Installation gif Demo


/# Program Usage gif Demo


# Project Summary

### Parsing - [Source Code](https://github.com/mohammadbutt/42_ft_ls/blob/master/ft_ls_src/ls_parsing.c)
When the user runs the program and there in only one argument that is `./ft_ls` then the program calls onto the function `void	single_argument(t_ls *ls, t_info *info, char *dir_path_str)`. Single_argument calls onto opendir(3), opendir takes in the path of a directory. If a directory has permission denied, then the program will print the name of the directory and then display "permission denied". If a directory is valid, then readdir(3) is used with dirent struct to open the directory and read the contents of the directory one at a time, the contents of the directory are stored in a linked list. A slash is appended after the directory path and the file name is concatenated after it. For example, "this_is_a_directory/file_name". List is saved with the last index of the file. This slash index is used later to print just the file name instead of printing the file path and the name when only the file name is needed.

If there is a dash `-` after `./ft_ls ` that's when the program starts collecting flags that are `l`, `R`, `a`, `t`, `r`. If there is no dash then the program looks for either a valid or invalid file name, or a directory. If a file name is valid then the program displays the file name, if an entered file does not exist then the program displays a message, "./ft_ls: name_of_invalid_file: No such file or directory", just like the original ls. If the entered name is a directory then the program displays files of that directory.

### `-R` Recursively list subdirectories - [Source Code](https://github.com/mohammadbutt/42_ft_ls/blob/master/ft_ls_src/ls_recursive_call.c)
If there are two arguments and the `R` flag exists in the argument then the program recursively enters through directories and subdirectories the open each directory, store the files in a linked list, sorts them, prints the files, frees the linked list, and then moves to the next directory to perform the same action until it gets to the end cant find any more directories to treverse through. Below is a table:

```
|___CODEOWNERS
|___Makefile
|___README.md
|___author
|___documents_and_media
|  |___doc_ft_ls.en.pdf
|  |___norme.en.pdf
|___empty_dir
|___ft_ls_src
|  |___append_slash.c
|  |___delete_linked_list.c
|  |___formatting.c
|  |___ft_ls.h
|  |___ft_printf
|  |  |___Makefile
|  |  |___srcs
|  |  |  |___append_to_buffer.c
|  |  |  |___collect_and_cancel_flags.c
|  |  |  |___collect_width_precision_length_type.c
|  |  |  |___ft_itoa_min_handler.c
|  |  |  |___ft_printf.c
|  |  |  |___ft_printf.h
|  |  |  |___mini_libft
|  |  |  |  |___ft_atoi.c
|  |  |  |  |___ft_bzero.c
|  |  |  |  |___ft_ftoa.c
|  |  |  |  |___ft_hex.c
|  |  |  |  |___ft_isdigit.c
|  |  |  |  |___ft_itoa_base.c
|  |  |  |  |___ft_putstr.c
|  |  |  |  |___ft_strcat.c
|  |  |  |  |___ft_strcmp.c
|  |  |  |  |___ft_strcpy.c
|  |  |  |  |___ft_strdup.c
|  |  |  |  |___ft_strlen.c
|  |  |  |  |___mini_libft.h
|  |  |  |  |___utility.c
|  |  |  |___parsing.c
|  |  |  |___type_field_b.c
|  |  |  |___type_field_c.c
|  |  |  |___type_field_d_i.c
|  |  |  |___type_field_f.c
|  |  |  |___type_field_o.c
|  |  |  |___type_field_p.c
|  |  |  |___type_field_percent.c
|  |  |  |___type_field_s.c
|  |  |  |___type_field_u.c
|  |  |  |___type_field_x.c
|  |  |  |___type_field_x_remaining_conditions.c
|  |___long_file_listing.c
|  |___ls_collect_flags.c
|  |___ls_parsing.c
|  |___ls_recursive_call.c
|  |___main.c
|  |___merge_sort_alpha.c
|  |___merge_sort_invalid_file.c
|  |___merge_sort_time.c
|  |___padding_and_blocks_total.c
|  |___print_file_name.c
|  |___process_dir_valid.c
|  |___process_valid_and_invalid_file.c
|  |___store_file_name.c
|  |___store_file_name_with_index.c
|  |___usage_and_permission_denied.c

```

### `-l` Long file listing - [Source Code](https://github.com/mohammadbutt/42_ft_ls/blob/master/ft_ls_src/long_file_listing.c)
If there are two arguments, some examples would be `./ft_ls -l`, `./ft_ls -la`, `./ft_ls -lar`, then the program collects the flags that are after dash, and sets them equal to true, `l` stands for long listing format. 

Below is a table and format of `ls -l author` and `./ft_ls -l author`

|Permission|Links   |owner id| group owner id |size in bytes |month, date, time modified  |file name                    |
|----------|--------|--------|----------------|--------------|----------------------------|-----------------------------|
|Permission|st_nlink|st_uid  |        st_gid  |   st_size    |st_ctimespec.tv_sec         |d_name under dirent struct   |
|-rw-r--r--|    1   |  mbutt |   2018_october |       6      | Sep 18 15:35               |  author                     |

### 



#### Mandatory Flags:
1. `-l`
   - a total sum of all the file sizes.
2. `-R`
   - Recursively lists subdirectories.
3. `-a`
   - Include directories that begin with a dot '.'.
4. `-r`
   - Reverse the order of the sot to get reverse lexical order or the oldest entries.
5. `-t`
   - Sort by time modified (most recently modified first).

#### `-l` flag
-l flag has several elements to it. It's generally called long format and it gives several pieces of information about a file or directory. It displays Unix file type, permissions, number of hardlinks, owner, group, size in bytes, last-modified date and time , and file name.

First line of the output `ls -l` gives a total. This total is file system blocks. Running `ls -s` shows the size of each file and folder, their sum will equal to the sum of total for `ls -l`. File system block can be acessed in stat(2).

Below is a table and format of `ls -l author` and `./ft_ls -l author`


|Permission|st_nlink|owner id| group owner id |size in bytes |month, date, time modified  |file name                    |
|----------|--------|--------|----------------|--------------|----------------------------|-----------------------------|
|Permission|st_nlink|st_uid  |        st_gid  |   st_size    |st_ctimespec.tv_sec         |d_name under dirent struct   |
|    ✔     |   ✔    |   ✔    |         ✔      |     ✔        |       ✔                    |      ✔                      |
|-rw-r--r--|    1   |  mbutt |   2018_october |       6      | Sep 18 15:35               |  author                     |


#### Optional/Bonus Flags:
1. `-u`
   - Use time of last access (not modified, or printed).
2. `-f`
   - Output is not sorted. Turns on `-a` option/flag.
3. `-d`
   - Directories are listed as plain files.
4. `-G`
   - Colorizes output.

# Resources and References
1. [ls - Wikipedia](https://en.wikipedia.org/wiki/Ls)
2. [ls source code](https://github.com/wertarbyte/coreutils/blob/master/src/ls.c)
3. [Decoded ls - maizure.org](http://www.maizure.org/projects/decoded-gnu-coreutils/ls.html)
4. [Simple ls - stackoverflow](https://stackoverflow.com/questions/3554120/open-directory-using-c)
5. [Members of dirent struct - Apple OS Reference](https://opensource.apple.com/source/xnu/xnu-4570.41.2/bsd/sys/dirent.h.auto.html)
6. [Dirent and Stat usage](http://codepad.org/mocgJvtX#output)
7. [Differentiate between a unix directory and file in C - Stackoverflow](https://stackoverflow.com/questions/1036625/differentiate-between-a-unix-directory-and-file-in-c-and-c)
8. [Singly Linked List - Hacker Earth](https://www.hackerearth.com/practice/data-structures/linked-list/singly-linked-list/tutorial/)
9. [Merge Sort for Linked List - geeksforgeeks](https://www.geeksforgeeks.org/merge-sort-for-linked-list/)
10. [C program to list all files in a directory recursively - Codeforwin.org](https://codeforwin.org/2018/03/c-program-to-list-all-files-in-a-directory-recursively.html)
10. [Members of winsize struct - Delorie](http://www.delorie.com/djgpp/doc/libc/libc_495.html)
11. [Members of stat struct - man7.org](http://man7.org/linux/man-pages/man2/stat.2.html)
12. [Members of stat struct st_mode - mkssoftware](https://www.mkssoftware.com/docs/man5/struct_stat.5.asp)
13. [Recursively list directories in C on Linux - Stackoverflow](https://stackoverflow.com/questions/8436841/how-to-recursively-list-directories-in-c-on-linux)
14. [Carnegie Mellon University - Introduction to Computer Systems - Lecture System Level I/O](https://scs.hosted.panopto.com/Panopto/Pages/Viewer.aspx?id=f107c2ce-79d5-4529-baeb-2bb495d8c11a)
15. [Big O Cheatsheet - Hackerearth](https://www.hackerearth.com/practice/notes/big-o-cheatsheet-series-data-structures-and-algorithms-with-thier-complexities-1/)
16. [Big O Cheatsheet - bigocheatsheet](https://www.bigocheatsheet.com/)
17. [Algorithms and Data Structures - Cooervo.github.io](https://cooervo.github.io/Algorithms-DataStructures-BigONotation/index.html)
18. [List all directories in a given directory - Works - Stackoverflow](https://stackoverflow.com/questions/1723002/how-to-list-all-subdirectories-in-a-given-directory-in-c)
19. [A Recursive Directory Scanning program](https://johnloomis.org/ece537/notes/Files/Examples/printdir.html)
20. [Linux print file information format](http://www.hep.by/gnu/findutils/Print-File-Information.html)
21. [View file permissions in Linux](https://askubuntu.com/questions/528411/how-do-you-view-file-permissions)
22. [ls -l permissions](https://stackoverflow.com/questions/10323060/printing-file-permissions-like-ls-l-using-stat2-in-c)
23. [Permission Bits explained](https://www.gnu.org/software/libc/manual/html_node/Permission-Bits.html)
24. [Linux File type](https://www.gnu.org/software/libc/manual/html_node/Testing-File-Type.html#Testing-File-Type)
25. [Determining if a file is a link](https://stackoverflow.com/questions/3984948/how-to-figure-out-if-a-file-is-a-link)
26. [Extended Attributes @ that appears in permission/chmod](https://stackoverflow.com/questions/36229265/how-to-get-extended-attributes-of-a-fileunix-c)
