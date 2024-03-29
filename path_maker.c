/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_maker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:54:46 by tauer             #+#    #+#             */
/*   Updated: 2024/03/29 13:55:14 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*result;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	result = str;
	while (*s1)
		*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
	*str = '\0';
	return (result);
}

char	*path_maker(const char *path, const char *exec_name)
{
	if (!path || !exec_name)
		return (NULL);
	return (ft_strjoin(path, exec_name));
}
