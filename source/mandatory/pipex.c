/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:45:05 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/18 22:03:13 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "pipex.h"
#include "libft.h"
#include "common.h"

void	pipex(t_pipex_tab *tab)
{
	int	i;
	int	fd_in;
	int	fd_out;

	i = 0;
	while (i < tab->cmd_cnt)
	{
		fd_in = tab->infile;
		fd_out = tab->outfile;
		if (i < (tab->cmd_cnt - 1) && pipe(tab->pipefd[i]) == -1)
		{
			free_pipex_table(tab);
			exit(ERROR_INIT_PIPE_FAILED);
		}
		if (i != 0)
			fd_in = tab->pipefd[i - 1][0];
		if (i < tab->cmd_cnt - 1)
			fd_out = tab->pipefd[i][1];
		create_proc(fd_in, fd_out, i, tab);
		// here to close pipe
		i++;
	}
	// here close all pipe elm
	// here loop all waitpid 
}

void	init_pipefd(t_pipex_tab *tab)
{
	int	i;

	tab->pipefd = (int **)malloc(sizeof(int *) * (tab->cmd_cnt - 1));
	if (!tab->pipefd)
	{
		free_pipex_table(tab);
		exit(ERROR_MEM_ALLOC_FAILED);
	}
	i = 0;
	while (i < (tab->cmd_cnt - 1))
	{
		tab->pipefd[i] = (int *)malloc(sizeof(int) * 2);
		if (!tab->pipefd[i])
		{
			free_pipex_table(tab);
			exit(ERROR_MEM_ALLOC_FAILED);
		}
		tab->pipe_cnt = ++i;
	}
}

void	init_pipex_table(int argc, char **argv, char **envp, t_pipex_tab *tab)
{
	int		i;
	char	**full_cmd;

	tab->cmd_list = malloc(sizeof(t_cmd) * (argc - 3));
	if (!tab->cmd_list)
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
	init_pipefd(tab);
	tab->envp = envp;
}

int	main(int argc, char **argv, char **envp)
{
	t_error_code	error_code;
	t_pipex_tab		*tab;

	error_code = check_input(argc, argv, envp, TRUE);
	if (error_code != ERROR_NONE)
		exit(error_code);
	tab = malloc(sizeof(t_pipex_tab) * 1);
	if (!tab)
		exit(ERROR_MEM_ALLOC_FAILED);
	init_pipex_table(argc, argv, envp, tab);
	print_pipx_table(tab);
	pipex(tab);
	free_pipex_table(tab);
	exit(ERROR_NONE);
}
