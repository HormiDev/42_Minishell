/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_checker.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 21:21:51 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/05/07 14:37:39 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_check_instructions_after_parenthesis(t_list *tks)
{
	int		parenthesis;
	char	*content;

	parenthesis = 0;
	while (tks)
	{
		content = (char *)tks->content;
		if (*content == ')')
			parenthesis++;
		else if (parenthesis > 0 && (*content == '"'
				|| *content == '\'' || *content == '('))
		{
			ft_print_syntax_error_message(tks->content);
			return (1);
		}
		else if (*content == '&' || *content == '|')
			parenthesis = 0;
		tks = tks->next;
	}
	return (0);
}

int	ft_check_instructions_before_parenthesis(t_list *tks)
{
	int	instructions;

	instructions = 0;
	while (tks)
	{
		if (*(char *)tks->content == '"' || *(char *)tks->content == '\''
			|| *(char *)tks->content == ')')
			instructions++;
		if (*(char *)tks->content == '|' || *(char *)tks->content == '&')
			instructions = 0;
		if (instructions > 0 && *(char *)tks->content == '(')
		{
			ft_print_syntax_error_message(tks->content);
			return (1);
		}
		tks = tks->next;
	}
	return (0);
}
