/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbathe <bbathe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 18:20:32 by bbathe            #+#    #+#             */
/*   Updated: 2021/10/11 14:35:36 by bbathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_p
{
	char	**mypaths;
	char	**mycmdargs;
	int		fdin;
	int		fdout;
}	t_p;

char	*sub(int i, int j, char **s);
char	*ft_substr(char **s, char *start);
char	**ft_split_for_paths(char const *s, char c);
char	**ft_split_for_args(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *str);
int		ft_strncmp(const char *s1, const char *s2);
void	path_parsing(t_p *p, char **envp);
char	*cmd_parsing(char *s);
void	exec_cmd(t_p *p, char *argv, char **envp);

#endif