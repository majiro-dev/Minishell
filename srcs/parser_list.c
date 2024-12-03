/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manujime <manujime@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:14:27 by manujime          #+#    #+#             */
/*   Updated: 2023/06/22 16:06:30 by manujime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//0 = non-quoted string
//1 = '' single quoted string
//2 = "" double quoted string
//3 = << here document
//4 = <  input redirect
//5 = >> output redirect append
//6 = >  output redirect
//7 = | pipe

//creates a new node and adds it to the end of the list
//the node contains from s to e of the data->line string
void	ft_new_node(t_data *data, int s, int e)
{
	t_input	*new;
	t_input	*tmp;
	char	*str;

	str = ft_substr(data->line, s, e - s);
	new = malloc(sizeof(t_input));
	if (!new)
		return ;
	new->content = str;
	new->type = 0;
	new->next = NULL;
	new->prev = NULL;
	if (!data->list)
		data->list = new;
	else
	{
		tmp = data->list;
		while (tmp->next)
			tmp = tmp->next;
		new->prev = tmp;
		tmp->next = new;
	}
}

//handles the quoted part of the input string
//separating it into a new node for further processing later
void	ft_quote_node(t_data *data, int *start, int *counter, char quote)
{
	int	c;
	int	s;

	c = *counter;
	s = *start;
	c++;
	while (data->line[c] && data->line[c] != quote)
		c++;
	if (data->line[c] == quote)
		c++;
	ft_new_node(data, s, c);
	*counter = c;
}

//makes a new node for the pipes and redirects from the unquoted
//part of the input string
void	ft_repi_node(t_data *data, int *start, int *counter, char div)
{
	int	c;
	int	s;

	c = *counter;
	s = *start;
	c++;
	if (data->line[c] == div && div != '|')
		c++;
	if (div == '>' || div == '<')
	{
		while (data->line[c] == ' ')
			c++;
		while (data->line[c] && ft_strchr("|>< ", data->line[c]) == 0)
			c++;
	}
	ft_new_node(data, s, c);
	*counter = c;
}

//makes a new node for the non-quoted part of the input string
//it skips the spaces and pipes and redirects
//separating it into a new node for further processing later
void	ft_regular_node(t_data *data, int *start, int *counter)
{
	int	c;
	int	s;

	c = *counter;
	s = *start;
	while (data->line[c] && data->line[c] == ' ')
		c++;
	s = c;
	while (data->line[c] && data->line[c] != '\''
		&& data->line[c] != '\"'
		&& ft_strchr("|>< ", data->line[c]) == 0)
		c++;
	if (c > s)
		ft_new_node(data, s, c);
	*counter = c;
}

//divides the data->line string into nodes
//each node contains a string surrounded by single or double quotes
//or a non-quoted string, that includes non closed quotes
void	ft_input_parse(t_data *data)
{
	int	c;
	int	s;

	c = 0;
	while (data->line[c])
	{
		s = c;
		if (data->line[c] == '\'')
			ft_quote_node(data, &s, &c, '\'');
		else if (data->line[c] == '\"')
			ft_quote_node(data, &s, &c, '\"');
		else if (ft_strchr("|><", data->line[c]))
			ft_repi_node(data, &s, &c, data->line[c]);
		else
			ft_regular_node(data, &s, &c);
	}
	ft_set_input_type(data);
}
