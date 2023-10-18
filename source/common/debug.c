/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:02:38 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/18 17:19:43 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "common.h"

void    print_pipx_table(t_pipex_tab *tab)
{
	int i;
	int j;

	printf("tab->cmd_cnt = %d\n", tab->cmd_cnt);
	printf("tab->pipe_cnt = %d\n", tab->pipe_cnt);
	i = 0;
	while (i < tab->cmd_cnt)
	{
		printf("cmd[%d] = %s\n", i, tab->cmd_list[i].full_cmd[0]);
		j = 0;
		while (tab->cmd_list[i].full_cmd && tab->cmd_list[i].full_cmd[j])
		{
			printf("\tcmd[%d][%d] = %s\n", i, j, tab->cmd_list[i].full_cmd[j]);
			j++;
		}
		i++;
	}
	printf("tab->infile = %d\n", tab->infile);
	printf("tab->outfile = %d\n", tab->outfile);
	i = 0;
	while (i < tab->pipe_cnt)
	{
		printf("tab->pipefd[%d][0]: %d, tab->pipefd[%d][1]: %d\n", i, i, tab->pipefd[i][0], tab->pipefd[i][1]);
		i++;
	}
}
