/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:19:02 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/19 17:22:04 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_format(int fd, char type, va_list *args)
{
	int	ret;

	ret = 0;
	if (type == '%')
		ret = ft_print_char(fd, '%');
	else if (type == 'c')
		ret = ft_print_char(fd, va_arg(*args, int));
	else if (type == 's')
		ret = ft_print_string(fd, va_arg(*args, char *));
	else if (type == 'd' || type == 'i')
		ret = ft_print_int(fd, va_arg(*args, int));
	else if (type == 'u')
		ret = ft_print_uint(fd, va_arg(*args, unsigned int));
	else if (type == 'p')
		ret = ft_print_addr(fd, va_arg(*args, unsigned long int));
	else if (type == 'x')
		ret = ft_print_hex(fd, va_arg(*args, unsigned int), false);
	else if (type == 'X')
		ret = ft_print_hex(fd, va_arg(*args, unsigned int), true);
	else
	{
		ret += ft_print_char(fd, '%');
		ret += ft_print_char(fd, type);
	}
	return (ret);
}

bool	ft_has_subset(const char *s, const char *subset)
{
	int	i;
	int	j;

	if (!s || !subset)
		return (false);
	i = 0;
	while (s[i])
	{
		j = 0;
		while (subset[j])
		{
			if (s[i] == subset[j])
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}

int	ft_printf_helper(int fd, const char *fmt, va_list *args)
{
	const char	*formatters = "udicsupxX%";
	int			ret;
	int			i;

	i = 0;
	ret = 0;
	while (i < (int)ft_strlen(fmt))
	{
		if (fmt[i] == '%')
		{
			i++;
			if (!ft_has_subset(fmt + i, formatters))
			{
				ret += ft_print_char(fd, '%');
				ret += ft_print_char(fd, fmt[i]);
			}
			else
				ret += ft_print_format(fd, fmt[i], args);
		}
		else
			ret += ft_print_char(fd, fmt[i]);
		i++;
	}
	return (ret);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	args;
	int		ret;

	if (!format)
		return (-1);
	va_start(args, format);
	ret = ft_printf_helper(fd, format, &args);
	va_end(args);
	return (ret);
}
