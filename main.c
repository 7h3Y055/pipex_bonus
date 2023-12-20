#include "pipex_bonus.h"

int main(int argc, char **argv, char **envp)
{
    int i;
    int in;
	int fd[2];
	t_utilis	pipex;

	i = 2;
	init_t_utilis(&pipex, argc, argv, envp);
	pipe(fd);
	child(&pipex, argv[i++], pipex.infile_fd , fd[1]);
	while (i < argc - 2)
	{
		in = fd[0];
		pipe(fd);
		child(&pipex, argv[i], in , fd[1]);
		i++;
	}
	child(&pipex, argv[i++], fd[0] , pipex.outfile_fd);
	while ((wait(NULL)) > 0);
	//while (wait(NULL) != -1){}
}

void	child(t_utilis *pipex, char *cmd, int in, int out)
{
	int pid;
	char **param;
	char *binary;

	param = ft_split(cmd, ' ');
	binary = get_binary_path(pipex, param[0]);
	pid = fork();
	if (pid == -1)
		ft_putendl_fd("fork Error", 2);
	else if (pid == 0)
	{
		dup2(out, 1);
		close(out);
		dup2(in, 0);
		close(in);
		//ft_printf("%s\n%s|%s|%s\n", binary, param[0], param[1], param[2]);
		execve(binary, param, pipex->envp);
		//ft_printf("I:%d|P: %s|O:%d\n", in, cmd, out);
		exit(0);
	}
	//exit(0);
}

char	*get_binary_path(t_utilis *pipex, char *binary)
{
	int		i;
	char	*path;
	char	**paths;

	i = -1;
	while (pipex->envp[++i])
		if (ft_strncmp(pipex->envp[i], "PATH=", 5) == 0)
			path = &pipex->envp[i][5];
	paths = ft_split(path, ':');
	path = access_path(paths, binary);
	i = 0;
	while (paths[i] != NULL)
		free(paths[i++]);
	free(paths);
	return (path);
}

char	*access_path(char **paths, char *binary)
{
	int		i;
	char	*tmp;
	char	*path;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin("/", binary);
		path = ft_strjoin(paths[i], tmp);
		free(tmp);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

void	init_t_utilis(t_utilis *pipex, int argc, char **argv, char **envp)
{
	pipex->infile = argv[1];
	pipex->outfile = argv[argc - 1];
	pipex->infile_fd = open(pipex->infile, O_RDONLY);
	pipex->outfile_fd = open(pipex->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	pipex->envp = envp;
	pipex->argument_1 = ft_split(argv[2], ' ');
	pipex->argument_2 = ft_split(argv[3], ' ');
	pipex->binary_path_1 = get_binary_path(pipex, pipex->argument_1[0]);
	pipex->binary_path_2 = get_binary_path(pipex, pipex->argument_2[0]);
	pipe(pipex->pipe_fd);
}

