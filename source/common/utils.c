/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:44:48 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/12 18:45:00 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "common.h"

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
		if (ft_strncmp(envp[i], env, env_len) != 0)
		{
			i++;
			continue ;
		}
		path = ft_strdup(envp[i] + env_len + 1);
		i++;
	}
	return (path);
}

char	*get_exec_path(char *cmd, char **envp)
{
	char	**all_path;
	char	*part_path;
	char	*exec_path;
	int		i;

	all_path = ft_split(extract_env(envp, "PATH"), ':');
	i = 0;
	while (all_path && all_path[i])
	{
		part_path = ft_strjoin(all_path[i], "/");
		exec_path = ft_strjoin(part_path, cmd);
		safe_free((void **)&part_path, sizeof(char));
		if (access(exec_path, F_OK | X_OK) == 0)
			return (exec_path);
		safe_free((void **)&exec_path, sizeof(char));
		i++;
	}
	free_array(
		(void **)all_path,
		get_array_len((void **)all_path),
		sizeof(char));
	return (NULL);
}

int	get_array_len(void **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}
