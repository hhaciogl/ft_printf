/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhaciogl <hhaciogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:40:25 by hhaciogl          #+#    #+#             */
/*   Updated: 2024/11/28 20:58:14 by hhaciogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	_p(void *n)
{
	unsigned long	m;
	char			*hex_str;
	unsigned long	head;
	unsigned long	tail;

	m = (unsigned long)n;
	hex_str = "0123456789abcdef";
	head = m / 16;
	tail = m % 16;
	if (16 > m)
	{
		return (write(1, &hex_str[m], 1));
	}
	else
	{
		return (_p((void *)head) + write(1, &hex_str[tail], 1));
	}
}

static int	handle_p(void *n)
{
	if (NULL == n)
		return (write(1, "(nil)", 5));
	return (write(1, "0x", 2) + _p(n));
}

static	int	handle_formats(char *a, va_list lst_ptr, int *is_err)
{
	if ('s' == *a)
		return (handle_s(va_arg(lst_ptr, char *)));
	else if ('c' == *a)
		return (handle_c(va_arg(lst_ptr, int)));
	else if ('d' == *a)
		return (handle_d_and_i(va_arg(lst_ptr, int), is_err));
	else if ('i' == *a)
		return (handle_d_and_i(va_arg(lst_ptr, int), is_err));
	else if ('%' == *a)
		return (write(1, a, 1));
	else if ('u' == *a)
		return (handle_u(va_arg(lst_ptr, unsigned), is_err));
	else if ('x' == *a)
		return (handle_x(va_arg(lst_ptr, unsigned), 1));
	else if ('X' == *a)
		return (handle_x(va_arg(lst_ptr, unsigned), 0));
	else if ('p' == *a)
		return (handle_p(va_arg(lst_ptr, void *)));
	else
	{
		*is_err = -1;
		return (-1);
	}
}

static	int	_printf(const char *fmt, va_list lst_ptr, int *is_err)
{
	char	*chr;

	if (fmt == NULL || 0 > *is_err)
		return (-1);
	if (ft_strncmp(fmt, "", 1) == 0)
	{		
		return (0);
	}
	chr = ft_strchr(fmt, '%');
	if (NULL == chr)
	{
		return (write(1, fmt, ft_strlen(fmt)));
	}
	else
		return (write(1, fmt, chr - fmt)
			+ handle_formats(chr + 1, lst_ptr, is_err)
			+ _printf(chr + 2, lst_ptr, is_err));
}

int	ft_printf(const char *format, ...)
{
	int		out;
	va_list	lst_ptr;
	int		is_err;

	is_err = 0;
	va_start(lst_ptr, format);
	out = _printf(format, lst_ptr, &is_err);
	va_end(lst_ptr);
	if (0 > is_err)
	{
		return (-1);
	}
	return (out);
}
