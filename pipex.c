/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbathe <bbathe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:46:43 by bbathe            #+#    #+#             */
/*   Updated: 2021/10/11 16:23:04 by bbathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int *end, t_p *p, char **argv, char **envp)
{
	close(end[0]);
	if (dup2(end[1], STDOUT_FILENO) < 0 || dup2(p->fdin, STDIN_FILENO) < 0)
	{
		write(STDERR_FILENO, "Dup2 child error.\n", 20);
		exit(0);
	}
	close(end[1]);
	close(p->fdin);
	close(p->fdout);
	exec_cmd(p, argv[2], envp);
	exit(1);
}

void	parent_process(int *end, t_p *p, char **argv, char **envp)
{
	int	status;

	waitpid(-1, &status, 0);
	if (dup2(end[0], STDIN_FILENO) < 0 || dup2(p->fdout, STDOUT_FILENO) < 0)
	{
		write(STDERR_FILENO, "Dup2 parent error.\n", 20);
		exit(1);
	}
	close(end[1]);
	close(end[0]);
	close(p->fdin);
	close(p->fdout);
	exec_cmd(p, argv[3], envp);
	exit(1);
}

void	pipex(t_p *p, char **argv, char **envp)
{
	int		end[2];
	pid_t	parent;

	if (pipe(end) == -1)
	{
		write(STDERR_FILENO, "Pipe error.\n", 13);
		exit(1);
	}
	parent = fork();
	if (parent < 0)
	{
		write(STDERR_FILENO, "Fork error.\n", 13);
		exit(1);
	}
	if (!parent)
		child_process(end, p, argv, envp);
	else
		parent_process(end, p, argv, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_p		*p;

	p = malloc(sizeof(t_p));
	if (argc != 5)
	{
		write(STDERR_FILENO, "Invalid number of arguments.\n", 30);
		exit(1);
	}
	p->fdin = open(argv[1], O_RDONLY, 0777);
	p->fdout = open(argv[4], O_WRONLY | O_CREAT, 0777);
	if (p->fdin == -1 || p->fdout == -1)
	{
		write(STDERR_FILENO, "Cannot open file.\n", 19);
		exit(1);
	}
	path_parsing(p, envp);
	pipex(p, argv, envp);
	free (p);
	return (0);
}
