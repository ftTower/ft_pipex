/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 00:19:43 by tauer             #+#    #+#             */
/*   Updated: 2024/03/28 00:20:59 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_pipex.h"

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
	while (n > 0)
	{
		if (*s1 != *s2 || *s1 == '\0' || *s2 == '\0')
			return (false);
		s1++;
		s2++;
		n--;
	}
	return (true);
}

int	is_sep(char c, char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (1);
		charset++;
	}
	return (0);
}

int	count_words(char *str, char *charset, int i, int ret)
{
	while (str[i + 1])
	{
		if (is_sep(str[i], charset) && !is_sep(str[i + 1], charset))
			ret++;
		else if (i == 0 && !is_sep(str[i], charset))
			ret++;
		i++;
	}
	return (ret);
}

char	*mal_next_str(char *str, char *charset, int *ptr)
{
	int		len;
	char	*dup;

	len = 0;
	while (is_sep(str[*ptr], charset) && str[*ptr])
		(*ptr)++;
	while (!is_sep(str[*ptr], charset) && str[*ptr])
	{
		(*ptr)++;
		len++;
	}
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	(*ptr) -= len;
	len = 0;
	while (!is_sep(str[*ptr], charset) && str[*ptr])
	{
		dup[len] = str[*ptr];
		(*ptr)++;
		len++;
	}
	dup[len] = '\0';
	return (dup);
}

char	**inoutput_split(char *str, char *charset)
{
	char	**tab;
	int		i;
	int		pos;
	int		count;

	i = 0;
	pos = 0;
	count = count_words(str, charset, 0, 0);
	tab = (char **)malloc(sizeof(char *) * (count + 1));
	if (!(tab))
		return (NULL);
	while (i < count)
	{
		pos = 0;
		tab[i] = mal_next_str(str, charset, &pos);
		str += pos;
		i++;
	}
	tab[i] = 0;
	return (tab);
}

char	**ft_split(char *str, char *charset)
{
	char	**tab_split;

	if (!(str))
		return (NULL);
	tab_split = inoutput_split(str, charset);
	return (tab_split);
}