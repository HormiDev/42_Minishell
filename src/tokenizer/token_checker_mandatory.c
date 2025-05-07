/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker_mandatory.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 22:04:40 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/05/07 13:26:30 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_check_token_list(t_list **list, t_minishell *minishell)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (!ft_strncmp_p((char *)tmp->content, "&&", 2)
			|| !ft_strncmp_p((char *)tmp->content, "||", 2)
			|| !ft_strncmp_p((char *)tmp->content, "(", 1)
			|| !ft_strncmp_p((char *)tmp->content, ")", 1))
		{
			printf("%sOperators not allowed in mandatory part%s\n", RED, RESET);
			return (0);
		}
		tmp = tmp->next;
	}
	ft_dollar_variable_converter(*list, minishell);
	ft_join_str_tokenizer(*list);
	ft_remove_spaces(list);
	if (!ft_check_redirections(*list))
		return (0);
	ft_join_redirections(*list);
	if (ft_verify_correct_order_onwards(*list)
		|| ft_verify_correct_order_backwards(*list))
		return (0);
	return (1);
}
