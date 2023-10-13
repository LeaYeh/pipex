/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:07:56 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/13 19:12:42 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "error.h"

void	do_parent(int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		printf("子进程正常结束，退出状态：%d\n", WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		printf("子进程因信号结束，信号号码：%d\n", WTERMSIG(status));
	else
		printf("子进程结束状态未知\n");
}

void	do_child(int fd_in, int fd_out, int cur_idx, t_pipex_tab *tab)
{
	int		i;

	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	i = 0;
	while (i < cur_idx)
	{
		close(tab->pipefd[i][0]);
		close(tab->pipefd[i][1]);
		i++;
	}
	execve(tab->cmd_list[cur_idx].exec_cmd,
		tab->cmd_list[cur_idx].full_cmd, tab->envp);
	free_pipex_table(tab);
	exit(ERROR_EXEC_FAILED);
}

void	create_proc(int fd_in, int fd_out, int cur_idx, t_pipex_tab *tab)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		free_pipex_table(tab);
		exit(ERROR_FORK_PROC_FAILED);
	}
	else if (pid == 0)
		do_child(fd_in, fd_out, cur_idx, tab);
	else
		do_parent(pid);
}
