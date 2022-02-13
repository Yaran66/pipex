/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 06:54:58 by wjasmine          #+#    #+#             */
/*   Updated: 2021/11/09 15:46:10 by wjasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

char	*ft_strnstr(const char *largestr, const char *smallstr, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!smallstr[i])
		return ((char *)largestr);
	while (i < n && largestr[i])
	{
		j = 0;
		while (largestr[i + j] && smallstr[j] && largestr[i + j] == smallstr[j]
			&& i + j < n)
			j++;
		if (smallstr[j] == 0)
			return ((char *)(largestr + i));
		i++;
	}
	return (0);
}
