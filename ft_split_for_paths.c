/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_for_paths.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbathe <bbathe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 18:11:00 by bbathe            #+#    #+#             */
/*   Updated: 2021/10/04 16:45:46 by bbathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	help_count_str(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (s[i] != c && s[i] != '\0')
		count++;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			count++;
		i++;
	}
	return (count);
}

static int	help_count(char const *s, char c)
{
	int	count;

	count = 0;
	while (s[count] != c && s[count] != '\0')
		count++;
	return (count);
}

static int	ft_free(char **res, int i)
{
	if (res[i] == 0)
	{
		while (i > 0)
		{
			free(res[i - 1]);
			i--;
		}
		free(res);
		return (0);
	}
	return (1);
}

static char	**help(char const *s, char c, char **res, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (s[k] != '\0')
	{
		if (s[k] != c)
		{
			res[i] = malloc(help_count(&s[k], c) + 2);
			if (ft_free(res, i) == 0)
				return (0);
			j = 0;
			while (s[k] != c && s[k] != '\0')
				res[i][j++] = s[k++];
			res[i][j] = '/';
			res[i][j + 1] = '\0';
			i++;
		}
		if (s[k] != '\0')
			k++;
	}
	return (res);
}

char	**ft_split_for_paths(char const *s, char c)
{
	int		i;
	char	**res;

	i = 0;
	if (s == 0)
		return (0);
	res = malloc((help_count_str(s, c) + 1) * sizeof(char *));
	if (res == 0)
		return (0);
	res = help(s, c, res, i);
	res[help_count_str(s, c)] = 0;
	return (res);
}
