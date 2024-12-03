/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manujime <manujime@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 22:58:35 by manujime          #+#    #+#             */
/*   Updated: 2023/06/13 19:47:07 by manujime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//redirects the output to the file specified in the command
//if the file does not exist, it creates it
//if the file exists, it overwrites it
//if the file is not specified, it prints an error
//if open fails, it prints an error
//0664 represents the permissions for the file
// if the flag is set to 0 it overwrites the file
// if the flag is set to 1 it appends to the file
void	ft_output_redirect(t_input *current, int *outputfd,
	int append, t_data *data)
{
	int		fd;
	char	**tmp;

	tmp = ft_split(current->content, ' ');
	if (!tmp[1] || tmp == NULL)
	{
		ft_free_char_matrix(tmp);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("syntax error near unexpected token 'newline'\n", 2);
		data->redir_err = 1;
		return ;
	}
	if (append == 1)
		fd = open(tmp[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(tmp[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_free_char_matrix(tmp);
	if (*outputfd != 1)
		close(*outputfd);
	*outputfd = fd;
}

//redirects the input to the file specified in the command
//if the file does not exist or cannot be opened, it prints an error
//if the file is not specified, it prints an error
void	ft_input_redirect(t_input *current, int *inputfd)
{
	int		fd;
	char	**tmp;

	tmp = ft_split(current->content, ' ');
	if (!tmp[1] || tmp == NULL)
	{
		ft_free_char_matrix(tmp);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("syntax error near unexpected token 'newline'\n", 2);
		return ;
	}
	fd = open(tmp[1], O_RDONLY);
	ft_free_char_matrix(tmp);
	if (fd == -1)
	{
		perror("open: ");
		return ;
	}
	if (*inputfd != 0)
		close(*inputfd);
	*inputfd = fd;
}

//checks if there is any redirection in the command
//if there is, it redirects the input or output to the file
//if there is not, it does nothing
//3 = << here document
//4 = <  input redirect
//5 = >> output redirectss append
//6 = >  output redirect
void	ft_redirect_fd(t_data *data, int *inputfd, int *outputfd)
{
	t_input	*tmp;

	tmp = data->current;
	while (tmp->prev && tmp->type != 7)
		tmp = tmp->prev;
	while (tmp)
	{
		if (tmp->type == 6)
			ft_output_redirect(tmp, outputfd, 0, data);
		else if (tmp->type == 3)
			ft_here_document(tmp, inputfd, data);
		else if (tmp->type == 4)
			ft_input_redirect(tmp, inputfd);
		else if (tmp->type == 5)
			ft_output_redirect(tmp, outputfd, 1, data);
		tmp = tmp->next;
	}
}
