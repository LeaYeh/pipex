/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:44:41 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/13 12:54:49 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "common.h"

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

void	free_array(void **arr, size_t elm_size)
{
	int	i;
	int	count;

	count = get_array_len(arr);
	if (arr == NULL || count <= 0)
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
		free_array((void **)cmd_list[i].full_cmd, sizeof(char));
		i++;
	}
	free (cmd_list);
}

void	free_pipex_table(t_pipex_tab *tab)
{
	close(tab->infile);
	close(tab->outfile);
	free_cmd_list(tab->cmd_list, tab->cmd_cnt);
	free_array((void **)tab->pipefd, sizeof(int));
	free(tab);
}
