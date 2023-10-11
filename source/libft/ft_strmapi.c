/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 15:29:22 by lyeh              #+#    #+#             */
/*   Updated: 2023/09/10 15:37:35 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			src_len;
	char			*ptr;
	unsigned int	i;

	if (s)
	{
		src_len = ft_strlen(s);
		if (src_len == 0)
			return (ft_strdup(""));
		ptr = (char *)malloc(sizeof(char) * src_len + 1);
		if (!ptr)
			return (NULL);
		i = 0;
		while (s[i])
		{
			ptr[i] = (*f)(i, (char)s[i]);
			i++;
		}
		ptr[i] = '\0';
		return (ptr);
	}
	return (NULL);
}
