/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parenthesis_checker.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:20:47 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/30 23:40:47 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_print_syntax_error_message(char *token)
{
	ft_dprintf(2, "%sminishell: syntax error near unexpected token `%s'%s\n",
		RED, token, RESET);
}

int	ft_check_parenthesis(t_list *tks)
{
	int	parenthesis;
	int	strings;

	parenthesis = 0;
	strings = 0;
	while (tks)
	{
		if (*(char *)tks->content == '\'' || *(char *)tks->content == '"')
			strings++;
		if (*(char *)tks->content == '(')
		{
			parenthesis++;
			strings = 0;
		}
		if (*(char *)tks->content == ')')
		{
			if (!strings)
				return (-1);
			parenthesis--;
		}
		if (parenthesis < 0)
			break ;
		tks = tks->next;
	}
	return (parenthesis);
}

int	ft_check_instructions_after_tokens(t_list *tks)
{
	int		instructions_after;

	instructions_after = 0;
	while (tks)
	{
		if (*(char *)tks->content == '"' || *(char *)tks->content == '\''
			|| *(char *)tks->content == ')')
			instructions_after++;
		if (*(char *)tks->content == '&' || *(char *)tks->content == '|')
		{
			if (instructions_after <= 0)
			{
				ft_print_syntax_error_message(tks->content);
				printf("1\n");
				return (1);
			}
			instructions_after = 0;
		}
		tks = tks->next;
	}
	return (0);
}

int	check_tokens_after_special_found(t_list *tks, int *instructions_last)
{
	while (tks)
	{
		if (*(char *)tks->content == '"' || *(char *)tks->content == '\''
			|| *(char *)tks->content == '(')
			(*instructions_last)++;
		if (*(char *)tks->content == '&' || *(char *)tks->content == '|'
			|| *(char *)tks->content == '<' || *(char *)tks->content == '>')
			{
			if (*instructions_last <= 0)
			{
				ft_print_syntax_error_message(tks->content);
				printf("2\n");
				return (1);
			}
			*instructions_last = 0;
		}
		if (!tks->next)
			return (0);
		tks = tks->next;
	}
	return (0);
}

int ft_check_instructions_last_tokens(t_list *tks)
{
	int		instructions_last;

	instructions_last = 0;
	while (tks && (*(char *)tks->content != '&' && *(char *)tks->content != '|'
			&& *(char *)tks->content != '<' && *(char *)tks->content != '>'))
		tks = tks->next;
	if (!tks)
		return (0);
	if (tks->next)
	{
		tks = tks->next;
		if (check_tokens_after_special_found(tks, &instructions_last))
			return (1);
	}
	if (instructions_last <= 0)
	{
		ft_print_syntax_error_message(tks->content);
		printf("3\n");
		return (1);
	}
	return (0);
}

int	ft_check_parenthesis_and_instructions(t_list *tks)
{
	int	parenthesis;

	parenthesis = 0;
	while (tks)
	{
		if (*(char *)tks->content == ')')
			parenthesis++;
		else if (parenthesis > 0 && (*(char *)tks->content == '"'
				|| *(char *)tks->content == '\'' || *(char *)tks->content == '('))
		{
			ft_print_syntax_error_message(tks->content);
			printf("4\n");
			return (1);
		}
		else if (*(char *)tks->content == '&' || *(char *)tks->content == '|')
			parenthesis = 0;
		tks = tks->next;
	}
	return (0);
}
/*
int	check_token_order_validity(t_list *tks, int *order, int *instructions)
{
	if (*order == 1 && (*(char *)tks->content == '"'
			|| *(char *)tks->content == '\''))
	{
		(*instructions)++;
		*order = 0;
	}
	if (*instructions > 0 && *(char *)tks->content == '(' && *order == 0)
	{
		ft_print_syntax_error_message(tks->content);
		printf("5\n");
		return (1);
	}
	if (*instructions == 0 && *(char *)tks->content == '(')
	{
		(*instructions)++;
		*order = 0;
	}
	if ((*(char *)tks->content == '&' || *(char *)tks->content == '|'))
	{
		*instructions = 0;
		*order = 1;
	}
	return (0);
}

int	ft_check_instructions_and_parenthesis(t_list *tks)
{
	int	instructions;
	int order;

	instructions = 0;
	order = 1;
	while(tks)
	{
		if (check_token_order_validity(tks, &order, &instructions))
			return (1);
		tks = tks->next;
	}
	return (0);
}*/

int	ft_check_instructions_and_parenthesis(t_list *tks)
{
	int instructions;

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
			printf("5\n");
			return (1);
		}
		tks = tks->next;
	}
	return (0);
}

int	ft_find_open_parenthesis(t_list *tks)
{
	int	open_parenthesis;
	//int	is_in_fact_open;

	open_parenthesis = 0;
	//is_in_fact_open = 0;

	while (tks)
	{
		if (*(char *)tks->content == '(')
			open_parenthesis++;
		tks = tks->next;
	}
	return (open_parenthesis);
}

int 	ft_check_for_redundant_parenthesis(t_list *tks, int exit_code)
{
	int	logic_operator_found;
	int	open_parenthesis;
	//int len;

	if (exit_code)
		return (1);
	open_parenthesis = ft_find_open_parenthesis(tks);
	//open_parenthesis = 0;
	logic_operator_found = 0;
	//len = ft_lstsize(tks);
	while (tks)
	{
		if (*(char *)tks->content == ')')
		{
			if (!logic_operator_found)
			{
				printf("Si se imprime esto, es que hay un error\n");
				return (1);
			}
			return (0);
		}
		if (*(char *)tks->content == '(')
		{
			exit_code = ft_check_for_redundant_parenthesis(tks->next, exit_code);
			if (exit_code)
				return (1);
			//len = ft_lstsize(tks);
			//while (--len && (*(char *)tks->content != ')' || *(char *)tks->content != '&' || ft_strncmp_p(tks->content, "||" , 2)))
			//open_parenthesis = 1;
			while (tks && open_parenthesis > 0)
			{
				if (*(char *)tks->content == '(')
					open_parenthesis++;
				if (*(char *)tks->content == ')')
					open_parenthesis--;
				tks = tks->next;
				//len--;
			}
			if (!tks)
			{
				printf("Si se imprime esto, es que hay un error\n");
				return (1);
			}
		}
		if (*(char *)tks->content == '&' || !ft_strncmp_p(tks->content, "||" , 2))
			logic_operator_found = 1;
		tks = tks->next;
	}
	return (exit_code);
}
