/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhaciogl <hhaciogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:40:25 by hhaciogl          #+#    #+#             */
/*   Updated: 2024/11/27 18:50:50 by hhaciogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "./libft/libft.h"
#include <stdarg.h>
#include <stdio.h>

int handle_str(char *str)
{
	if (str == NULL)
		return (write(1, "(null)", 6));
	return (write(1, str, ft_strlen(str)));
}


int _printf(char *fmt, va_list va_args)
{
	char	*vars;
	char	*rest_of_str;

	vars = "%s";
	//abc
	rest_of_str = ft_strnstr(fmt, vars, ft_strlen(fmt));
	if(!rest_of_str)
	{	//This is a string: %s
		return (write(1, fmt, ft_strlen(fmt)));
	}
	if (ft_strncmp(rest_of_str, "%s") == 0)
		return ;
	else
		
	// puts("==============");
	// printf("%li", rest_of_str - fmt);
	// puts("");
	// puts("==============");
	return (write(1, fmt, (rest_of_str -fmt)) + handle_str(va_arg(va_args, char *)));
}


int	ft_printf(const char *format, ...)
{
	char *fmt;
	int	out;
	va_list va_args;

	va_start(va_args, format);
	fmt = ft_strdup(format);
	if(fmt == NULL)
	{
		out = -1;
	}
	else
	{
		out = _printf(fmt, va_args);
	}
	va_end(va_args);
	return (out);
}
