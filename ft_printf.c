/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhaciogl <hhaciogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:40:25 by hhaciogl          #+#    #+#             */
/*   Updated: 2024/11/28 19:27:47 by hhaciogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "./libft/libft.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>




int handle_s(char *str)
{

	if (NULL == str)
		return (write(1, "(null)", 6));
	return (write(1, str, ft_strlen(str)));
}

int handle_c(int c)
{
	return (write(1, &c, 1));
}

int handle_d_and_i(int n, int *is_err)
{
	char	*str;
	int		count;

	str = ft_calloc(1, 20);
	if (NULL == str)
	{
		*is_err = -1;
		return (-1);
	}
	ft_strlcpy(str, ft_itoa(n), 20);
	count = handle_s(str);
	free(str);
	return (count);
}

int handle_u(unsigned n, int *is_err)
{
	if (n / 10000)
		return (handle_d_and_i(n / 10000, is_err) +
			handle_d_and_i(n % 10000, is_err));
	else
		return (handle_d_and_i(n % 10000, is_err));
}

int handle_x(unsigned n, int x)
{
	char *hex_str;
	char up_case;
	
	hex_str = "0123456789abcdef";
	if (16 > n)
	{
		if (x)
			return (write(1, &hex_str[n], 1));
		else
		{
			up_case = ft_toupper(hex_str[n]);
			return (write(1, &up_case, 1));
		}		
	}
	else
	{
		if (x)
			return (handle_x(n / 16, x) + write(1, &hex_str[n % 16], 1));
		else
		{
			up_case = ft_toupper(hex_str[n % 16]);
			return (handle_x(n / 16, x) + write(1, &up_case, 1));
		}
			
	}
}


static int handle_formats(char *a, va_list lst_ptr, int *is_err)
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
	else
	{
		*is_err = -1;
		return (-1);
	}
}


static int _printf(const char *fmt, va_list lst_ptr, int *is_err)
{
	char *chr;
	
	if (fmt == NULL || 0 > *is_err )
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
		return (write(1, fmt, chr-fmt) + handle_formats(chr + 1, lst_ptr, is_err) + _printf(chr + 2, lst_ptr, is_err));
}


int	ft_printf(const char *format, ...)
{
	int	out;
	va_list lst_ptr;
	int is_err;

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
