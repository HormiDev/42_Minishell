/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_tokens_management_bonus.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:20:13 by dagimeno          #+#    #+#             */
/*   Updated: 2025/05/06 21:20:17 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

static int	ft_manage_spaces(char *c)
{
	int	size;

	size = 0;
	while (!ft_strncmp_p(c, " ", 1) || !ft_strncmp_p(c, "\t", 1))
	{
		c++;
		size++;
	}
	return (size);
}

static int	ft_manage_quotes(char *c)
{
	int		size;
	char	quote;

	size = 1;
	quote = *c;
	c++;
	while (*c != quote)
	{
		if (*c == '\0')
			return (-1);
		c++;
		size++;
	}
	return (++size);
}

int	ft_is_special_token(char *c)
{
	int	size;

	size = 0;
	if (!ft_strncmp_p(c, ">>", 2) || !ft_strncmp_p(c, "<<", 2)
		|| !ft_strncmp_p(c, "||", 2) || !ft_strncmp_p(c, "&&", 2))
		return (2);
	if (!ft_strncmp_p(c, ">", 1) || !ft_strncmp_p(c, "<", 1)
		|| !ft_strncmp_p(c, "|", 1) || !ft_strncmp_p(c, "(", 1)
		|| !ft_strncmp_p(c, ")", 1) || !ft_strncmp_p(c, "\n", 1))
		return (1);
	if (!ft_strncmp_p(c, " ", 1) || !ft_strncmp_p(c, "\t", 1))
		size = ft_manage_spaces(c);
	if (!ft_strncmp_p(c, "'", 1) || !ft_strncmp_p(c, "\"", 1))
		size = ft_manage_quotes(c);
	return (size);
}
