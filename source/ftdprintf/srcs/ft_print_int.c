/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:39:03 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/19 17:13:15 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_int(int fd, int n)
{
	char	*num_str;
	int		len;

	num_str = ft_itoa(n);
	len = ft_strlen(num_str);
	write(fd, num_str, len);
	free(num_str);
	return (len);
}
