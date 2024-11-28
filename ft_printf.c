/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhaciogl <hhaciogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:40:25 by hhaciogl          #+#    #+#             */
/*   Updated: 2024/11/28 16:59:10 by hhaciogl         ###   ########.fr       */
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

int handle_d(int n, int *is_err)
{
	char *str;
	int		count;

	str = ft_calloc(1, sizeof(int));
	if (NULL == str)
	{
		*is_err = -1;
		return (-1);
	}
	ft_strlcpy(str, ft_itoa(n), sizeof(int));
	count = handle_s(str);
	free(str);
	return (count);
}

static int handle_formats(char *a, va_list lst_ptr, int *is_err)
{

	if ('s' == *a)
	{
		return (handle_s(va_arg(lst_ptr, char *)));
	}
	if ('c' == *a)
		return (handle_c(va_arg(lst_ptr, int)));
	else
	{
		*is_err = 1;
		return (-1);
	}
}


static int _printf(const char *fmt, va_list lst_ptr, int *is_err)
{
	char *chr;
	
	is_err = 0;
	if (fmt == NULL || 0 > is_err )
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
	else if (NULL == chr+1)
	{
		return (-1);
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
	return (out);
}
