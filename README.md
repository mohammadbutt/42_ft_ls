# 42_ft_ls - Purpose of the project is to recode ls(1).

ls, list directory contents, is a command to list computer files in Unix and Unix-like operating systems.

#### Project file: [ft_ls](https://github.com/mohammadbutt/42_ft_ls/blob/master/ft_ls.en.pdf)
Allowed C functions: opendir(3), readdir(3), closedir(3), getpwuid(3), getgrgid(3), time(3), ctime(3), malloc(3), free(3), perror(3), strerror(3), exit(3).

Allowed BSD System Calls:  write(2), stat(2), lstat(2), listxattr(2), getxattr(2), readlink(2)

#### Mandatory Flags:
1. `-l`
   - a total sum of all the file sizes.
2. `-R`
   - Recursively lists subdirectories.
3. `-a`
   - Include directories that begin with a dot `.`.
4. `-r`
   - Reverse the order of the sot to get reverse lexical order or the oldest entries.
5. `-t`
   - Sort by time modified (most recently modified first).
   
#### Optional/Bonus Flags:
1. `-u`
   - Use time of last access (not modified, or printed).
2. `-f`
   - Output is not sorted. Turns on `-a` option/flag.
3. `-d`
   - Directories are listed as plain files.
4. `-G`
   - Colorizes output.
