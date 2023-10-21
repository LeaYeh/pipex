/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 15:42:53 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/21 15:44:08 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "pipex.h"
#include "libft.h"
#include "ft_printf.h"
#include "common.h"

static void	_setup_fd(int *fd_in, int *fd_out, int idx, t_pipex_tab *tab)
{
	static int	prev_read_end;
	int			pipefd[2];

	if (idx < ft_max(2, (tab->cmd_cnt - 1), 1))
	{
		if (pipe(pipefd) == -1)
		{
			close(prev_read_end);
			free_pipex_table(tab);
			exit(ERROR_INIT_PIPE_FAILED);
		}
	}
	*fd_in = tab->infile;
	*fd_out = tab->outfile;
	if (idx == 0)
		*fd_out = pipefd[1];
	else if (idx == tab->cmd_cnt - 1)
		*fd_in = prev_read_end;
	else
	{
		*fd_in = prev_read_end;
		*fd_out = pipefd[1];
	}
	prev_read_end = pipefd[0];
}

void	pipex(t_pipex_tab *tab)
{
	int	i;
	int	fd_in;
	int	fd_out;
	int	status;

	i = 0;
	while (i < tab->cmd_cnt)
	{
		_setup_fd(&fd_in, &fd_out, i, tab);
		create_proc(fd_in, fd_out, i, tab);
		close(fd_in);
		close(fd_out);
		i++;
	}
	i = tab->cmd_cnt;
	while (i-- > 0)
	{
		waitpid(tab->child_pid_list[i], &status, WNOHANG);
		if (WIFEXITED(status))
			ft_dprintf(2, "(%s) process success.\n",
				tab->cmd_list[i].full_cmd[0]);
		else if (WIFSIGNALED(status))
			ft_dprintf(2, "(%s) process terminated by signal.\n",
				tab->cmd_list[i].full_cmd[0]);
	}
}

void	init_pipex_table(int argc, char **argv, char **envp, t_pipex_tab *tab)
{
	int		i;
	char	**full_cmd;

	tab->cmd_list = malloc(sizeof(t_cmd) * (argc - 3));
	if (!tab->cmd_list)
		exit(ERROR_MEM_ALLOC_FAILED);
	tab->child_pid_list = ft_calloc(argc - 3, sizeof(int));
	if (tab->child_pid_list == NULL)
		exit(ERROR_MEM_ALLOC_FAILED);
	tab->cmd_cnt = argc - 3;
	i = 0;
	while (i + 2 < argc - 1)
	{
		full_cmd = ft_split(argv[i + 2], ' ');
		if (!full_cmd)
		{
			free_cmd_list(tab->cmd_list, i);
			exit(ERROR_MEM_ALLOC_FAILED);
		}
		set_cmd_params(&tab->cmd_list[i], full_cmd, envp);
		i++;
	}
	tab->infile = open(argv[1], O_RDONLY);
	tab->outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
	tab->envp = envp;
}

int	main(int argc, char **argv, char **envp)
{
	t_error_code	error_code;
	t_pipex_tab		*tab;

	error_code = check_input(argc, argv, envp, false);
	if (error_code != ERROR_NONE)
		exit(error_code);
	tab = malloc(sizeof(t_pipex_tab) * 1);
	if (!tab)
		exit(ERROR_MEM_ALLOC_FAILED);
	init_pipex_table(argc, argv, envp, tab);
	pipex(tab);
	free_pipex_table(tab);
	exit(ERROR_NONE);
}
