/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:45:05 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/29 16:01:57 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		waitpid(tab->child_pid_list[i], &status, 0);
}

bool	init_cmd_list(int argc, char **argv, char **envp, t_pipex_tab *tab)
{
	int		i;
	char	**full_cmd;

	tab->cmd_list = malloc(sizeof(t_cmd) * (argc - 3));
	if (!tab->cmd_list)
		return (false);
	tab->cmd_cnt = argc - 3;
	i = 0;
	while (i + 2 < argc - 1)
	{
		full_cmd = ft_split(argv[i + 2], ' ');
		if (!full_cmd)
		{
			free_cmd_list(tab->cmd_list, i);
			return (false);
		}
		tab->cmd_list[i].full_cmd = full_cmd;
		tab->cmd_list[i].exec_cmd = get_exec_path(full_cmd[0], envp);
		if (tab->cmd_list[i].exec_cmd == NULL)
			tab->cmd_list[i].exec_cmd = ft_strdup(full_cmd[0]);
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
	tab->program_name = argv[0];
	tab->infile_path = argv[1];
	tab->outfile_path = argv[argc - 1];
	tab->fd_in = -1;
	tab->fd_out = -1;
	tab->prev_read_end = -1;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex_tab		*tab;

	if (!check_input_format(argc, false))
		exit(ERROR_INVALID_INPUT);
	tab = malloc(sizeof(t_pipex_tab) * 1);
	if (!tab)
		exit(ERROR_MEM_ALLOC_FAILED);
	init_pipex_table(argc, argv, envp, tab);
	pipex(tab);
	free_pipex_table(tab);
	exit(ERROR_NONE);
}
