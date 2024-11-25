/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhaciogl <hhaciogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:40:25 by hhaciogl          #+#    #+#             */
/*   Updated: 2024/11/25 17:56:03 by hhaciogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stddef.h>
#include "ft_printf.h"
#include <stdlib.h>

static	int	_get_hex(unsigned int num, int isx)
{
	char	*hex_s;
	char	*hex_b;
	int		size;

	hex_s = "0123456789abcdef";
	hex_b = "0123456789ABCDEF";
	size = 0;
	if (num < 16)
	{
		if (isx)
			ft_putchar_fd(hex_s[num], 1);
		else
			ft_putchar_fd(hex_b[num], 1);
		size += 1;
	}
	else
	{
		size += _get_hex(num / 16, isx);
		size += _get_hex(num % 16, isx);
	}
	return (size);
}

static	int	_get_ptr(void *num)
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

static	void	_get_ptr_with_ox(unsigned long a, size_t *j)
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

static	int	_free_with_return(int output, int n, ...)
{
	va_list	arg_list;

	va_start(arg_list, n);
	while (n--)
		free(va_arg(arg_list, void *));
	return (output);
}

static	int	_get_unsigned_int(unsigned int z, size_t *j)
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

static	int	_get_int(int intm, size_t *j)
{
	char	*str;

	str = ft_itoa(intm);
	if (str == NULL)
		return (-1);
	ft_putstr_fd(str, 1);
	*j += ft_strlen(str) - 2;
	free(str);
	return (0);
}

static	int	_get_str(char *str, size_t *j)
{
	ft_putstr_fd(str, 1);
	if (str != NULL)
		*j += ft_strlen(str) - 2;
	else
		return (-1);
	return (0);
}

static	void	_get_char(int c, size_t *j)
{
	ft_putchar_fd(c, 1);
	*j -= 1;
}


int	ft_printf(const char *format, ...)
{
	va_list				arg_list;
	size_t				i;
	size_t				j;
	int					is_f;

	i = 0;
	j = 0;
	is_f = 0;
	va_start(arg_list, format);
	while (format[i])
	{
		if (is_f)
		{
			if (format[i] == 'p')
				_get_ptr_with_ox(va_arg(arg_list, unsigned long), &j);
			else if (format[i] == 'X')
				j += _get_hex(va_arg(arg_list, unsigned int), 0) - 2;
			else if (format[i] == 'x')
				j += _get_hex(va_arg(arg_list, unsigned int), 1) - 2;
			else if (format[i] == 'u')
			{
				if (0 > _get_unsigned_int(va_arg(arg_list, unsigned int), &j))
					return (-1);
			}
			else if (format[i] == 'c')
				_get_char(va_arg(arg_list, int), &j);
			else if (format[i] == '%')
				_get_char(format[i], &j);
			else if (format[i] == 's')
			{
				if (0 > _get_str(va_arg(arg_list, char *), &j))
					return (-1);
			}
			else if (format[i] == 'i' || format[i] == 'd')
			{
				if (0 > _get_int(va_arg(arg_list, int), &j))
					return (-1);
			}
			else
				return (-1);
			is_f = 0;
		}
		else if (format[i] == '%')
		{
			if (format[i + 1])
				is_f = 1;
			else
				return (-1);
		}
		else
			ft_putchar_fd(format[i], 1);
		i++;
	}
	va_end(arg_list);
	return (i + j);
}
