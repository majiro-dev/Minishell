/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manujime <manujime@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:27:37 by manujime          #+#    #+#             */
/*   Updated: 2023/06/22 16:06:13 by manujime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//returns the variable value from an environment variable
char	*ft_get_env(char *input, t_data *data)
{
	int		c;
	char	*var;
	char	**value;
	char	*tmp;

	c = 0;
	while (data->envp[c])
	{
		var = ft_get_var(data->envp[c]);
		if (ft_strcmp(var, input) == 0)
		{
			free(var);
			value = ft_split(data->envp[c], '=');
			tmp = ft_strdup(value[1]);
			ft_free_char_matrix(value);
			return (tmp);
		}
		free(var);
		c++;
	}
	return (NULL);
}

//prints the content of the input linked list
//used for debugging only
void	ft_print_input(t_input *list)
{
	while (list)
	{
		printf("content: %s\n", list->content);
		printf("type: %d\n", list->type);
		list = list->next;
	}
}

//counts how big should be the allocated memory for the input char **
int	ft_count_input(t_input *list)
{
	int		count;
	t_input	*tmp;

	tmp = list;
	count = 0;
	while (tmp && tmp->type != 7)
	{
		if (tmp->type == 3 || tmp->type == 4
			|| tmp->type == 5 || tmp->type == 6)
		{
			tmp = tmp->next;
			continue ;
		}
		count++;
		tmp = tmp->next;
	}
	return (count);
}

//sets the type of the input node
//0 = non-quoted string
//1 = '' single quoted string
//2 = "" double quoted string
//3 = << here document
//4 = <  input redirect
//5 = >> output redirect append
//6 = >  output redirect
//7 = | pipe
void	ft_set_input_type(t_data *data)
{
	t_input	*tmp;

	tmp = data->list;
	while (tmp)
	{
		if (tmp->content[0] == '\'' && ft_strlen(tmp->content) > 1
			&& tmp->content[ft_strlen(tmp->content) - 1] == '\'')
			tmp->type = 1;
		else if (tmp->content[0] == '\"' && ft_strlen(tmp->content) > 1
			&& tmp->content[ft_strlen(tmp->content) - 1] == '\"')
			tmp->type = 2;
		else if (tmp->content[0] == '<' && tmp->content[1] == '<')
			tmp->type = 3;
		else if (tmp->content[0] == '<')
			tmp->type = 4;
		else if (tmp->content[0] == '>' && tmp->content[1] == '>')
			tmp->type = 5;
		else if (tmp->content[0] == '>')
			tmp->type = 6;
		else if (tmp->content[0] == '|')
			tmp->type = 7;
		else
			tmp->type = 0;
		tmp = tmp->next;
	}
}

//parses the line string of the data struct
void	ft_parse(t_data *data)
{
	ft_input_parse(data);
	ft_search_and_replace(data);
	data->pipecount = ft_count_pipes(data->list);
}
