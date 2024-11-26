/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _printf_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhaciogl <hhaciogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:15:31 by hhaciogl          #+#    #+#             */
/*   Updated: 2024/11/26 18:20:15 by hhaciogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdlib.h>
#include <stdarg.h>

int	_get_hex(unsigned int num, char x)
{
	char	*hex_s;
	char	*hex_b;
	int		size;

	hex_s = "0123456789abcdef";
	hex_b = "0123456789ABCDEF";
	size = 0;
	if (num < 16)
	{
		if (x == 'x')
			ft_putchar_fd(hex_s[num], 1);
		else
			ft_putchar_fd(hex_b[num], 1);
		size += 1;
	}
	else
	{
		size += _get_hex(num / 16, x);
		size += _get_hex(num % 16, x);
	}
	return (size);
}

int	_get_ptr(void *num)
{
	int				size;
	unsigned long	ulnum;
	char			*hex;

	size = 0;
	hex = "0123456789abcdef";
	ulnum = (unsigned long)num;
	if (ulnum < 16)
	{
		ft_putchar_fd(hex[ulnum], 1);
		size += 1;
	}
	else
	{
		size += _get_ptr((void *)(ulnum / 16));
		size += _get_ptr((void *)(ulnum % 16));
	}
	return (size);
}

void	_get_ptr_with_ox(unsigned long a, size_t *j)
{
	if (a != 0)
	{
		ft_putstr_fd("0x", 1);
		*j += _get_ptr((void *)a);
	}
	else
	{
		ft_putstr_fd("(nil)", 1);
		*j += 3;
	}
}

int	_free_with_return(int output, int n, ...)
{
	va_list	arg_list;

	va_start(arg_list, n);
	while (n--)
		free(va_arg(arg_list, void *));
	return (output);
}

int	_get_unsigned_int(unsigned int z, size_t *j)
{
	char			*str;
	char			*str2;
	char			*new_str;

	if (z / 10000 != 0)
	{
		str = ft_itoa((z / 10000));
		if (!str)
			return (-1);
	}	
	else
	{
		str = ft_strdup("");
		if (!str)
			return (-1);
	}
	str2 = ft_itoa((z % 10000));
	if (!str2)
		return (_free_with_return(-1, 1, str));
	new_str = ft_strjoin(str, str2);
	if (new_str == NULL)
		return (_free_with_return(-1, 2, str, str2));
	ft_putstr_fd(new_str, 1);
	*j += ft_strlen(new_str) - 2;
	return (_free_with_return(0, 3, str, str2, new_str));
}
