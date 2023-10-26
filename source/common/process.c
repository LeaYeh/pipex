/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:07:56 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/26 19:18:41 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "common.h"
#include "error.h"
#include "ft_printf.h"

void	do_child(t_pipex_tab *tab, int cur_idx)
{
	if (cur_idx == 0)
		tab->fd_in = open(tab->infile_path, O_RDONLY);
	if (cur_idx == (tab->cmd_cnt - 1))
		tab->fd_out = open(tab->outfile_path, O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (tab->fd_in == -1 || tab->fd_out == -1)
	{
		ft_dprintf(2, "here1: ");
		perror(tab->program_name);
		free_pipex_table(tab);
	}
	if (dup2(tab->fd_in, STDIN_FILENO) == -1 || \
		dup2(tab->fd_out, STDOUT_FILENO) == -1)
	{
		ft_dprintf(2, "here2: ");
		perror(tab->program_name);
		free_pipex_table(tab);
	}
	safe_close(&tab->pipefd[0]);
	safe_close(&tab->pipefd[1]);
	execve(tab->cmd_list[cur_idx].full_cmd[0],
		tab->cmd_list[cur_idx].full_cmd, tab->envp);
	ft_dprintf(2, "%s: %s: ", tab->program_name, tab->cmd_list[cur_idx].full_cmd[0]);
	perror("");
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
		tab->fd_out = tab->pipefd[1];
		tab->prev_read_end = tab->pipefd[0];
	}
	else if (idx == tab->cmd_cnt - 1)
	{
		tab->fd_in = tab->prev_read_end;
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
		if (cur_idx > 0)
			safe_close(&tab->fd_in);
		if (cur_idx != tab->cmd_cnt - 1)
			safe_close(&tab->pipefd[1]);
	}
}
