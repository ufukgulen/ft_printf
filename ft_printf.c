/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufgulen <ufgulen@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 06:51:49 by ufgulen           #+#    #+#             */
/*   Updated: 2024/02/02 14:09:44 by ufgulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <unistd.h>

static int	ft_putstr(char *str)
{
	int	len;

	len = -1;
	if (!str)
		str = "(null)";
	while (str[++len])
		if (write(1, &str[len], 1) == -1)
			return (-1);
	return (len);
}

static int	ft_itoasecond(u_int64_t n, int base, char *str, int len)
{
	int	arr[100];
	int	i;

	i = 0;
	while (n)
	{
		arr[i++] = n % base;
		n /= base;
	}
	while (i--)
	{
		if (write(1, &str[arr[i]], 1) == -1)
			return (-1);
		len++;
	}
	return (len);
}

static int	ft_itoa(u_int64_t n, int base, char *str, int mod)
{
	int	len;

	len = 0;
	if (mod == 1 && (int)n < 0)
	{
		n *= -1;
		if (write(1, "-", 1) == -1)
			return (-1);
		len++;
	}
	if (mod == 2)
	{
		if (write(1, "0x", 2) == -1)
			return (-1);
		len += 2;
	}
	if (n == 0)
	{
		if (write(1, "0", 1) == -1)
			return (-1);
		return (len + 1);
	}
	return (ft_itoasecond(n, base, str, len));
}

static int	ft_format(va_list args, char f)
{
	if (f == 'c')
		return (f = va_arg(args, int), write(1, &f, 1));
	else if (f == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (f == 'u')
		return (ft_itoa(va_arg(args, unsigned int), 10, DEC, 0));
	else if (f == 'd' || f == 'i')
		return (ft_itoa(va_arg(args, int), 10, DEC, 1));
	else if (f == 'p')
		return (ft_itoa(va_arg(args, u_int64_t), 16, HEXLOW, 2));
	else if (f == 'x')
		return (ft_itoa(va_arg(args, unsigned int), 16, HEXLOW, 0));
	else if (f == 'X')
		return (ft_itoa(va_arg(args, unsigned int), 16, HEXUP, 0));
	else if (f == '%')
		return (write(1, "%", 1));
	return (0);
}

int	ft_printf(const char *s, ...)
{
	int		len;
	int		tmp;
	va_list	args;

	len = 0;
	va_start(args, s);
	while (*s)
	{
		tmp = 1;
		if (*s == '%')
			tmp = ft_format(args, *++s);
		else if (write(1, s, 1) == -1)
			return (-1);
		s++;
		if (tmp == -1)
			return (-1);
		len += tmp;
	}
	return (va_end(args), len);
}
