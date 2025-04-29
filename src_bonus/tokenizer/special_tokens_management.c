/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_tokens_management.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 22:05:05 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/02/19 22:05:13 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
