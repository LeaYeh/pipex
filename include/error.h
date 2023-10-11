/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 21:42:04 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/08 17:28:29 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H
# include "common.h"

# define MAX_MASSAGE_LEN 256;

typedef enum {
	ERROR_NONE = 0,
	ERROR_INVALID_INPUT,
	ERROR_FILE_NOT_FOUND,
	ERROR_FILE_NOT_READABLE,
	ERROR_FILE_NOT_WRITABLE,
	ERROR_CMD_INVALID,
	ERROR_INIT_PIPE_FAILED,
	ERROR_FORK_PROC_FAILED,
	ERROR_MEM_ALLOC_FAILED
} ErrorCode;

typedef struct {
    ErrorCode code;
    const char *message;
} Error;

void	error_handling(Error error);
Error	check_input(int argc, char **argv, char **envp, t_bool is_bonus);
Error	check_input_format(int argc, t_bool is_bonus);
Error	check_input_cmd(int argc, char **argv, char **envp);
Error	check_input_file(int argc, char **argv);

#endif
