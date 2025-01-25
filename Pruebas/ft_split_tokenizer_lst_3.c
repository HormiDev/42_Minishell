/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tokenizer_lst_3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:50:10 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/25 19:47:02 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_tkncmp(char c)
{
	if (c == ' ' || c == '\t' || c == '\'' || c == '>'
		|| c == '<' || c == '|' || c == '(' || c == ')'
		|| c == '\n' || c == ';' || c == '&')
		return (1);
	return (0);
}

void join_free_strings_tokens_with_adjacent_double_quote_tokens(t_list *list)
{
	t_list	*tmp;
	char	*str;

	while (((char *)list->next->content)[0])
	{
		if (((char *)list->next->content)[0] == '\"')
		{
			if (!ft_tkncmp(((char *)list->content)[0]))
			{
			}
		}
		list = list->next;
	}
}