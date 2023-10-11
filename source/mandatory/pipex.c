#include "pipex.h"

void	pipex(t_pipex_tab *tab)
{
	int **pipes_fd;
	int	pipe_idx;
	int	cmd_idx;
	int	i;

	// pipe_idx = 0;
	// i = 0;
	pipes_fd = (int **)malloc(sizeof(int *) * (tab->cmd_cnt - 1));
	if (!pipes_fd)
		exit(ERROR_MEM_ALLOC_FAILED);
	while (i < tab->cmd_cnt - 1)
	{
		pipes_fd[i] = (int *)malloc(sizeof(int) * 2);
	}
	
}

void	init_pipex_table(int argc, char **argv, char **envp, t_pipex_tab *tab)
{
	int		i;
	char	**full_cmd;

	tab->cmd_list = (t_cmd *)malloc(sizeof(t_cmd) * (argc - 3));
	if (!tab->cmd_list)
		exit(ERROR_MEM_ALLOC_FAILED);
	tab->cmd_cnt = 0;
	tab->infile = open(argv[1], O_RDONLY);
	tab->outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
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
}

int	main(int argc, char **argv, char **envp)
{
	Error 	error;
	int		input_fd;
	int		output_fd;
	t_pipex_tab *tab;

	error = check_input(argc, argv, envp, FALSE);
	if (error.code != ERROR_NONE)
		error_handling(error);
	init_pipex_table(argc, argv, envp, tab);
	// pipex(argc, argv, envp);
	free_pipex_table(tab);
}