/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manujime <manujime@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:41:29 by manujime          #+#    #+#             */
/*   Updated: 2023/06/15 12:43:34 by manujime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//updates the envp array with the new PWD and OLDPWD
void	ft_cd_update(t_data *data)
{
	char	*cwd;

	cwd = ft_get_env("PWD", data);
	free(data->input[1]);
	data->input[1] = ft_strjoin("OLDPWD=", cwd);
	ft_update_env(data);
	free(cwd);
	free(data->input[1]);
	cwd = getcwd(NULL, 0);
	data->input[1] = ft_strjoin("PWD=", cwd);
	ft_update_env(data);
	free(cwd);
	free(data->input[1]);
	data->input[1] = NULL;
}

//checks if the var to remove exits
int	ft_unset_check(t_data *data)
{
	char	*var;
	int		c;
	int		found;

	c = 0;
	found = 0;
	while (data->envp[c])
	{
		var = ft_get_var(data->envp[c]);
		if (ft_strcmp(var, data->input[1]) == 0)
			found = 1;
		c++;
		free(var);
	}
	return (found);
}

//removes a variable from the envp array
void	ft_unset(t_data *data)
{
	char	*var;
	char	**new_envp;
	int		c;
	int		d;

	if (ft_unset_check(data) == 0)
		return ;
	c = 0;
	d = 0;
	new_envp = malloc(sizeof(char *) * (ft_char_matrix_len(data->envp)));
	while (data->envp[c])
	{
		var = ft_get_var(data->envp[c]);
		if (ft_strcmp(var, data->input[1]) == 0)
		{
			free(var);
			c++;
			continue ;
		}
		free(var);
		new_envp[d++] = ft_strdup(data->envp[c++]);
	}
	new_envp[d] = NULL;
	ft_free_char_matrix(data->envp);
	data->envp = new_envp;
}

//executes the builtin commands
void	ft_execute_builtin(t_data *data, int inputfd, int outputfd)
{
	ft_redirect_in_out(inputfd, outputfd, data);
	if (ft_strcmp(data->input[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(data->input[0], "echo") == 0)
		ft_echo(data->input);
	else if (ft_strcmp(data->input[0], "env") == 0)
		ft_print_env(data->envp);
	else if (ft_strcmp(data->input[0], "exit") == 0)
		ft_exit(data->input, data);
	ft_clean_exit(EXIT_SUCCESS, data);
}

//executes commands in the parent process
void	ft_parent_command(t_data *data)
{
	if (ft_strcmp(data->input[0], "export") == 0)
		ft_export(data);
	else if (ft_strcmp(data->input[0], "cd") == 0)
		ft_cd(data);
	else if (ft_strcmp(data->input[0], "unset") == 0)
		ft_unset(data);
	else if (ft_strcmp(data->input[0], "exit") == 0)
		ft_exit(data->input, data);
}
