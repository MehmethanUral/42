/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mural <mural@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 13:47:18 by mural             #+#    #+#             */
/*   Updated: 2026/11/26 02:50:00 by mural            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_format(char c, va_list *args)
{
	int	count;

	count = 0;
	if (c == 'c')
		count = ft_print_char(va_arg(*args, int));
	else if (c == 's')
		count = ft_print_str(va_arg(*args, char *));
	else if (c == 'p')
		count = ft_print_ptr(va_arg(*args, void *));
	else if (c == 'd' || c == 'i')
		count = ft_print_nbr(va_arg(*args, int));
	else if (c == 'u')
		count = ft_print_unnbr(va_arg(*args, unsigned int));
	else if (c == 'x' || c == 'X')
		count = ft_print_hex(va_arg(*args, unsigned int), c);
	else if (c == '%')
		count = ft_print_char('%');
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	int		i;

	va_start(args, format);
	count = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			count += ft_format(format[i], &args);
		}
		else
			count += ft_print_char(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}
