/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhaciogl <hhaciogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:40:25 by hhaciogl          #+#    #+#             */
/*   Updated: 2024/11/25 01:16:34 by hhaciogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stddef.h>
#include "ft_printf.h"
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

static int get_hex(unsigned int num, int isx)
{
    char    *hex_s;
    char    *hex_b;
    int     size;

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
        size += get_hex(num/16, isx);
        size += get_hex(num%16, isx);
    }
    return (size);
}

static int get_ptr(void *num)
{
    int size;
    unsigned long ulnum;
    char *hex;

    size = 0;
    hex = "0123456789abcdef";
    ulnum = (unsigned long)num;

    if (ulnum < 16)
    {
        ft_putchar_fd(hex[ulnum],1);
        size += 1;
    }
    else
    {
        size += get_ptr((void *)(ulnum/16));
        size += get_ptr((void *)(ulnum%16));
    }

    return (size);
}

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
            if (format[i] == 'p')
            {   
                unsigned long a = (unsigned long)va_arg(arg_list, void *);
                if (a != 0)
                {
                    ft_putstr_fd("0x", 1);
                    j += get_ptr((void *)a);
                }
                else
                {
                    ft_putstr_fd("(nil)",1);
                    j += 3;
                }

            }
            else if (format[i] == 'X')
            {
                j += get_hex(va_arg(arg_list, unsigned int), 0) - 2;
            }
            else if (format[i]== 'x')
            {
               j += get_hex(va_arg(arg_list, unsigned int), 1) - 2;
            }
			else if (format[i] == 'u')
			{
				unsigned int a = va_arg(arg_list, unsigned int);
				unsigned int b = a % 10000;
				a = a / 10000;
                if (a != 0)
				    str = ft_itoa(a);
                else
                    str=ft_strdup("");
				char *str2 = ft_itoa(b);
				char *new_str = ft_strjoin(str, str2);
				if (new_str == NULL)
					return (-1);
				ft_putstr_fd(new_str, 1);
				j += ft_strlen(new_str) - 2;
				free(str);
				free(str2);
				free(new_str);
				str = NULL;	
			}
			else if (format[i] == 'c')
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
				int a = va_arg(arg_list, int);
				str = ft_itoa(a);
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
