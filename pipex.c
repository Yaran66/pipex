#include "pipex.h"

//extern char **environ;

//int	ft_wordcount(const char *s, char c)
//{
//	int	i;
//	int	j;
//
//	i = 0;
//	j = 0;
//	while (s[i])
//	{
//		if (s[i] == c)
//			i++;
//		else if (s[i] != c)
//		{
//			j++;
//			while (s[i] != '\0' && s[i] != c)
//				i++;
//		}
//	}
//	return (j);
//}
//
//char	*ft_word_extract(char const *str, char c)
//{
//	char	*word;
//	int		i;
//
//	i = 0;
//	while (*str && *str == c)
//		str++;
//	while (str[i] && str[i] != c)
//		i++;
//	word = (char *) malloc(sizeof(char) * (i + 1));
//	if (word == 0)
//		return (0);
//	i = 0;
//	while (str[i] != 0 && str[i] != c)
//	{
//		word[i] = str[i];
//		i++;
//	}
//	word[i] = '\0';
//	return (word);
//}
//
//void	ft_free_words_ptr(int i, char **ptr)
//{
//	while (i > 0)
//	{
//		free(ptr[i - 1]);
//		i--;
//	}
//	free(ptr);
//}
//
//char	**ft_split(char const *s, char c)
//{
//	char	**splitstr;
//	int		strnbr;
//	int		i;
//
//	i = 0;
//	if (!s)
//		return (0);
//	strnbr = ft_wordcount(s, c);
//	splitstr = (char **) malloc (sizeof(char *) * (strnbr + 1));
//	if (splitstr == 0)
//		return (0);
//	while (i < strnbr)
//	{
//		while (*s && *s == c)
//			s++;
//		splitstr[i] = ft_word_extract(s, c);
//		if (splitstr == 0)
//			ft_free_words_ptr(i, splitstr);
//		while (*s && *s != c)
//			s++;
//		i++;
//	}
//	splitstr[i] = NULL;
//	return (splitstr);
//}
//
//char	*ft_strnstr(const char *largestr, const char *smallstr, size_t n)
//{
//	size_t	i;
//	size_t	j;
//
//	i = 0;
//	if (!smallstr[i])
//		return ((char *)largestr);
//	while (i < n && largestr[i])
//	{
//		j = 0;
//		while (largestr[i + j] && smallstr[j] && largestr[i + j] == smallstr[j]
//			   && i + j < n)
//			j++;
//		if (smallstr[j] == 0)
//			return ((char *)(largestr + i));
//		i++;
//	}
//	return (0);
//}
//
//size_t	ft_strlen(const char *str)
//{
//	size_t	i;
//
//	i = 0;
//	while (str[i])
//	{
//		i++;
//	}
//	return (i);
//}
//
//
//char	*ft_strjoin(char const *s1, char const *s2)
//{
//	char	*newstr;
//	int		i;
//
//	if (s1 == 0 || s2 == 0)
//		return (0);
//	newstr = malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
//	if (newstr == 0)
//		return (0);
//	i = 0;
//	while (*s1)
//	{
//		newstr[i] = *s1;
//		s1++;
//		i++;
//	}
//	while (*s2)
//	{
//		newstr[i] = *s2;
//		s2++;
//		i++;
//	}
//	newstr[i] = '\0';
//	return (newstr);
//}

char *ft_get_path_cmd(char *cmd)
{
	char *tmp;
	char *pathcmd;
	char **paths_cmd_arr;

	while((ft_strnstr(*environ, "PATH", 4)) == 0)
		environ++;
	paths_cmd_arr = ft_split((*environ + 5), ':');
	while(*paths_cmd_arr)
		{
			tmp = ft_strjoin(*paths_cmd_arr, "/");
			pathcmd = ft_strjoin(tmp, cmd);
			free(tmp);
			if(access(pathcmd, 0) == 0)
			return (pathcmd);
			free(pathcmd);
			paths_cmd_arr++;
		}
	return (0);
}

void ft_execute(char *cmd)
{
	char **cmds;
	char *pathcmd;

	cmds = ft_split(cmd, ' ');
	pathcmd = ft_get_path_cmd(cmds[0]);
	if (!pathcmd)
	{
		//perror("Your command not found");
		write(STDERR_FILENO, "command not found:", 18);
		write(STDERR_FILENO, cmds[0], ft_strlen(cmds[0]));
		write(STDERR_FILENO, "\n", 1);
		exit(EXIT_FAILURE);
	}
	execve(pathcmd, cmds, environ);

}

void ft_pipex(int fdin, int fdout, char **argv)
{
	int fd[2]; // fd for pipe
	int pid;

	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if ( pid == 0)
	{
		close(fd[0]);
		dup2 (fdin, STDIN_FILENO);
		dup2 (fd[1], STDOUT_FILENO);
//		close(fd[0]);
		close(fdin);
		ft_execute(argv[2]);
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(fd[1]);
		dup2 (fd[0], STDIN_FILENO);
		dup2 (fdout, STDOUT_FILENO);
//		close(fd[1]);
		close(fdout);
		ft_execute(argv[3]);
	}
}

int main(int argc, char **argv)
{
	int fdin;
	int fdout;

	if (argc != 5)
	{
		(write(STDERR_FILENO, "invalid number of arguments", 27));
		return (-1);
	}
	fdin = open(argv[1], O_RDONLY, 0777);
	fdout = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fdin < 0 || fdout < 0)
		return (0);
	ft_pipex (fdin, fdout, argv);
	return (0);
}
