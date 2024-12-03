/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manujime <manujime@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:58:52 by manujime          #+#    #+#             */
/*   Updated: 2023/06/15 19:59:04 by manujime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//checks if a string is comprised of - as the first character and n as the
//rest of the characters
int	ft_is_n(char *str)
{
	int	c;

	c = 0;
	if (str[c] != '-')
		return (0);
	c++;
	while (str[c])
	{
		if (str[c] != 'n')
			return (0);
		c++;
	}
	return (1);
}
