/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 21:42:04 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/26 19:51:27 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H
# include <stdbool.h>

typedef enum s_error_code{
	ERROR_NONE = 0,
	ERROR_INVALID_INPUT,
	ERROR_INVALID_FILE,
	ERROR_INVALID_CMD,
	ERROR_INIT_PIPE_FAILED,
	ERROR_INIT_CMD_LIST_FAILED,
	ERROR_FORK_PROC_FAILED,
	ERROR_MEM_ALLOC_FAILED,
	ERROR_EXEC_FAILED,
	ERROR_CLOSE_FD_FAILED
}	t_error_code;

t_error_code	check_input(int argc, char **argv, char **envp, bool is_bonus);
bool			check_input_format(int argc, bool is_bonus);
bool			check_input_cmd(int argc, char **argv, char **envp);
// bool			check_file(int argc, char **argv);

#endif
