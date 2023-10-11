/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:01:36 by lyeh              #+#    #+#             */
/*   Updated: 2023/09/10 15:28:18 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *buf1, const void *buf2, size_t len)
{
	const unsigned char	*_buf1 = (const unsigned char *) buf1;
	const unsigned char	*_buf2 = (const unsigned char *) buf2;

	if (len == 0)
		return (0);
	while (len-- > 0)
	{
		if (*_buf1 != *_buf2)
			return (*_buf1 - *_buf2);
		_buf1++;
		_buf2++;
	}
	return (0);
}
