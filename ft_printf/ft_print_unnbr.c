/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unnbr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mural <mural@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 13:41:15 by mural             #+#    #+#             */
/*   Updated: 2026/11/26 02:50:00 by mural            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_unnbr(unsigned int n)
{
	int	count;

	count = 0;
	if (n >= 10)
		count += ft_print_unnbr(n / 10);
	count += ft_print_char(n % 10 + '0');
	return (count);
}
