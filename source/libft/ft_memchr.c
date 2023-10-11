/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:51:39 by lyeh              #+#    #+#             */
/*   Updated: 2023/09/10 15:28:15 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *src, int c, size_t len)
{
	const unsigned char	*_src = src;

	if (len == 0)
		return (NULL);
	while (len-- > 0)
	{
		if (*_src == (unsigned char) c)
			return ((void *) _src);
		_src++;
	}
	return (NULL);
}
