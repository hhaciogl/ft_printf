/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhaciogl <hhaciogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:40:25 by hhaciogl          #+#    #+#             */
/*   Updated: 2024/11/23 14:23:27 by hhaciogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stddef.h>
#include "ft_printf.h"
#include <stdlib.h>

union typeholder
{
	char *s;
	int	i;
};

int	ft_printf(const char *format, ...)
{
	va_list				arg_list;
	size_t				i;
	size_t				j;
	char				*str;
	int					is_f;

	i = 0;
	j = 0;
	is_f = 0;
	va_start(arg_list, format);
	while (format[i])
	{
		if (is_f)
		{
			if (format[i] == 'c')
			{
				ft_putchar_fd(va_arg(arg_list, int), 1);
				j -= 1;
			}
			else if (format[i] == '%')
			{
				ft_putchar_fd(format[i], 1);
				j -= 1;
			}
			else if (format[i] == 's')
			{
				str = va_arg(arg_list, char *);
				ft_putstr_fd(str, 1);
				j += ft_strlen(str) - 2;
			}
			else if (format[i] == 'i' || format[i] == 'd')
			{
				str = ft_itoa(va_arg(arg_list, int));
				if (str == NULL)
					return (-1);
				ft_putstr_fd(str, 1);
				j += ft_strlen(str) - 2;
				free(str);
				str = NULL;
			}
			else
			{
				return (-1);
			}

			is_f = 0;
		}
		else if (format[i] == '%')
		{
			if (format[i+1])
				is_f = 1;
			else
				return (-1);
		}
		else
		{
			ft_putchar_fd(format[i], 1);
		}

		i++;
	}
	va_end(arg_list);
	return (i+j);
}
