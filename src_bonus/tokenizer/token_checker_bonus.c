/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:21:04 by dagimeno          #+#    #+#             */
/*   Updated: 2025/05/06 23:33:08 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_bonus.h"

int	ft_check_token_list(t_list **list, t_minishell *minishell)
{
	int		parenthesis_code;

	parenthesis_code = ft_check_parenthesis(*list);
	if (parenthesis_code)
	{
		if (parenthesis_code < 0)
			ft_print_syntax_error_message(")");
		else
			ft_print_syntax_error_message("(");
		return (0);
	}
	ft_dollar_variable_converter(*list, minishell);
	ft_join_str_tokenizer(*list);
	ft_manage_wildcards(*list);
	ft_remove_spaces(list);
	if (!ft_check_redirections(*list))
		return (0);
	ft_join_redirections(*list);
	if (ft_verify_correct_order_onwards(*list)
		|| ft_verify_correct_order_backwards(*list)
		|| ft_check_instructions_after_parenthesis(*list)
		|| ft_check_instructions_before_parenthesis(*list)
		/*|| ft_check_for_redundant_parenthesis(*list)*/)
		return (0);
	return (1);
}
