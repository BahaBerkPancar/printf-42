/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpancar <bpancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:15:33 by bpancar           #+#    #+#             */
/*   Updated: 2024/11/07 04:40:55 by bpancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_pointer(unsigned long p, int a)
{
	int	i;

	i = 0;
	if (p == '\0')
	{
		i += ft_putstr("(nil)");
		return (i);
	}
	if (a == 0)
	{
		i += ft_putstr("0x");
		a = 1;
	}
	if (p >= 16)
		i += ft_pointer(p / 16, a);
	if ((p % 16) < 10)
		i += ft_putchar((p % 16) + '0');
	else
		i += ft_putchar((p % 16) + 87);
	return (i);
}

int	ft_check_type(char c, va_list arg)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += ft_putchar(va_arg(arg, int));
	else if (c == 's')
		count += ft_putstr(va_arg(arg, char *));
	else if (c == 'd' || c == 'i')
		count += ft_putnbr(va_arg(arg, int));
	else if (c == 'u')
		count += ft_printf_unsigned(va_arg(arg, unsigned int));
	else if (c == '%')
		count += ft_putchar('%');
	else if (c == 'p')
	{
		count += ft_pointer(va_arg(arg, unsigned long), 0);
	}
	else if (c == 'x' || c == 'X')
		count += ft_hexa(va_arg(arg, int), c);
	else
		count += ft_putchar(va_arg(arg, int));
	return (count);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		count;
	va_list	a;

	count = 0;
	i = 0;
	va_start(a, str);
	while (str[i])
	{
		if (str[i] != '%')
		{
			ft_putchar(str[i]);
			count++;
		}
		if (str[i] == '%')
		{
			i += 1;
			while (str[i] == ' ' && str[i])
				i++;
			count += ft_check_type(str[i], a);
		}
		i++;
	}
	return (count);
}
