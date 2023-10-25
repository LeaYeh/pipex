/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:45:05 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/24 12:55:31 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "pipex.h"
#include "libft.h"
#include "ft_printf.h"
#include "common.h"

void	pipex(t_pipex_tab *tab)
{
	int	i;
	int	status;

	i = 0;
	while (i < tab->cmd_cnt)
	{
		create_proc(tab, i);
		i++;
	}
	i = tab->cmd_cnt;
	while (i-- > 0)
	{
		waitpid(tab->child_pid_list[i], &status, 0);
		if (WIFEXITED(status))
			ft_dprintf(2, "(%s) process success.\n",
				tab->cmd_list[i].full_cmd[0]);
		else if (WIFSIGNALED(status))
			ft_dprintf(2, "(%s) process terminated by signal.\n",
				tab->cmd_list[i].full_cmd[0]);
	}
}

bool	init_cmd_list(int argc, char **argv, char **envp, t_pipex_tab *tab)
{
	int		i;
	char	**full_cmd;

	tab->cmd_list = malloc(sizeof(t_cmd) * (argc - 3));
	if (!tab->cmd_list)
	{
		ft_dprintf(2, "Init cmd list, memory alloc failed.\n");
		return (false);
	}
	tab->cmd_cnt = argc - 3;
	i = 0;
	while (i + 2 < argc - 1)
	{
		full_cmd = ft_split(argv[i + 2], ' ');
		if (!full_cmd)
		{
			ft_dprintf(2, "Split full_cmd, memory alloc failed.\n");
			free_cmd_list(tab->cmd_list, i);
			return (false);
		}
		set_cmd_params(&tab->cmd_list[i], full_cmd, envp);
		i++;
	}
	return (true);
}

void	init_pipex_table(int argc, char **argv, char **envp, t_pipex_tab *tab)
{
	if (!init_cmd_list(argc, argv, envp, tab))
		exit(ERROR_INIT_CMD_LIST_FAILED);
	tab->child_pid_list = ft_calloc(argc - 3, sizeof(int));
	if (tab->child_pid_list == NULL)
		exit(ERROR_MEM_ALLOC_FAILED);
	tab->envp = envp;
	tab->infile = open(argv[1], O_RDONLY);
	tab->outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
	tab->fd_in = -1;
	tab->fd_out = -1;
	tab->prev_read_end = -1;
}

int	main(int argc, char **argv, char **envp)
{
	t_error_code	error_code;
	t_pipex_tab		*tab;

	error_code = check_input(argc, argv, envp, true);
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
