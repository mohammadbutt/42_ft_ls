# 42_ft_ls - Purpose of the project is to recode ls(1).

ls, list directory contents, is a command to list computer files in Unix and Unix-like operating systems.

#### Project file: [ft_ls](https://github.com/mohammadbutt/42_ft_ls/blob/master/doc_ft_ls.en.pdf)
Allowed C functions: opendir(3), readdir(3), closedir(3), getpwuid(3), getgrgid(3), time(3), ctime(3), malloc(3), free(3), perror(3), strerror(3), exit(3).

Justifiable C functions for bonus part: tcgetattr(3). Structs found in `man 4 tty`.

Allowed  System Calls:  write(2), stat(2)(struct), lstat(2)(struct), listxattr(2), getxattr(2), readlink(2)



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
9. [Members of winsize struct - Delorie](http://www.delorie.com/djgpp/doc/libc/libc_495.html)
10. [Members of stat struct - man7.org](http://man7.org/linux/man-pages/man2/stat.2.html)
11. [Members of stat struct st_mode - mkssoftware](https://www.mkssoftware.com/docs/man5/struct_stat.5.asp)
12. [Recursively list directories in C on Linux - Stackoverflow](https://stackoverflow.com/questions/8436841/how-to-recursively-list-directories-in-c-on-linux)
13. [Carnegie Mellon University - Introduction to Computer Systems - Lecture System Level I/O](https://scs.hosted.panopto.com/Panopto/Pages/Viewer.aspx?id=f107c2ce-79d5-4529-baeb-2bb495d8c11a)
