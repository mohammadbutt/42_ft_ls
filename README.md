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

#### `-l` flag
-l flag has several elements to it. It's generally called long format and it gives several pieces of information about a file or directory. It displays Unix file type, permissions, number of hardlinks, owner, group, size in bytes, last-modified date and time , and file name.

First line of the output `ls -l` gives a total. This total is file system blocks. Running `ls -s` shows the size of each file and folder, their sum will equal to the sum of total for `ls -l`. File system block can be acessed in stat(2).

Below is a table and format of `ls -l author` and `./ft_ls -l author`


|Permission|st_nlink|owner id| group owner id |size in bytes |month, date, time modified  |file name|
|----------|--------|--------|----------------|--------------|----------------------------|---------|
|Permission|st_nlink|st_uid  |        st_gid  |   st_size    |st_ctimespec.tv_sec         |d_name   |
|          |   ✔    |   ✔    |         ✔      |     ✔        |       ✔                    |      ✔  |
|-rw-r--r--|    1   |  mbutt |   2018_october |       6      | Sep 18 15:35               |  author |


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
