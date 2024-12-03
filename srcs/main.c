/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manujime <manujime@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 21:14:58 by manujime          #+#    #+#             */
/*   Updated: 2023/06/15 20:07:17 by manujime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//checks if the first argument is a builtin command and if it is, executes it
//and returns 1, if it isn't, returns 0
int	ft_builtins(t_data *data, int inputfd, int outputfd)
{	
	pid_t	pid;
	int		status;
	int		is_builtin;

	is_builtin = 0;
	if (ft_strnstr("cd pwd echo exit export unset env",
			data->input[0], 33) != 0)
		is_builtin = 1;
	if (is_builtin == 1 && ft_strnstr("pwd echo env",
			data->input[0], 33) != 0)
	{
		ft_active_setter(1);
		pid = fork();
		if (pid == 0)
			ft_execute_builtin(data, inputfd, outputfd);
		else if (pid < 0)
		{
			perror("fork");
			ft_clean_exit(EXIT_FAILURE, data);
		}
		else
			waitpid(pid, &status, WUNTRACED);
	}
	return (is_builtin);
}

//checks if the first argument exists in the path from the PATH variable
//and if it does, it replaces the first argument with the full path
//to the executable
void	ft_execute_from_path(t_data *data)
{
	char	*aux;
	char	**paths;
	int		c;

	aux = ft_pathfinder(data);
	paths = ft_split(aux, ':');
	c = 0;
	if (ft_strcmp(aux, "") != 0)
		free (aux);
	while (paths[c] && ft_strcmp(paths[c], "") != 0)
	{
		aux = ft_strjoin(paths[c], "/");
		free (paths[c]);
		paths[c] = ft_strjoin(aux, data->input[0]);
		free (aux);
		if (access(paths[c], F_OK) == 0
			&& ft_strnstr(data->input[0], "./", 3) == 0)
		{
			free(data->input[0]);
			data->input[0] = ft_strdup(paths[c]);
			break ;
		}
		c++;
	}
	ft_free_char_matrix(paths);
}

//Search and launch the right executable (based on the PATH variable or using a
//relative or an absolute path)
void	ft_launch_executable(t_data *data, int infd, int outfd)
{
	int		status;

	ft_active_setter(1);
	data->child = fork();
	if (data->child == 0)
	{
		ft_check_file(data, data->input[0]);
		ft_execute_from_path(data);
		ft_redirect_in_out(infd, outfd, data);
		if (execve(data->input[0], data->input, data->envp) == -1)
			ft_print_error(data->input[0], outfd, data);
		ft_clean_exit(EXIT_FAILURE, data);
	}
	else if (data->child < 0)
		perror(data->input[0]);
	else
	{
		waitpid(data->child, &status, WUNTRACED);
		if (data->child > 0)
		{
			if (WIFEXITED(status))
				data->actual_status = WEXITSTATUS(status);
		}
	}
}

//checks if the first argument is a builtin command and if it isn't, it checks
//if it is an executable and if it is, it executes it
//checks for the exit command and exits the shell if it is
void	ft_command(t_data *data, int inputfd, int outputfd, int c)
{
	int	builtin;

	ft_redirect_fd(data, &inputfd, &outputfd);
	ft_parent_command(data);
	builtin = ft_builtins(data, inputfd, outputfd);
	if (!builtin && data->input[0])
		ft_launch_executable(data, inputfd, outputfd);
	if (c == ft_count_pipes(data->list))
		ft_active_setter(0);
}

//this is the main function, it displays a prompt and waits for the user to
//enter a command. It then reads the command and executes it. It loops until
//the user presses ctrl-D or types exit.
// atexit(ft_leaks);
int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	ft_print_init();
	ft_init_data(&data, argc, argv, envp);
	ft_shell_name(&data);
	while (1)
	{
		data.line = readline("minishell$ ");
		if (data.line == NULL)
		{
			printf("\n");
			break ;
		}
		if (ft_strcmp(data.line, "") == 0 || ft_is_all_space(data.line))
		{
			free(data.line);
			continue ;
		}
		add_history(data.line);
		ft_parse(&data);
		ft_pipeline(&data, ft_count_pipes(data.list));
		ft_clean_input(&data);
	}
	ft_clean_exit(EXIT_SUCCESS, &data);
	return (0);
}
