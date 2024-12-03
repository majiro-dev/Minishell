/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manujime <manujime@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:43:08 by manujime          #+#    #+#             */
/*   Updated: 2023/06/12 12:48:36 by manujime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//removes the first and last character the list->content string
void	ft_remove_quotes(t_input *list)
{
	int		c;
	int		k;
	char	*new;

	c = 1;
	k = 0;
	new = malloc(sizeof(char) * ft_strlen(list->content));
	if (!new)
		return ;
	while (list->content[c])
	{
		new[k] = list->content[c];
		k++;
		c++;
	}
	new[k - 1] = '\0';
	free(list->content);
	list->content = new;
}

void	ft_rep_lace(t_input *input, int s, int e, char *val)
{
	int		c;
	int		k;
	char	*new;

	c = 0;
	k = 0;
	if (val == NULL)
		val = "";
	new = malloc(sizeof(char) * (ft_strlen(input->content)
				- (e - s) + ft_strlen(val) + 1));
	if (!new)
		return ;
	while (c < s)
		new[k++] = input->content[c++];
	c = 0;
	while (val[c])
		new[k++] = val[c++];
	c = e;
	while (input->content[c])
		new[k++] = input->content[c++];
	new[k] = '\0';
	free(input->content);
	input->content = new;
}

//takes the position of the first and las character of the variable name
//makes a substring of the variable name
//searches for the variable name in the env list
//if it finds it, it replaces the variable name with the value
void	ft_replace_var(t_input *input, t_data *data)
{
	int		s;
	int		e;
	char	*var;
	char	*val;

	s = 0;
	e = 0;
	while (input->content[e] && input->content[e] != '$')
		e++;
	if (input->content[e] == '$')
	{
		e++;
		s = e;
		while (input->content[e]
			&& ft_strchr("'\"><| $", input->content[e]) == NULL)
				e++;
		var = ft_substr(input->content, s, e - s);
		if (ft_strcmp(var, "?") == 0)
			val = ft_itoa(data->actual_status);
		else
			val = ft_get_env(var, data);
		ft_rep_lace(input, s - 1, s + ft_strlen(var), val);
		free(var);
		free(val);
	}
}

//searches for variables in the list->content string
//if it finds one, it replaces it with the value of the variable
//if the content is a quoted string, it removes the closed quotes
void	ft_search_and_replace(t_data *data)
{
	t_input	*aux;

	aux = data->list;
	while (aux)
	{
		if (aux->type == 1 || aux->type == 2)
			ft_remove_quotes(aux);
		while ((aux->type == 0 || aux->type == 2)
			&& ft_strchr(aux->content, '$'))
			ft_replace_var(aux, data);
		aux = aux->next;
	}
}
