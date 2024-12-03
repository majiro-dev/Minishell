/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manujime <manujime@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:46:15 by manujime          #+#    #+#             */
/*   Updated: 2023/06/15 16:07:09 by manujime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_tmp_path(t_data *data)
{
	char	*shell;
	char	*tmp;

	tmp = ft_get_env("SHELL", data);
	shell = ft_strtrim(tmp, "minishell");
	free(tmp);
	tmp = ft_strjoin(shell, "/tmp/.here_docminishell.tmp");
	free(shell);
	return (tmp);
}

char	*ft_get_delimiter(t_input *current)
{
	char	**tmp;
	char	*aux;

	tmp = ft_split(current->content, ' ');
	aux = ft_strjoin(tmp[1], "\n");
	ft_free_char_matrix(tmp);
	return (aux);
}

void	ft_here_document(t_input *current, int *inputfd, t_data *data)
{
	int		fd;
	char	*delim;
	char	*line;
	char	*shell;

	delim = ft_get_delimiter(current);
	shell = ft_get_tmp_path(data);
	fd = open(shell, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	line = get_next_line(STDIN_FILENO);
	while (ft_strcmp(line, delim) != 0)
	{
		ft_putstr_fd(line, fd);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	close(fd);
	fd = open(shell, O_RDONLY);
	free(shell);
	free(line);
	free(delim);
	if (*inputfd != 0)
		close(*inputfd);
	*inputfd = fd;
}
