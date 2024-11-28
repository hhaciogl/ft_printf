/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _printf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhaciogl <hhaciogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 20:46:32 by hhaciogl          #+#    #+#             */
/*   Updated: 2024/11/28 20:59:27 by hhaciogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_s(char *str)
{
	if (NULL == str)
		return (write(1, "(null)", 6));
	return (write(1, str, ft_strlen(str)));
}

int	handle_c(int c)
{
	return (write(1, &c, 1));
}

int	handle_d_and_i(int n, int *is_err)
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

int	handle_u(unsigned int n, int *is_err)
{
	if (n / 10000)
	{
		return (handle_d_and_i(n / 10000, is_err)
			+ handle_d_and_i(n % 10000, is_err));
	}
	else
		return (handle_d_and_i(n % 10000, is_err));
}

int	handle_x(unsigned int n, int x)
{
	char	*hex_str;
	char	up_case;

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
