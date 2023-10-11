/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 14:16:35 by lyeh              #+#    #+#             */
/*   Updated: 2023/09/11 16:26:14 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	_count_word(char const *s, char c)
{
	int	count;
	int	has_meet_word;

	count = 0;
	has_meet_word = 0;
	while (s && *s)
	{
		if (*s == c && has_meet_word)
		{
			has_meet_word = 0;
			count++;
		}
		else if (*s != c)
			has_meet_word = 1;
		s++;
	}
	if (has_meet_word)
		count++;
	return (count);
}

static int	_safe_copy(char **splitted_arr, int arr_idx, char *word)
{
	int		i;

	if (!word)
	{
		i = 0;
		while (i < arr_idx)
			free(splitted_arr[i++]);
		free(splitted_arr);
		return (0);
	}
	splitted_arr[arr_idx] = word;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char		**ret;
	int			start;
	size_t		i;
	size_t		j;

	start = -1;
	i = 0;
	j = 0;
	ret = (char **)malloc(sizeof(char *) * (_count_word(s, c) + 1));
	if (!s || !ret)
		return (NULL);
	while (i <= ft_strlen(s) && _count_word(s, c) > 0)
	{
		if (s[i] != c && start == -1)
			start = i;
		else if (start > -1 && (s[i] == c || i == ft_strlen(s)))
		{
			if (!(_safe_copy(ret, j++, ft_substr(s, start, i - start))))
				return (NULL);
			start = -1;
		}
		i++;
	}
	ret[j] = NULL;
	return (ret);
}
