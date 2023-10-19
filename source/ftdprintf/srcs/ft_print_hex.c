/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 22:34:50 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/19 17:15:05 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hex(int fd, unsigned int n, bool is_upper)
{
	char	*num_str;
	int		len;

	num_str = ft_utox(n, is_upper);
	len = ft_strlen(num_str);
	write(fd, num_str, len);
	free(num_str);
	return (len);
}
