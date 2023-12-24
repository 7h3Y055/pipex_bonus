#include "libft.h"
#include "pipex_bonus.h"


char *get_input_data(char *limiter)
{
	char *str;
	char *tmp;

	str = NULL;
	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		tmp = get_next_line(0);
		if (!tmp)
			ft_putchar_fd('\n', 1);
		else
			tmp[ft_strlen(tmp) - 1] = 0;
		if (tmp && ft_strncmp(tmp, limiter, ft_strlen(limiter) + 1) == 0)
		{
			free(tmp);
			break ;
		}
		str = ft_merge(str, tmp);
	}
	get_next_line(INT_MAX);
	return (str);
}

char *ft_merge(char *s1, char *s2)
{
	char *tmp;

	if (!s1 && !s2)
		return (NULL);
	if (s1 && !s2)
		return (s1);
	else if (!s1 && s2)
		return (s2);
	else
	{
		tmp = ft_strjoin(s1, s2);
		free(s1);
		free(s2);
	}
	return (tmp);
}



char	*get_binary_path(char **envp, char *binary)
{
	int		i;
	char	*path;
	char	**paths;

	i = -1;
	while (envp[++i])
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			path = &envp[i][5];
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





void	*ft_error(char *str)
{
	ft_putstr_fd("command not found: ", 2);
	ft_putendl_fd(str, 2);
	return (NULL);
}

