#include "../include/minishell.h"

void	ft_dollar_variable_converter(t_list *list);
void	ft_join_str_tokenizer(t_list *list);
void	ft_put_quotes(t_list *list);
int		ft_check_parenthesis(t_list *tks);
int		ft_verify_correct_order_onwards(t_list *tks);
void	ft_print_syntax_error_message(char *token);
int		ft_verify_correct_order_backwards(t_list *tks);
int		ft_check_instructions_after_parenthesis(t_list *tks);
int		ft_check_instructions_before_parenthesis(t_list *tks);
int		ft_check_for_redundant_parenthesis(t_list *tks);
int		ft_check_redirections(t_list *list);
void	ft_join_redirections(t_list *list);

int	ft_check_token_list(t_list **list)
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
	ft_dollar_variable_converter(*list);
	ft_join_str_tokenizer(*list);
	ft_remove_spaces(list);
	if (!ft_check_redirections(*list))
		return (0);
	ft_join_redirections(*list);
	if (ft_verify_correct_order_onwards(*list)
		|| ft_verify_correct_order_backwards(*list)
		|| ft_check_instructions_after_parenthesis(*list)
		|| ft_check_instructions_before_parenthesis(*list)
		|| ft_check_for_redundant_parenthesis(*list))
		return (0);
	return (1);
}
