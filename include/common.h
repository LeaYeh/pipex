/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:44:18 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/12 18:44:37 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

# define TRUE 1
# define FALSE 0

typedef struct s_cmd
{
	char	**full_cmd;
	char	*exec_cmd;
}	t_cmd;

typedef struct s_pipex_tab
{
	int		infile;
	int		outfile;
	t_cmd	*cmd_list;
	int		**pipefd;
	char	**envp;
	int		cmd_cnt;
}	t_pipex_tab;

void	safe_free(void **buf, size_t elm_size);
void	free_array(void **arr, int count, size_t elm_size);
void	free_cmd_list(t_cmd *cmd_list, int len);
void	free_pipex_table(t_pipex_tab *tab);

char	*extract_env(char **envp, char *env);
char	*get_exec_path(char *cmd, char **envp);
int		get_array_len(void **arr);

#endif
