#include "../../include/common.h"
#include "../../include/pipex.h"

void	safe_free(void **buf, size_t elm_size)
{
	free(*buf);
	if (elm_size != sizeof(char))
		ft_memset(*buf, 0, elm_size);
	*buf = NULL;
}

void	free_array(void **arr, int count, size_t elm_size)
{
	int	i;

	if (arr == NULL || count <= 0)
        return ;
	i = 0;
	while (i < count)
	{
		if (arr[i])
			safe_free(&arr[i], elm_size);
		i++;
	}
	free(arr);
	arr = NULL;
}

void free_cmd_list(t_cmd *cmd_list, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		safe_free((void **)&cmd_list[i].exec_cmd, sizeof(char));
		free_array(
			(void **)cmd_list[i].full_cmd,
			get_array_len((void **)cmd_list[i].full_cmd),
			sizeof(char));
		i++;
	}
	free(cmd_list);	
}

void free_pipex_table(t_pipex_tab *tab)
{
	close(tab->infile);
	close(tab->outfile);
	free_cmd_list(tab->cmd_list, tab->cmd_cnt);
	free(tab);
}
