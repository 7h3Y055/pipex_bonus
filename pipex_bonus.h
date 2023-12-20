#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include "libft.h"

typedef struct s_utilis
{
	char const	*infile;
	char const	*outfile;
	int			infile_fd;
	int			outfile_fd;
	char		**envp;
	char		*binary_path_1;
	char		*binary_path_2;
	char		**argument_1;
	char		**argument_2;
	int			pipe_fd[2];
}	t_utilis;

void	init_t_utilis(t_utilis *pipex, int argc, char **argv, char **envp);
char	*access_path(char **paths, char *binary);
void	child(t_utilis *pipex, char *cmd, int in, int out);
char	*get_binary_path(t_utilis *pipex, char *binary);


#endif
