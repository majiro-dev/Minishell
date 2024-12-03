/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manujime <manujime@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 13:39:51 by manujime          #+#    #+#             */
/*   Updated: 2023/06/14 16:50:15 by manujime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//checks if the input[0] has "./" before the executable name
//if it does it prints perror(path), if it doesn't it prints
//ft_putstr_fd("command not found", 2)
void	ft_print_error(char *path, int outfd, t_data *data)
{
	dup2(STDOUT_FILENO, outfd);
	if (ft_strnstr(path, "./", 3) != 0 || ft_strnstr(path, "/", 2) != 0)
		perror(path);
	else
	{
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd("command not found \n", STDERR_FILENO);
	}
	ft_clean_exit(127, data);
}

//checks if the input is comprised of only spaces or tabs
//if it is it returns 1, if it isn't it returns 0
int	ft_is_all_space(char *input)
{
	int	c;

	c = 0;
	while (input[c] && (input[c] == ' ' || input[c] == '\t'))
		c++;
	if (input[c] == '\0')
		return (1);
	return (0);
}

//checks if the file exists in the current folder, if it does but it's not
//preceded by "./" it prints command not found, if it doesn't it prints
//perror(path)
void	ft_check_file(t_data *data, char *input)
{
	if (access(input, F_OK) == 0)
	{
		if (ft_strnstr(input, "./", 3) == 0 && ft_strnstr(input, "/", 2) == 0)
		{
			ft_putstr_fd(input, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd("command not found \n", STDERR_FILENO);
			ft_clean_exit(127, data);
		}
	}
}

//checks if the path env variable exists, if it does it returns the path
//if it doesn't it returns an empty string
char	*ft_pathfinder(t_data *data)
{
	char	*path;

	path = ft_get_env("PATH", data);
	if (path == NULL)
		return ("");
	return (path);
}
