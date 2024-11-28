/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhaciogl <hhaciogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:45:10 by hhaciogl          #+#    #+#             */
/*   Updated: 2024/11/28 20:57:25 by hhaciogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "./libft/libft.h"
# include <stdarg.h>
# include <unistd.h>

int	handle_s(char *str);
int	handle_c(int c);
int	handle_d_and_i(int n, int *is_err);
int	handle_u(unsigned int n, int *is_err);
int	handle_x(unsigned int n, int x);
int	ft_printf(const char *format, ...);

#endif