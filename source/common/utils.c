/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:44:48 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/26 21:02:24 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*extract_env(char **envp, char *env)
{
	int		i;
	int		env_len;
	char	*path;

	path = NULL;
	env_len = ft_strlen(env);
	if (!env_len || !envp)
		return (path);
	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], env, env_len) == 0)
		{
			path = ft_strdup(envp[i] + env_len + 1);
			break ;
		}
		i++;
	}
	return (path);
}

void	set_cmd_params(t_cmd *cmd, char **full_cmd, char **envp)
{
	cmd->full_cmd = full_cmd;
	cmd->exec_cmd = get_exec_path(full_cmd[0], envp);
	if (cmd->exec_cmd == NULL)
		cmd->exec_cmd = full_cmd[0];
}

char	*get_exec_path(char *cmd, char **envp)
{
	char	**all_path;
	char	*part_path;
	char	*exec_path;
	int		i;

	if (ft_strchr(cmd, '/') && access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	exec_path = extract_env(envp, "PATH");
	all_path = ft_split(exec_path, ':');
	safe_free((void **)&exec_path);
	i = 0;
	while (all_path && all_path[i])
	{
		part_path = ft_strjoin(all_path[i], "/");
		exec_path = ft_strjoin(part_path, cmd);
		safe_free((void **)&part_path);
		if (access(exec_path, F_OK) == 0)
			break ;
		safe_free((void **)&exec_path);
		i++;
	}
	free_array((void **)all_path, -1);
	return (exec_path);
}

int	get_array_len(void **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

char	*get_base_filename(char	*full_name)
{
	char	*ret;
	char	**tmp;

	tmp = ft_split(full_name, '/');
	if (!tmp)
		return (NULL);
	ret = ft_strdup(tmp[get_array_len((void **)tmp) - 1]);
	return (ret);
}
