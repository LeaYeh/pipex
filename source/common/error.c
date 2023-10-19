/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:44:34 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/20 00:27:42 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "error.h"
#include "common.h"

t_error_code	check_input(int argc, char **argv, char **envp, bool is_bonus)
{
	if (!check_input_format(argc, is_bonus))
		return (ERROR_INVALID_INPUT);
	if (!check_file(argc, argv))
		return (ERROR_INVALID_FILE);
	if (!check_input_cmd(argc, argv, envp))
		return (ERROR_NONE);
	return (ERROR_NONE);
}

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

bool	check_input_cmd(int argc, char **argv, char **envp)
{
	bool	ret;
	int		i;
	char	**tmp_cmd;
	char	*exec_cmd;
	
	ret = true;
	i = 2;
	while (i < argc - 1)
	{
		tmp_cmd = ft_split(argv[i++], ' ');
		if (!tmp_cmd)
			exit(ERROR_MEM_ALLOC_FAILED);
		exec_cmd = get_exec_path(tmp_cmd[0], envp);
		if (!exec_cmd)
		{
			ft_dprintf(2, "./pipex: %s: command not found\n", tmp_cmd[0]);
			ret = false;
		}
		else if (access(exec_cmd, X_OK) != 0)
		{
			ft_dprintf(2, "./pipex: %s: Permission denied\n", tmp_cmd[0]);
			ret = false;
		}
		safe_free((void **)&exec_cmd);
		free_array((void **)tmp_cmd, -1);
	}
	return (ret);
}

bool	check_file(int argc, char **argv)
{
	bool	ret;

	ret = true;
	if (access(argv[1], F_OK) != 0)
	{
		ft_dprintf(2, "./pipex: %s: No such file or directory\n", argv[1]);
		ret = false;
	}
	else if (access(argv[1], R_OK) != 0)
	{
		ft_dprintf(2, "./pipex: %s: Permission denied\n", argv[1]);
		ret = false;
	}
	if (access(argv[argc - 1], F_OK) != 0)
		open(argv[argc - 1], O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	else if (access(argv[argc - 1], W_OK) != 0)
	{
		ft_dprintf(2, "./pipex: %s: Permission denied\n", argv[argc - 1]);
		ret = false;
	}
	return (ret);
}
