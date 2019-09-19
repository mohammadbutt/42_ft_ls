/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 21:19:28 by mbutt             #+#    #+#             */
/*   Updated: 2019/09/18 22:21:03 by mbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int main(int argc, char **argv)
{
	struct dirent *pDirent;
	DIR *pDir;

	if(argc < 2)
	{
		ft_printf("Useage: testprog <dirname>\n");
		return(1);
	}
	pDir = opendir(argv[1]);
	if(pDir == NULL)
	{
		ft_printf("Cannot open directory '%s'\n", argv[1]);
		return(1);
	}
	while((pDirent = readdir(pDir)) != NULL)
		ft_printf("[%s]\n", pDirent->d_name);
	closedir(pDir);
	return(0);
}

/*
int main(void)
{
	   printf("   printf:|This is a test.|\n");
	ft_printf("ft_printf:|This is a test.|\n");
}
*/
