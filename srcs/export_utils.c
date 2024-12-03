/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manujime <manujime@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:46:34 by manujime          #+#    #+#             */
/*   Updated: 2023/06/15 20:11:06 by manujime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//gets the variable name from the input for the export command
//which is everything before the '=' sign
//and returns it
char	*ft_get_var(char *env)
{
	int		c;
	char	*var;

	c = 0;
	while (env[c] != '=')
		c++;
	var = malloc(sizeof(char) * (c + 1));
	if (var == NULL)
	{
		ft_putstr_fd("Error: malloc failed\n", STDERR_FILENO);
		return (NULL);
	}
	c = -1;
	while (env[++c] != '=')
		var[c] = env[c];
	var[c] = '\0';
	return (var);
}

//prints the environment variables
void	ft_print_env(char **envp)
{
	int	c;

	c = 0;
	while (envp[c])
	{
		ft_putstr_fd(envp[c], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		c++;
	}
}

//checks if the input variable aleady exists in the envp array
//if it does, it updates the value of the variable
//and returns 1
//if it doesn't it does nothing and returns 0
int	ft_update_env(t_data *data)
{
	int		c;
	char	*var_name;
	char	*input_name;

	c = 0;
	input_name = ft_get_var(data->input[1]);
	while (data->envp[c])
	{
		var_name = ft_get_var(data->envp[c]);
		if (ft_strcmp(var_name, input_name) == 0)
		{
			free(data->envp[c]);
			data->envp[c] = ft_strdup(data->input[1]);
			free(var_name);
			free(input_name);
			return (1);
		}
		free(var_name);
		c++;
	}
	free(input_name);
	return (0);
}

//adds a new environment variable to the envp array
int	ft_add_env(t_data *data)
{
	int			c;
	char		**new_envp;

	c = 0;
	while (data->envp[c])
		c++;
	new_envp = malloc(sizeof(char *) * (c + 2));
	if (new_envp == NULL)
	{
		ft_putstr_fd("Error: malloc failed\n", STDERR_FILENO);
		return (0);
	}
	c = -1;
	while (data->envp[++c])
		new_envp[c] = ft_strdup(data->envp[c]);
	new_envp[c] = ft_strdup(data->input[1]);
	new_envp[c + 1] = NULL;
	ft_free_char_matrix(data->envp);
	data->envp = new_envp;
	return (1);
}
