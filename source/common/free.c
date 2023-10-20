/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:44:41 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/20 13:20:25 by lyeh             ###   ########.fr       */
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
			free(arr[i]);
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
		free_array((void **)cmd_list[i].full_cmd, len);
		// safe_free((void **)&cmd_list[i].exec_cmd);
		i++;
	}
	free (cmd_list);
}

void	free_pipex_table(t_pipex_tab *tab)
{
	free_cmd_list(tab->cmd_list, tab->cmd_cnt);
	free(tab->child_pid_list);
	free(tab);
}
