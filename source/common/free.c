/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:44:41 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/13 20:21:37 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "common.h"
#include "error.h"

void	safe_free(void **buf, size_t elm_size)
{
	if (*buf == NULL)
		return ;
	if (elm_size != sizeof(char))
		ft_memset(*buf, 0, elm_size);
	else
		free(*buf);
	*buf = NULL;
}

void	free_array(void **arr, int count, size_t elm_size)
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
			safe_free(&arr[i], elm_size);
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
		safe_free((void **)&cmd_list[i].exec_cmd, sizeof(char));
		free_array((void **)cmd_list[i].full_cmd, -1, sizeof(char));
		i++;
	}
	free (cmd_list);
}

void	free_pipe_list(int **pipe_arr, int pipe_cnt)
{
	// int	i;
	// int	close_status;

	// i = 0;
	// while (i < pipe_cnt - 1)
	// {
	// 	close_status = close(pipe_arr[i][0]);
	// 	close_status |= close(pipe_arr[i][1]);
	// 	if (close_status != 0)
	// 	{
	// 		perror("Error closing file");
	// 		exit(ERROR_CLOSE_FD_FAILED);
	// 	}
	// 	i++;
	// }
	free_array((void **)pipe_arr, pipe_cnt, sizeof(int) * 2);
}

void	free_pipex_table(t_pipex_tab *tab)
{
	close(tab->infile);
	close(tab->outfile);
	free_cmd_list(tab->cmd_list, tab->cmd_cnt);
	free_pipe_list(tab->pipefd, tab->pipe_cnt);
	free(tab);
}
