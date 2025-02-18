#include "../include/minishell.h"

int	ft_check_token_list(t_list *list)
{
	int		parenthesis_code;

	parenthesis_code = ft_check_parenthesis(list);
	if (parenthesis_code)
	{
		if (parenthesis_code < 0)
			ft_print_syntax_error_message(")");
		else
			ft_print_syntax_error_message("(");
		return (0);
	}
	ft_dollar_variable_converter(list);
	ft_join_str_tokenizer(list);
	ft_remove_spaces(&list);
	if (!ft_check_redirections(list))
		return (0);
	ft_join_redirections(list);
	if (ft_check_instructions_after_tokens(list) 
		|| ft_check_instructions_last_tokens(list)
		|| ft_check_parenthesis_and_instructions(list)
		|| ft_check_instructions_and_parenthesis(list)
		|| ft_check_for_redundant_parenthesis(list))
		return (0);
	return (1);
}