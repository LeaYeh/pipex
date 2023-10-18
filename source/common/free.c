/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:44:41 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/18 13:17:36 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "common.h"
#include "error.h"

void	safe_free(void **buf)
{
	if (*buf == NULL)
		return ;
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
			safe_free(&arr[i]);
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
		free_array((void **)cmd_list[i].full_cmd, -1);
		i++;
	}
	free (cmd_list);
}

void	free_pipex_table(t_pipex_tab *tab)
{
	close(tab->infile);
	close(tab->outfile);
	free_cmd_list(tab->cmd_list, tab->cmd_cnt);
	free_array((void **)tab->pipefd, tab->pipe_cnt);
	free(tab);
}
