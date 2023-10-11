#include "pipex.h"

void	create_proc(int fd_in, int fd_out, int cur_idx, t_pipex_tab *tab)
{
	pid_t	pid;
	int		i;

	if ((pid = fork()) == -1)
	{
		free_pipex_table(tab);
		exit(ERROR_FORK_PROC_FAILED);
	}
	else if (pid == 0)
	{
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		i = 0;
		while (i < cur_idx)
		{
			close(tab->pipefd[i][0]);
			close(tab->pipefd[i][1]);
			i++;
		}
		execve(
			tab->cmd_list[cur_idx].exec_cmd,
			tab->cmd_list[cur_idx].full_cmd, tab->envp);
		free_pipex_table(tab);
		exit(ERROR_EXEC_FAILED);
	}
}

void	pipex(t_pipex_tab *tab)
{
	int	i;
	int	fd_in;
	int	fd_out;

	i = 0;
	while (i < tab->cmd_cnt)
	{
		if (i < tab->pipe_cnt)
		{
			if (pipe(tab->pipefd[i]) == -1)
			{
				free_pipex_table(tab);
				exit(ERROR_INIT_PIPE_FAILED);
			}
		}
		fd_in = (i == 0) ? tab->infile : tab->pipefd[i][0];
		fd_out = (i == tab->cmd_cnt - 1) ? tab->outfile : tab->pipefd[i][1];
		create_proc(fd_in, fd_out, i, tab);
		close(tab->pipefd[i][0]);
		close(tab->pipefd[i][1]);
		i++;
	}
}

void init_pipefd(t_pipex_tab *tab)
{
	int	i;

	tab->pipe_cnt = tab->cmd_cnt - 1;
	tab->pipefd = (int **)malloc(sizeof(int *) * tab->pipe_cnt);
	if (!tab->pipefd)
		exit(ERROR_MEM_ALLOC_FAILED);
	i = 0;
	while (i < tab->pipe_cnt)
	{
		tab->pipefd[i] = (int *)malloc(sizeof(int) * 2);
		if (!tab->pipefd[i])
		{
			free_pipex_table(tab);
			exit(ERROR_MEM_ALLOC_FAILED);
		}
		i++;
	}
}

void	init_pipex_table(int argc, char **argv, char **envp, t_pipex_tab *tab)
{
	int		i;
	char	**full_cmd;

	tab->cmd_list = (t_cmd *)malloc(sizeof(t_cmd) * (argc - 3));
	if (!tab->cmd_list)
		exit(ERROR_MEM_ALLOC_FAILED);
	tab->cmd_cnt = argc - 3;
	i = 0;
	while (i + 2 < argc - 1)
	{
		full_cmd = ft_split(argv[i + 2], ' ');
		if (!full_cmd)
		{
			free_cmd_list(tab->cmd_list, i + 1);
			exit(ERROR_MEM_ALLOC_FAILED);
		}
		tab->cmd_list[i].full_cmd = full_cmd;
		tab->cmd_list[i].exec_cmd = get_exec_path(full_cmd[0], envp);
		i++;
	}
	tab->infile = open(argv[1], O_RDONLY);
	tab->outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
	tab->pipe_cnt = tab->cmd_cnt - 1;
	init_pipefd(tab);
	tab->envp = envp;
}

int	main(int argc, char **argv, char **envp)
{
	Error 	error;
	t_pipex_tab *tab;

	error = check_input(argc, argv, envp, FALSE);
	if (error.code != ERROR_NONE)
		error_handling(error);
	tab = NULL;
	init_pipex_table(argc, argv, envp, tab);
	pipex(tab);
	free_pipex_table(tab);
	exit(ERROR_NONE);
}
