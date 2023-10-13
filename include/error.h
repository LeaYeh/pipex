/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 21:42:04 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/13 12:47:40 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H
# include <stdbool.h>

typedef enum s_error_code{
	ERROR_NONE = 0,
	ERROR_INVALID_INPUT,
	ERROR_FILE_NOT_FOUND,
	ERROR_FILE_NOT_READABLE,
	ERROR_FILE_NOT_WRITABLE,
	ERROR_CMD_INVALID,
	ERROR_INIT_PIPE_FAILED,
	ERROR_FORK_PROC_FAILED,
	ERROR_MEM_ALLOC_FAILED,
	ERROR_EXEC_FAILED
}	t_error_code;

typedef struct s_error {
	t_error_code	code;
	const char		*message;
}	t_error;

void	error_handling(t_error error);
t_error	check_input(int argc, char **argv, char **envp, bool is_bonus);
t_error	check_input_format(int argc, bool is_bonus);
t_error	check_input_cmd(int argc, char **argv, char **envp);
t_error	check_input_file(int argc, char **argv);

#endif
