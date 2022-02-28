/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 18:31:42 by wjasmine          #+#    #+#             */
/*   Updated: 2022/02/28 12:39:28 by wjasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_get_path_cmd(char *cmd)
{
	char	*tmp;
	char	*pathcmd;
	char	**paths_cmd_arr;

	while ((ft_strnstr(*environ, "PATH", 4)) == 0)
		environ++;
	paths_cmd_arr = ft_split((*environ + 5), ':');
	while (*paths_cmd_arr)
	{
		tmp = ft_strjoin(*paths_cmd_arr, "/");
		pathcmd = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(pathcmd, 0) == 0)
			return (pathcmd);
		free(pathcmd);
		paths_cmd_arr++;
	}
	return (0);
}

void	ft_execute(char *cmd)
{
	char	**cmds;
	char	*pathcmd;

	cmds = ft_split(cmd, ' ');
	pathcmd = ft_get_path_cmd(cmds[0]);
	if (!pathcmd)
	{
		write(STDERR_FILENO, "command not found: ", 19);
		write(STDERR_FILENO, cmds[0], ft_strlen(cmds[0]));
		write(STDERR_FILENO, "\n", 1);
		exit(EXIT_FAILURE);
	}
	if (execve (pathcmd, cmds, environ) == -1)
	{
		perror("execution error");
		exit(EXIT_FAILURE);
	}
}

void	ft_kid(int *fd, int fdin, char **argv)
{
	close(fd[0]);
	dup2 (fdin, STDIN_FILENO);
	dup2 (fd[1], STDOUT_FILENO);
	close(fdin);
	ft_execute(argv[2]);
}

void	ft_pipex(int fdin, int fdout, char **argv)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
	{
		perror("pipe error");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork error");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		ft_kid(fd, fdin, argv);
	else
	{
		close(fd[1]);
		dup2 (fd[0], STDIN_FILENO);
		dup2 (fdout, STDOUT_FILENO);
		close(fdout);
		ft_execute(argv[3]);
	}
	waitpid(-1, NULL, 0);
}

int	main(int argc, char **argv)
{
	int	fdin;
	int	fdout;

	if (argc != 5)
	{
		(write(STDERR_FILENO, "invalid number of arguments\n", 28));
		exit(1);
	}
	fdin = open(argv[1], O_RDONLY, 0777);
	fdout = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fdin < 0 || fdout < 0)
	{
		perror("file error");
		exit(EXIT_FAILURE);
	}
	ft_pipex (fdin, fdout, argv);
	return (0);
}
