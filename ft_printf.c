/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhaciogl <hhaciogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:40:25 by hhaciogl          #+#    #+#             */
/*   Updated: 2024/11/25 20:52:06 by hhaciogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stddef.h>
#include "ft_printf.h"
#include <stdlib.h>

typedef struct s_args
{
	size_t				i;
	size_t				j;
	int					is_f;
	int					is_err;
} t_args;

static	int	_get_hex(unsigned int num, char x)
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

static	void	_get_int(int intm, size_t *j, int *is_err)
{
	char	*str;

	str = ft_itoa(intm);
	if (str == NULL)
	{
		*is_err = 1;
		return ;
	}
	ft_putstr_fd(str, 1);
	*j += ft_strlen(str) - 2;
	free(str);
}

static	void	_get_str(char *str, size_t *j)
{
	ft_putstr_fd(str, 1);
	*j += ft_strlen(str) - 2;
}

static	void	_get_char(int c, size_t *j)
{
	ft_putchar_fd(c, 1);
	*j -= 1;
}

static void _init_to_zero(t_args *ta)
{
	ta->i = 0;
	ta->j = 0;
	ta->is_err = 0;
	ta->is_f = 0;
}

static void _char_format(const char *format, size_t *i, int *is_f, int *is_err)
{
	if (format[(*i + 1)] == '\0')
		*is_f = 1;
	else
		*is_err = 1;
}

static void _loop(const char *format, t_args *ta, va_list arg_list)
{
	while (format[ta->i] && !ta->is_err)
	{
		if (ta->is_f)
		{
			if (format[ta->i] == 'p')
				_get_ptr_with_ox(va_arg(arg_list, unsigned long), &ta->j);
			else if (format[ta->i] == 'X' || format[ta->i] == 'x')
				ta->j += _get_hex(va_arg(arg_list, unsigned), format[ta->i]) - 2;
			else if (format[ta->i] == 'c')
				_get_char(va_arg(arg_list, int), &ta->j);
			else if (format[ta->i] == '%')
				_get_char(format[ta->i], &ta->j);
			else if (format[ta->i] == 's')
				_get_str(va_arg(arg_list, char *), &ta->j);
			else if (format[ta->i] == 'i' || format[ta->i] == 'd')
				_get_int(va_arg(arg_list, int), &ta->j, &ta->is_err);
			else if (format[ta->i] == 'u')
			{
				if (0 > _get_unsigned_int(va_arg(arg_list, unsigned), &ta->j))
					ta->is_err = 1;
			}
			else
				ta->is_err = 1;
			ta->is_f = 0;
		}
		else if (format[ta->i] == '%')
			_char_format(format, &ta->i, &ta->is_err, &ta->is_f);
		else
			ft_putchar_fd(format[ta->i], 1);
		ta->i++;
	}
}

int	ft_printf(const char *format, ...)
{
	va_list	arg_list;
	t_args	ta;		

	_init_to_zero(&ta);
	va_start(arg_list, format);
	_loop(format, &ta, arg_list);
	va_end(arg_list);
	if (ta.is_err)
		return (-1);
	return (ta.i + ta.j);
}
