/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 22:38:23 by marvin            #+#    #+#             */
/*   Updated: 2024/04/23 23:23:52 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	ft_strnset(char *str, char c, int n)
{
	while (--n >= 0)
		str[n] = c;
}

char	*ft_stralloc(int len, char c)
{
	char	*out;

	out = malloc(len);
	if (!out)
		return (0);
	while (--len >= 0)
		out[len] = c;
	return (out);
}

void	gnlwatch(int fd, char **save)
{
	char	*buffer;
	int		read_len;

	if (!*save)
		*save = ft_stralloc(1, 0);
	buffer = ft_stralloc(BUFFER_SIZE + 1, 0);
	while (1)
	{
		ft_strnset(buffer, 0, BUFFER_SIZE);
		read_len = read(fd, buffer, BUFFER_SIZE);
		if (read_len <= 0)
		{
			if (ft_strlen(*save) > 0)
				break ;
			free(*save);
			*save = 0;
			break ;
		}
		ft_strmcat(save, buffer);
		if (read_len < BUFFER_SIZE)
			break ;
		if (has_char(*save, 10) != -1)
			break ;
	}
	free(buffer);
}

char	*gnlget(int fd, char **line, char **save)
{
	char	*new_save;
	int		len_save;
	int		i;

	i = 0;
	if (!*save)
		*save = ft_stralloc(1, 0);
	gnlwatch(fd, &*save);
	len_save = ft_strlen(*save);
	i = has_char(*save, 10);
	if (i == -1)
		i = len_save;
	*line = ft_substr(*save, 0, i + 1);
	len_save = ft_strlen(*save);
	if (i == len_save)
		new_save = NULL;
	else
		new_save = ft_substr(*save, i + 1, len_save - i + 1);
	if (*save)
		free(*save);
	*save = new_save;
	return (*line);
}

char	*get_next_line(int fd)
{
	static char	*saves[1024];
	char		*line;

	if (fd < 0 || fd > 1024 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
	{
		if (saves[fd])
			free(saves[fd]);
		saves[fd] = NULL;
		return (NULL);
	}
	line = NULL;
	gnlget(fd, &line, &saves[fd]);
	if (!line)
	{
		free(saves[fd]);
		saves[fd] = NULL;
	}
	return (line);
}
