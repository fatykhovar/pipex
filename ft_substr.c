/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbathe <bbathe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 18:31:03 by bbathe            #+#    #+#             */
/*   Updated: 2021/10/11 14:35:26 by bbathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*sub(int i, int j, char **s)
{
	int		k;
	int		len;
	char	*sub;

	len = 0;
	k = j;
	while (s[i][k])
	{
		len++;
		k++;
	}
	sub = malloc(len + 1);
	k = 0;
	while (s[i][j])
	{
		sub[k] = s[i][j];
		k++;
		j++;
	}
	sub[j] = '\0';
	return (sub);
}

char	*ft_substr(char **s, char *start)
{
	int		i;
	int		j;

	i = 0;
	if (s == 0)
		return (0);
	while (s[i])
	{
		j = 0;
		while (s[i][j])
		{
			while (start[j] && s[i][j] == start[j])
				j++;
			if (!start[j])
				return (sub(i, j, s));
			else
				break ;
		}
		i++;
	}
	return (0);
}
