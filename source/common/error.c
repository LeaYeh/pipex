/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:44:34 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/26 20:17:54 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	check_input_format(int argc, bool is_bonus)
{
	if (!is_bonus && argc != 5)
	{
		ft_dprintf(2, "./pipex: infile cmd1 cmd2 outfile\n");
		return (false);
	}
	else if (is_bonus && argc < 4)
	{
		ft_dprintf(2, "./pipex: infile cmd1 ... cmd[n] outfile (n >= 1)\n");
		return (false);
	}
	return (true);
}

bool	check_cmd(t_pipex_tab *tab, int cur_idx)
{
	if (access(tab->cmd_list[cur_idx].full_cmd[0], F_OK) != 0)
	{
		ft_dprintf(2, "%s: %s: Command not found.\n",
			tab->program_name,
			tab->cmd_list[cur_idx].full_cmd[0]);
		return (false);
	}
	else if (access(tab->cmd_list[cur_idx].full_cmd[0], X_OK) != 0)
	{
		ft_dprintf(2, "%s: %s: ",
			tab->program_name,
			tab->cmd_list[cur_idx].full_cmd[0]);
		perror("");
		return (false);
	}
	return (true);
}

bool	check_file(t_pipex_tab *tab, int cur_idx)
{
	if (cur_idx == 0)
	{
		tab->fd_in = open(tab->infile_path, O_RDONLY);
		if (tab->fd_in == -1)
		{
			ft_dprintf(2, "%s: %s: ", tab->program_name, tab->infile_path);
			perror("");
			return (false);
		}
	}
	if (cur_idx == (tab->cmd_cnt - 1))
	{
		tab->fd_out = open(tab->outfile_path, O_TRUNC | O_CREAT | O_RDWR, 0644);
		if (tab->fd_out == -1)
		{
			ft_dprintf(2, "%s: %s: ", tab->program_name, tab->outfile_path);
			perror("");
			return (false);
		}
	}
	return (true);
}