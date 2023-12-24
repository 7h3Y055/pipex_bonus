#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include "libft.a/libft.h"

typedef struct s_utilis
{
	char const	*infile;
	char const	*outfile;
	int			infile_fd;
	int			outfile_fd;
	int			argc;
	char		**argv;
	char		**envp;
	int			heredoc;
}	t_utilis;

t_utilis	*init_t_utilis(int argc, char **argv, char **envp, int heredoc);
char	*access_path(char **paths, char *binary);
void	child(t_utilis *pipex, char *cmd, int in, int *fd);
char	*get_binary_path(char **envp, char *binary);
void	*ft_error(char *str);
char	*get_input_data(char *limiter);
char	*ft_merge(char *s1, char *s2);
int		multi_pipes(t_utilis *pipex);
int		here_doc(t_utilis *pipex);
void	*free_split(char **param);
void	free_all(void *ptr1, void *ptr2, void *ptr3, void *ptr4);
void	child_helper(t_utilis *pipex, int *fd, char **param, int in);


#endif
