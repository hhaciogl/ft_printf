/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhaciogl <hhaciogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:45:10 by hhaciogl          #+#    #+#             */
/*   Updated: 2024/11/26 18:25:32 by hhaciogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stddef.h>

typedef struct s_args
{
	size_t	i;
	size_t	j;
	int		is_f;
	int		is_err;
}	t_args;
int		_get_hex(unsigned int num, char x);
int		_get_ptr(void *num);
void	_get_ptr_with_ox(unsigned long a, size_t *j);
int		_free_with_return(int output, int n, ...);
int		_get_unsigned_int(unsigned int z, size_t *j);
void	_get_int(int intm, size_t *j, int *is_err);
void	_get_str(char *str, size_t *j);
void	_get_char(int c, size_t *j);
void	_condition(const char *format, va_list arg_list, t_args *ta);
void	_loop(const char *format, t_args *ta, va_list arg_list);
int		ft_printf(const char *format, ...);

#endif