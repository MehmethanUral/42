/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mural <mural@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 13:45:50 by mural             #+#    #+#             */
/*   Updated: 2026/11/26 02:50:00 by mural            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_address(unsigned long n)
{
	int		count;
	char	*base;

	base = "0123456789abcdef";
	count = 0;
	if (n >= 16)
		count += ft_print_address(n / 16);
	count += ft_print_char(base[n % 16]);
	return (count);
}

int	ft_print_ptr(void *ptr)
{
	int	count;

	if (ptr == NULL)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	count = 0;
	count += ft_print_str("0x");
	count += ft_print_address((unsigned long)ptr);
	return (count);
}
