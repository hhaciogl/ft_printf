/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhaciogl <hhaciogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:40:25 by hhaciogl          #+#    #+#             */
/*   Updated: 2024/11/26 18:10:15 by hhaciogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	arg_list;
	t_args	ta;		

	ta.i = 0;
	ta.j = 0;
	ta.is_err = 0;
	ta.is_f = 0;
	va_start(arg_list, format);
	_loop(format, &ta, arg_list);
	va_end(arg_list);
	if (ta.is_err)
		return (-1);
	return (ta.i + ta.j);
}
