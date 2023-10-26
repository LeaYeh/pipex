/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 00:32:05 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/26 20:51:33 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <ctype.h>
# include "libft.h"
# include "ft_printf.h"

typedef enum s_error_code{
	ERROR_NONE = 0,
	ERROR_INVALID_INPUT,
	ERROR_INVALID_FILE,
	ERROR_INVALID_CMD,
	ERROR_INIT_PIPE_FAILED,
	ERROR_INIT_CMD_LIST_FAILED,
	ERROR_FORK_PROC_FAILED,
	ERROR_MEM_ALLOC_FAILED,
	ERROR_FD_DUP_FAILED,
	ERROR_EXEC_FAILED,
	ERROR_CLOSE_FD_FAILED
}	t_error_code;

typedef struct s_cmd
{
	char	*exec_cmd;
	char	**full_cmd;
}	t_cmd;

typedef struct s_pipex_tab
{
	char	*program_name;
	char	*infile_path;
	char	*outfile_path;
	int		pipefd[2];
	int		fd_in;
	int		fd_out;
	int		prev_read_end;
	t_cmd	*cmd_list;
	char	**envp;
	int		cmd_cnt;
	int		*child_pid_list;
}	t_pipex_tab;

bool	check_input_format(int argc, bool is_bonus);
bool	check_cmd(t_pipex_tab *tab, int cur_idx);
bool	check_file(t_pipex_tab *tab, int cur_idx);

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