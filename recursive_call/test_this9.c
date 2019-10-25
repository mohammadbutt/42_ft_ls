/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_this9.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 22:50:01 by mbutt             #+#    #+#             */
/*   Updated: 2019/10/24 22:50:07 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h> 
#include <stdio.h> 
#include <string.h>

#define NORMAL_COLOR  "\x1B[0m"
#define GREEN  "\x1B[32m"
#define BLUE  "\x1B[34m"



/* let us make a recursive function to print the content of a given folder */

void show_dir_content(char * path)
{
  DIR * d = opendir(path); // open the path
  if(d==NULL) return; // if was not able return
  struct dirent * dir; // for the directory entries
  while ((dir = readdir(d)) != NULL) // if we were able to read somehting from the directory
    {
      if(dir-> d_type != DT_DIR) // if the type is not directory just print it with blue
        printf("%s%s\n",BLUE, dir->d_name);
      else
      if(dir -> d_type == DT_DIR && strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0 ) // if it is a directory
      {
        printf("%s%s\n",GREEN, dir->d_name); // print its name in green
        char d_path[255]; // here I am using sprintf which is safer than strcat
        sprintf(d_path, "%s/%s", path, dir->d_name);
        show_dir_content(d_path); // recall with the new path
      }
    }
    closedir(d); // finally close the directory
}

int main(int argc, char **argv)
{

  printf("%s\n", NORMAL_COLOR);

    show_dir_content(argv[1]);

  printf("%s\n", NORMAL_COLOR);
  return(0);
}
