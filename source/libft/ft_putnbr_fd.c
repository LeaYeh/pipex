/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 15:08:17 by lyeh              #+#    #+#             */
/*   Updated: 2023/09/10 15:27:13 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	_get_num_len(long num)
{
	size_t	len;

	len = 0;
	if (num == 0)
		len = 1;
	else if (num < 0)
	{
		num *= -1;
		len++;
	}
	while (num > 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

static void	_convert_to_string(long nb, char *ptr)
{
	if (nb == 0)
	{
		*ptr = '0';
		return ;
	}
	if (nb >= 10)
		_convert_to_string(nb / 10, ptr - 1);
	*ptr = nb % 10 + '0';
}

void	ft_putnbr_fd(int n, int fd)
{
	const size_t	len = _get_num_len(n);
	char			ptr[12];
	long			long_nb;

	long_nb = n;
	ptr[len] = '\0';
	if (long_nb < 0)
	{
		long_nb *= -1;
		ptr[0] = '-';
	}
	_convert_to_string(long_nb, (ptr + len - 1));
	ft_putstr_fd(ptr, fd);
}
