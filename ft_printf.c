/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegendr <tlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:05:09 by tlegendr          #+#    #+#             */
/*   Updated: 2024/04/10 14:02:10 by tlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_nbr_unsigned(unsigned long n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		write(1, "-", 1);
		count++;
		n = -n;
	}
	if (n >= 10)
	{
		count += ft_print_nbr_unsigned(n / 10);
		count += ft_print_nbr_unsigned(n % 10);
	}
	else
	{
		n = n + '0';
		write(1, &n, 1);
		count++;
	}
	return (count);
}

int	ft_print_nbr(int nb)
{
	int		count;
	long	n;

	n = nb;
	count = 0;
	if (n < 0)
	{
		write(1, "-", 1);
		count++;
		n = -n;
	}
	if (n >= 10)
	{
		count += ft_print_nbr(n / 10);
		count += ft_print_nbr(n % 10);
	}
	else
	{
		n = n + '0';
		write(1, &n, 1);
		count++;
	}
	return (count);
}

int	process_large_arg( const char str, va_list ap)
{
	int		count;
	int		char_arg;
	char	*arg;

	count = 0;
	if (str == 'c')
	{
		char_arg = va_arg(ap, int);
		write(1, &char_arg, 1);
		return (1);
	}
	else if (str == 's')
	{
		arg = va_arg(ap, char *);
		if (!arg)
		{
			write(1, "(null)", 6);
			return (6);
		}
		while (arg[count])
			write(1, &arg[count++], 1);
	}
	return (count);
}

int	parse_arg(const char str, va_list ap)
{
	int	count;

	count = 0;
	if (str == 'c' || str == 's' || str == 'p')
		return (process_large_arg(str, ap));
	else if (str == 'd')
		count = ft_print_nbr(va_arg(ap, int));
	else if (str == 'i')
		count = ft_print_nbr(va_arg(ap, int));
	else if (str == 'u')
		count = ft_print_nbr_unsigned(va_arg(ap, unsigned int));
	else if (str == '%')
	{
		write(1, "%", 1);
		count++;
	}
	else
		return (0);
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		len;

	i = 0;
	len = 0;
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += parse_arg(str[i + 1], ap);
			i++;
		}
		else
		{
			write(1, &str[i], 1);
			len++;
		}
		i++;
	}
	va_end(ap);
	return (len);
}
