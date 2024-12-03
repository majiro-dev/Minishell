/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manujime <manujime@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:53:52 by manujime          #+#    #+#             */
/*   Updated: 2023/06/22 16:06:55 by manujime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h> //to delete

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;36m"
# define END "\033[0m"
# define CYAN "\033[0;36m"
# define YELLOW "\033[0;33m"

# define N0_QUOTE 0
# define SI_QUOTE 1
# define DO_QUOTE 2

typedef struct s_input
{
	char			*content;
	int				type;
	struct s_input	*next;
	struct s_input	*prev;
}	t_input;

typedef struct s_data
{
	char	*line;
	char	**input;
	t_input	*list;
	t_input	*current;
	int		pipecount;
	char	**envp;
	char	**argv;
	int		argc;
	int		actual_status;
	pid_t	child;
	int		redir_err;

}	t_data;

//main.c
int		ft_builtins(t_data *data, int infd, int outfd);
void	ft_launch_executable(t_data *data, int infd, int outfd);
void	ft_command(t_data *data, int infd, int outfd, int c);
//exe_utils.c
void	ft_print_error(char *path, int outfd, t_data *data);
int		ft_is_all_space(char *input);
void	ft_check_file(t_data *data, char *input);
char	*ft_pathfinder(t_data *data);
//builtins.c
void	ft_cd(t_data *data);
void	ft_pwd(void);
void	ft_echo(char **input);
//built_ins_2.c
void	ft_unset(t_data *data);
void	ft_execute_builtin(t_data *data, int inputfd, int outputfd);
void	ft_parent_command(t_data *data);
void	ft_cd_update(t_data *data);
//built_ins_3.c
int		ft_is_n(char *str);
//clean_up.c
void	ft_clean_paths(char **paths);
void	ft_clean_input(t_data *data);
void	ft_leaks(void);
void	ft_clean_exit(int exit_code, t_data *data);
//init.c
void	ft_init_data(t_data *data, int argc, char **argv, char **envp);
void	ft_exit(char **input, t_data *data);
void	ft_export(t_data *data);
void	ft_print_init(void);
//export_utils.c
char	*ft_get_var(char *env);
void	ft_print_env(char **envp);
int		ft_add_env(t_data *data);
int		ft_update_env(t_data *data);
//parser.c
char	*ft_get_env(char *line, t_data *data);
void	ft_parse(t_data *data);
int		ft_count_input(t_input *list);
void	ft_set_input_type(t_data *data);
//parser_sign.c
void	ft_search_and_replace(t_data *data);
//parser_list.c
void	ft_input_parse(t_data *data);
//updates_at_start.c
void	ft_shlvl(t_data *data);
void	ft_shell_name(t_data *data);
//pipes.c
int		ft_count_pipes(t_input *list);
void	ft_redirect_in_out(int inputfd, int outputfd, t_data *data);
void	ft_pipeline(t_data *data, int pipecount);
//redirects.c
void	ft_redirect_fd(t_data *data, int *inputfd, int *outputfd);
//signals.c
void	signal_setter(void);
void	signal_handler(int signal);
void	ft_active_setter(int i);
int		ft_active_getter(void);
//here_document.c
void	ft_here_document(t_input *current, int *inputfd, t_data *data);

#endif