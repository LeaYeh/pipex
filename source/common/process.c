/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:07:56 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/25 14:06:57 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "common.h"
#include "error.h"

void	do_child(t_pipex_tab *tab, int cur_idx)
{
	dup2(tab->fd_in, STDIN_FILENO);
	dup2(tab->fd_out, STDOUT_FILENO);
	safe_close(&tab->infile);
	safe_close(&tab->outfile);
	safe_close(&tab->pipefd[0]);
	safe_close(&tab->pipefd[1]);
	execve(tab->cmd_list[cur_idx].full_cmd[0],
		tab->cmd_list[cur_idx].full_cmd, tab->envp);
	free_pipex_table(tab);
	exit(ERROR_EXEC_FAILED);
}

bool	setup_fd(t_pipex_tab *tab, int idx)
{
	if (idx < ft_max(2, (tab->cmd_cnt - 1), 1))
	{
		if (pipe(tab->pipefd) == -1)
			return (false);
	}
	if (idx == 0)
	{
		tab->fd_in = tab->infile;
		tab->fd_out = tab->pipefd[1];
		tab->prev_read_end = tab->pipefd[0];
	}
	else if (idx == tab->cmd_cnt - 1)
	{
		tab->fd_in = tab->prev_read_end;
		tab->fd_out = tab->outfile;
		tab->prev_read_end = -1;
	}
	else
	{
		tab->fd_in = tab->prev_read_end;
		tab->fd_out = tab->pipefd[1];
		tab->prev_read_end = tab->pipefd[0];
	}
	return (true);
}

void	create_proc(t_pipex_tab *tab, int cur_idx)
{
	if (!setup_fd(tab, cur_idx))
	{
		free_pipex_table(tab);
		exit(ERROR_INIT_PIPE_FAILED);
	}
	tab->child_pid_list[cur_idx] = fork();
	if (tab->child_pid_list[cur_idx] == -1)
	{
		free_pipex_table(tab);
		exit(ERROR_FORK_PROC_FAILED);
	}
	else if (tab->child_pid_list[cur_idx] == 0)
		do_child(tab, cur_idx);
	else
	{
		if (tab->fd_in == tab->infile)
			safe_close(&tab->infile);
		if (tab->fd_out == tab->outfile)
			safe_close(&tab->outfile);
		if (cur_idx > 0)
			safe_close(&tab->fd_in);
		if (cur_idx != tab->cmd_cnt - 1)
			safe_close(&tab->pipefd[1]);
	}
}
