/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 13:34:02 by lyeh              #+#    #+#             */
/*   Updated: 2023/09/09 09:27:42 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needle_len;

	needle_len = ft_strlen(needle);
	if (needle_len == 0)
		return ((char *) haystack);
	if (ft_strlen(haystack) < ft_strlen(needle))
		return (NULL);
	if ((len > 0 && needle_len > len))
		return (NULL);
	i = 0;
	while ((i + needle_len) <= len)
	{
		if (ft_strncmp(haystack + i, needle, needle_len) == 0)
			return ((char *) haystack + i);
		i++;
	}
	return (NULL);
}
