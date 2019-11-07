/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_this4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 12:58:25 by mbutt             #+#    #+#             */
/*   Updated: 2019/09/29 13:02:48 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/param.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

int listDir_helper(char* path) {
  char slash = '\\';
  DIR* dir;
  struct dirent *ent;
  char *NulPosition = &path[strlen(path)];
  if ((dir = opendir(path)) != NULL) {
    while ((ent = readdir(dir)) != NULL) {
      printf("%s%c%s\n", path, slash, ent->d_name);
      if (ent->d_type == DT_DIR) {
        if ((strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, "..") != 0)) {
          sprintf(NulPosition, "%c%s", slash, ent->d_name);
          if (listDir_helper(path)) {
            closedir(dir);
            return 1;
          }
          *NulPosition = '\0';
        }
      }
    }
  }
  closedir(dir);
  return 0;
}

int listDir(char* path){
  struct dirent *ent;
  char pathmax[MAXPATHLEN+1+sizeof(ent->d_name)+1];
  if (strlen(path) > MAXPATHLEN) return 1;
  strcpy(pathmax, path);
  return listDir_helper(pathmax);
}

int main()
{
  listDir(".");
  return 0;
}
