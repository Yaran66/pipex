/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 12:23:34 by wjasmine          #+#    #+#             */
/*   Updated: 2021/11/07 18:26:26 by wjasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

int	ft_wordcount(const char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else if (s[i] != c)
		{
			j++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
	}
	return (j);
}

char	*ft_word_extract(char const *str, char c)
{
	char	*word;
	int		i;

	i = 0;
	while (*str && *str == c)
		str++;
	while (str[i] && str[i] != c)
		i++;
	word = (char *) malloc(sizeof(char) * (i + 1));
	if (word == 0)
		return (0);
	i = 0;
	while (str[i] != 0 && str[i] != c)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

void	ft_free_words_ptr(int i, char **ptr)
{
	while (i > 0)
	{
		free(ptr[i - 1]);
		i--;
	}
	free(ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**splitstr;
	int		strnbr;
	int		i;

	i = 0;
	if (!s)
		return (0);
	strnbr = ft_wordcount(s, c);
	splitstr = (char **) malloc (sizeof(char *) * (strnbr + 1));
	if (splitstr == 0)
		return (0);
	while (i < strnbr)
	{
		while (*s && *s == c)
			s++;
		splitstr[i] = ft_word_extract(s, c);
		if (splitstr == 0)
			ft_free_words_ptr(i, splitstr);
		while (*s && *s != c)
			s++;
		i++;
	}
	splitstr[i] = NULL;
	return (splitstr);
}
