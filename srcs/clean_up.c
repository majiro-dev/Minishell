/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manujime <manujime@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:09:32 by manujime          #+#    #+#             */
/*   Updated: 2023/06/14 18:17:50 by manujime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//keep this commented when pushing to the 42 repo
//the leaks produced by readline don't need to be fixed
void	ft_leaks(void)
{
	system("leaks -q minishell");
}

//frees all the memory allocated for the list
//and each of its nodes
void	ft_clean_list(t_input *list)
{
	t_input	*tmp;

	tmp = list;
	while (list)
	{
		tmp = list->next;
		free(list->content);
		free(list);
		list = tmp;
	}
}

void	ft_clean_input(t_data *data)
{
	t_input	*tmp;

	tmp = data->list;
	free(data->line);
	ft_clean_list(tmp);
	data->list = NULL;
}

void	ft_clean_exit(int exit_code, t_data *data)
{
	rl_clear_history();
	ft_free_char_matrix(data->envp);
	ft_clean_input(data);
	exit(exit_code);
}
