/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:44:34 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/16 15:55:23 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "common.h"

void	error_handling(t_error error)
{
	ft_putstr_fd((char *)error.message, STDERR_FILENO);
	exit (error.code);
}

t_error	check_input(int argc, char **argv, char **envp, bool is_bonus)
{
	t_error	error;

	error = check_input_format(argc, is_bonus);
	if (error.code != ERROR_NONE)
		return (error);
	error = check_input_cmd(argc, argv, envp);
	if (error.code != ERROR_NONE)
		return (error);
	error = check_input_file(argc, argv);
	return (error);
}

t_error	check_input_format(int argc, bool is_bonus)
{
	t_error	error;

	error.code = ERROR_NONE;
	if (!is_bonus && argc != 5)
	{
		error.code = ERROR_INVALID_INPUT;
		error.message = "input format: ./pipex infile cmd cmd outfile\n";
	}
	return (error);
}

t_error	check_input_cmd(int argc, char **argv, char **envp)
{
	t_error	error;
	int		i;
	char	**tmp_cmd;
	char	*exec_cmd;

	error.code = ERROR_NONE;
	i = 2;
	while (i < argc - 1)
	{
		tmp_cmd = ft_split(argv[i++], ' ');
		if (!tmp_cmd)
			exit(ERROR_MEM_ALLOC_FAILED);
		exec_cmd = get_exec_path(tmp_cmd[0], envp);
		if (!exec_cmd)
		{
			error.code = ERROR_CMD_INVALID;
			error.message = "Command is not exist or no permission\n";
			free_array((void **)tmp_cmd, -1);
			safe_free((void **)&exec_cmd);
			return (error);
		}
		safe_free((void **)&exec_cmd);
		free_array((void **)tmp_cmd, -1);
	}
	return (error);
}

t_error	check_input_file(int argc, char **argv)
{
	t_error	error;

	error.code = ERROR_NONE;
	if (access(argv[1], F_OK) != 0 || access(argv[argc - 1], F_OK) != 0)
	{
		error.code = ERROR_FILE_NOT_FOUND;
		error.message = "File is not exist.\n";
	}
	else if (access(argv[1], R_OK) != 0)
	{
		error.code = ERROR_FILE_NOT_READABLE;
		error.message = "Input file is not readable.\n";
	}
	else if (access(argv[argc - 1], W_OK) != 0)
	{
		error.code = ERROR_FILE_NOT_WRITABLE;
		error.message = "Output file is not writable.\n";
	}
	return (error);
}
