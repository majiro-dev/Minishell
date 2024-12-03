/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updates_at_start.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manujime <manujime@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:41:23 by manujime          #+#    #+#             */
/*   Updated: 2023/06/14 00:12:51 by manujime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//updates the SHLVL variable
void	ft_shlvl(t_data *data)
{
	int		c;
	char	*tmp;
	char	*aux;
	char	*var;

	c = 0;
	while (data->envp[c])
	{
		var = ft_get_var(data->envp[c]);
		if (ft_strcmp("SHLVL", var) == 0)
		{
			free(var);
			aux = ft_itoa(ft_atoi(data->envp[c] + 6) + 1);
			tmp = ft_strjoin("SHLVL=", aux);
			free(aux);
			free(data->envp[c]);
			data->envp[c] = tmp;
			break ;
		}
		free(var);
		c++;
	}
}

//updates the SHELL variable to the path of the executable
//and calls ft_shlvl to update the SHLVL variable
void	ft_shell_name(t_data *data)
{
	int		c;
	char	*aux;
	char	*path;
	char	*var;

	c = 0;
	path = getcwd(NULL, 0);
	while (data->envp[c])
	{
		var = ft_get_var(data->envp[c]);
		if (ft_strcmp("SHELL", var) == 0)
		{
			free(var);
			aux = ft_strjoin("SHELL=", path);
			free(path);
			path = ft_strjoin(aux, "/minishell");
			free (aux);
			free(data->envp[c]);
			data->envp[c] = path;
			break ;
		}
		free(var);
		c++;
	}
	ft_shlvl(data);
}
