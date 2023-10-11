/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 13:20:55 by lyeh              #+#    #+#             */
/*   Updated: 2023/09/10 13:37:21 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	_get_start_idx(char const *str, char const *set)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(set, str[i]) == NULL)
			return (i);
		i++;
	}
	return (-1);
}

static int	_get_end_idx(char const *str, char const *set)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i >= 0)
	{
		if (ft_strchr(set, str[i]) == NULL)
			return (i);
		i--;
	}
	return (-1);
}

char	*ft_strtrim(char const *str, char const *set)
{
	char	*ptr;
	int		start_pos;
	int		end_pos;

	if (!str)
		return (NULL);
	start_pos = _get_start_idx(str, set);
	end_pos = _get_end_idx(str, set);
	if (start_pos > end_pos || start_pos == -1 || end_pos == -1)
		return (ft_strdup(""));
	ptr = (char *)malloc(sizeof(char) * (end_pos - start_pos + 2));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, str + start_pos, (end_pos - start_pos + 1) + 1);
	return (ptr);
}
