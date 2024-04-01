/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 13:59:34 by tauer             #+#    #+#             */
/*   Updated: 2024/04/01 14:03:26 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

bool	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n-- > 0)
		if (*s1 != *s2 || *s1++ == '\0' || *s2++ == '\0')
			return (false);
	return (true);
}

char	*ft_strdup(const char *s)
{
	size_t len_s;
	char *str;
	char *ptr;

	len_s = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * (len_s + 1));
	if (!str)
		return (NULL);
	ptr = str;
	while (len_s-- > 0)
		*str++ = *s++;
	*str = '\0';
	return (ptr);
}
