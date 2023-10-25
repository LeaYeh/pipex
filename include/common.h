/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:44:18 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/24 12:43:03 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <ctype.h>

typedef struct s_cmd
{
	char	*exec_cmd;
	char	**full_cmd;
}	t_cmd;

typedef struct s_pipex_tab
{
	int		pipefd[2];
	int		infile;
	int		outfile;
	int		fd_in;
	int		fd_out;
	int		prev_read_end;
	t_cmd	*cmd_list;
	char	**envp;
	int		cmd_cnt;
	int		*child_pid_list;
}	t_pipex_tab;

void	safe_free(void **buf);
void	safe_close(int *fd);
void	free_array(void **arr, int count);
void	free_cmd_list(t_cmd *cmd_list, int len);
void	free_pipex_table(t_pipex_tab *tab);

char	*extract_env(char **envp, char *env);
char	*get_exec_path(char *cmd, char **envp);
void	set_cmd_params(t_cmd *cmd, char **full_cmd, char **envp);
int		get_array_len(void **arr);

void	create_proc(t_pipex_tab *tab, int cur_idx);

#endif
