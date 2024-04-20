/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:11:10 by tauer             #+#    #+#             */
/*   Updated: 2024/04/20 19:19:43 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

int	ft_printf(const char *str, ...)
{
	va_list	arg;
	int		ret_size;
	size_t	i;

	ret_size = 0;
	i = 0;
	va_start(arg, str);
	while (str[i])
	{
		if (str[i] != '%')
			ft_putchar_len(str[i], &ret_size);
		else if (str[i + 1] != '\0' && str[i++] == '%')
			ret_size = selecter(str[i], ret_size, arg);
		i++;
	}
	va_end(arg);
	return (ret_size);
}
