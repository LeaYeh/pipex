/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 23:02:44 by lyeh              #+#    #+#             */
/*   Updated: 2023/09/22 17:01:19 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"

static size_t	_get_num_len(unsigned long num)
{
	size_t	len;

	len = 0;
	if (num == 0)
		len = 1;
	while (num > 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

char	*ft_utoa(unsigned long long_n)
{
	char	*ptr;
	size_t	len;

	len = _get_num_len(long_n);
	ptr = (char *)malloc(sizeof(char) * len + 1);
	if (!ptr)
		return (NULL);
	ptr[len] = '\0';
	if (long_n == 0)
		ptr[0] = '0';
	while (long_n != 0)
	{
		ptr[len - 1] = long_n % 10 + '0';
		long_n /= 10;
		len--;
	}
	return (ptr);
}
