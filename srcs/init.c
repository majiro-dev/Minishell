/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manujime <manujime@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:12:32 by manujime          #+#    #+#             */
/*   Updated: 2023/06/13 17:38:58 by manujime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//copies the envp to the data structure
//this makes it easier to update the environment variables
void	ft_copy_envp(t_data *data, char **envp)
{
	int	c;

	c = 0;
	while (envp[c])
		c++;
	data->envp = malloc(sizeof(char *) * (c + 1));
	if (!data->envp)
		perror("malloc error");
	c = 0;
	while (envp[c])
	{
		data->envp[c] = ft_strdup(envp[c]);
		c++;
	}
	data->envp[c] = NULL;
}

//initializes the data structure
void	ft_init_data(t_data *data, int argc, char **argv, char **envp)
{
	data->redir_err = 0;
	data->actual_status = 0;
	data->list = NULL;
	data->argc = argc;
	data->argv = argv;
	ft_copy_envp(data, envp);
	signal_setter();
	ft_active_setter(0);
}

void	ft_print_init(void)
{
	ft_putendl_fd(YELLOW, 1);
	ft_putendl_fd("ｍｉｎｉｓｈｅｌｌ", 1);
	ft_putendl_fd("ｂｙ ｍａｎｕｊｉｍｅ", 1);
	ft_putendl_fd("＆ ａｌｂｇｏｎｚａ", 1);
	ft_putchar_fd('\n', 1);
	ft_putendl_fd("ａｓ ｂｅａｕｔｉｆｕｌ ａｓ ａ ｓｈｅｌｌ", 1);
	ft_putendl_fd(END, 1);
}
