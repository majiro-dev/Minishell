/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manujime <manujime@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:41:45 by manujime          #+#    #+#             */
/*   Updated: 2023/06/15 20:07:44 by manujime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//changes the current directory to the one specified in the input
//if no input is specified, it changes the current directory to the home
//directory
void	ft_cd(t_data *data)
{
	if (ft_char_matrix_len(data->input) > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return ;
	}
	if ((data->input[1] == NULL || ft_strcmp(data->input[1], "") == 0))
	{
		if (chdir(getenv("HOME")) != 0)
		{
			perror("cd");
			return ;
		}
	}
	else if (chdir(data->input[1]) != 0)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(data->input[1], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(2), STDERR_FILENO);
		return ;
	}
	ft_cd_update(data);
}

//gets the curent working directory and prints it to stdout
//if an error occurs, it prints the error to stderr
void	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		perror("pwd");
	else
	{
		ft_putstr_fd(cwd, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	free(cwd);
}

//prints the input to stdout, checks if there is a -n flag and if there is,
//it doesn't print a newline
//the -n flag is only valid if it's the first argument
//and can have many n
void	ft_echo(char **input)
{
	int	c;
	int	n_flag;

	c = 1;
	n_flag = 0;
	if (input[1] && ft_is_n(input[1]) == 1)
	{
		n_flag = 1;
		c++;
	}
	while (input[c] && ft_is_n(input[c]) == 1)
		c++;
	while (input[c])
	{
		ft_putstr_fd(input[c], STDOUT_FILENO);
		if (input[c + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		c++;
	}
	if (n_flag == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
}

//checks if there is an argument, if there is, it checks if it's valid
//then exits with the argument as the exit code
//if there is no argument, it exits with the exit code 0
void	ft_exit(char **input, t_data *data)
{
	int	c;

	c = 0;
	while (input[c])
		c++;
	if (c == 1)
		ft_clean_exit(EXIT_SUCCESS, data);
	else if (c == 2 && ft_isdigit(input[1][0]) == 1)
	{
		ft_clean_exit(ft_atoi(input[1]), data);
	}
	else if (!ft_isdigit(input[1][0]))
	{
		ft_putstr_fd("exit: numeric argument required : ", STDERR_FILENO);
		ft_putstr_fd(input[1], STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		ft_clean_exit(EXIT_SUCCESS, data);
	}
	else
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
	}
}

//export command, if there is no argument, it prints the environment
//if there is one argument, it checks if it's valid and if it is, it updates
//the environment variable if it exists, if it doesn't, it adds it to the
//environment
void	ft_export(t_data *data)
{
	int	c;

	c = 0;
	while (data->input[c])
		c++;
	if (c == 1)
		ft_print_env(data->envp);
	else if (c == 2)
	{
		if (ft_isalpha(data->input[1][0]) == 1)
		{
			if (!ft_update_env(data))
				ft_add_env(data);
		}
		else
		{
			printf("export: %s", strerror(2));
			printf(": %s\n", data->input[1]);
		}
	}
	else
	{
		printf("export: too many arguments\n");
	}
}
