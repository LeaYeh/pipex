/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:44:41 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/27 14:56:44 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	safe_free(void **buf)
{
	free(*buf);
	*buf = NULL;
}

void	free_array(void **arr, int count)
{
	int	i;

	if (arr == NULL)
		return ;
	if (count == -1)
		count = get_array_len(arr);
	if (count == 0)
		return ;
	i = 0;
	while (i < count)
	{
		if (arr[i])
			safe_free((void **)&arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

void	free_cmd_list(t_cmd *cmd_list, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(cmd_list[i].exec_cmd);
		free_array((void **)cmd_list[i].full_cmd, -1);
		i++;
	}
	free(cmd_list);
}

void	safe_close(int *fd)
{
	if (*fd < 0)
		return ;
	close(*fd);
	*fd = -1;
}

void	free_pipex_table(t_pipex_tab *tab)
{
	safe_close(&tab->pipefd[0]);
	safe_close(&tab->pipefd[1]);
	safe_close(&tab->prev_read_end);
	free_cmd_list(tab->cmd_list, tab->cmd_cnt);
	free(tab->child_pid_list);
	free(tab);
}
