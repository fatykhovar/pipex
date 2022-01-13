/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbathe <bbathe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:51:24 by bbathe            #+#    #+#             */
/*   Updated: 2021/10/11 14:57:11 by bbathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	path_parsing(t_p *p, char **envp)
{
	char	*path_from_envp;

	path_from_envp = ft_substr(envp, "PATH=");
	p->mypaths = ft_split_for_paths(path_from_envp, ':');
	free(path_from_envp);
}

int	slash_check(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (-1);
		i++;
	}
	return (1);
}

char	*cmd_parsing(char *s)
{
	int		i;
	char	*cmd;

	i = 0;
	while (s[i] && s[i] != ' ')
		i++;
	cmd = malloc(i + 1);
	if (!cmd)
		return (0);
	i = 0;
	while (s[i] && s[i] != ' ')
	{
		cmd[i] = s[i];
		i++;
	}
	cmd[i] = '\0';
	printf("%s\n", cmd);
	if (slash_check(cmd) == -1)
	{
		free(cmd);
		write(STDERR_FILENO, "Command does not exist.\n", 25);
		exit(1);
	}
	return (cmd);
}

void	exec_cmd(t_p *p, char *argv, char **envp)
{
	int		i;
	char	*cmd;
	char	*path_cmd;

	i = 0;
	cmd = cmd_parsing(argv);
	p->mycmdargs = ft_split_for_args(argv, ' ');
	while (p->mypaths[i])
	{
		path_cmd = ft_strjoin(p->mypaths[i], cmd);
		if (path_cmd == 0)
		{
			write(STDERR_FILENO, "ft_strjoin error.\n", 13);
			exit(1);
		}
		if (access(path_cmd, 0) == 0)
			execve(path_cmd, p->mycmdargs, envp);
		free(path_cmd);
		i++;
	}
	if (!p->mypaths[i])
		write(STDERR_FILENO, "Command does not exist.\n", 25);
	free(cmd);
}
