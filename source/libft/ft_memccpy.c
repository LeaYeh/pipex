/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 13:31:45 by lyeh              #+#    #+#             */
/*   Updated: 2023/09/10 15:28:12 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 
Copy no more than N bytes of SRC to DST, stopping when C is found.
Return the position in DST one byte past where C was copied, or
NULL if C was not found in the first N bytes of SRC.
*/
void	*ft_memccpy(void *dst, const void *src, int c, size_t len)
{
	const void	*ptr = ft_memchr(src, c, len);

	if (ptr == NULL)
	{
		ft_memcpy(dst, src, len);
		return (NULL);
	}
	ft_memcpy(dst, src, ptr - src + 1);
	return (dst + (ptr - src + 1));
}
