/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _printf_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhaciogl <hhaciogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:16:03 by hhaciogl          #+#    #+#             */
/*   Updated: 2024/11/26 18:19:36 by hhaciogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdlib.h>
#include <stdarg.h>
#include "ft_printf.h"

void	_get_int(int intm, size_t *j, int *is_err)
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

void	_get_str(char *str, size_t *j)
{
	if (str == NULL)
		str = "(null)";
	ft_putstr_fd(str, 1);
	*j += ft_strlen(str) - 2;
}

void	_get_char(int c, size_t *j)
{
	ft_putchar_fd(c, 1);
	*j -= 1;
}

void	_condition(const char *format, va_list arg_list, t_args *ta)
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

void	_loop(const char *format, t_args *ta, va_list arg_list)
{
	while (format[ta->i] && !ta->is_err)
	{
		if (ta->is_f)
		{
			_condition(format, arg_list, ta);
		}
		else if (format[ta->i] == '%')
		{
			if (format[ta->i + 1])
				ta->is_f = 1;
			else
				ta->is_err = 1;
		}
		else
			ft_putchar_fd(format[ta->i], 1);
		ta->i++;
	}
}
