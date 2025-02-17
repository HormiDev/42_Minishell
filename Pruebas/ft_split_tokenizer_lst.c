/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tokenizer_lst.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:58:26 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/02/17 21:22:57 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int	ft_manage_spaces(char *c)
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

int	ft_manage_quotes(char *c)
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

void	ft_print(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	while (tmp)
	{
		printf("%s,", (char *)tmp->content);
		tmp = tmp->next;
	}
	printf("\n");
}

int	ft_split_tokenizer_lst_while(char *str, t_list **list, int *i, int *start)
{
	int		size;

	size = ft_is_special_token(&str[*i]);
	if (size == -1)
	{
		ft_dprintf(2, "%sminishell: syntax error open quotes%s\n", RED, RESET);
		return (0);
	}
	if (size)
	{
		if (*i != 0)
		{
			if (*i - *start)
				ft_lstadd_back(list, ft_lstnew_ae(ft_substr_ae(str, *start,
					*i - *start)));
			ft_lstadd_back(list, ft_lstnew_ae(ft_substr_ae(str, *i, size)));
		}
		else
			ft_lstadd_back(list, ft_lstnew_ae(ft_substr_ae(str, *start, size)));
		(*start) = *i + size;
		(*i) += size;
	}
	else
		(*i)++;
	return (1);
}
void	ft_dollar_variable_converter(t_list *list);
void	ft_join_str_tokenizer(t_list *list);
void	put_quotes(t_list *list);
int		ft_check_parenthesis(t_list *tks);
int		ft_check_instructions_after_tokens(t_list *tks);
void	ft_print_syntax_error_message(char *token);
int		ft_check_instructions_last_tokens(t_list *tks);
int		ft_check_parenthesis_and_instructions(t_list *tks);
int		ft_check_instructions_and_parenthesis(t_list *tks);
int 	ft_check_for_redundant_parenthesis(t_list *tks);
/*
int	ft_check_token_list(t_list *list)
{
	while (list)
	{
		if (!ft_strncmp_p((char *)list->content, "&&", 2)
			|| !ft_strncmp_p((char *)list->content, "||", 2)
			|| !ft_strncmp_p((char *)list->content, "(", 1)
			|| !ft_strncmp_p((char *)list->content, ")", 1))
		{
			ft_print_syntax_error_message((char *)list->content);
			return (0);
		}
		list = list->next;
	}
	ft_dollar_variable_converter(list);
	ft_join_str_tokenizer(list);
	return (1);
}*/

int	ft_check_redirections(t_list *list)
{
	while (list)
	{
		if ((*(char *)list->content == '>' || *(char *)list->content == '<')
			&& (!list->next || *(char *)list->next->content != '"'))
		{
			ft_print_syntax_error_message((char *)list->content);
			return (0);
		}
		list = list->next;
	}
	return (1);
}

void	ft_join_redirections(t_list *list)
{
	char	*tmp;
	t_list	*tmp_list;

	while (list)
	{
		if (*(char *)list->content == '>' || *(char *)list->content == '<')
		{
			tmp = (char *)list->next->content;
			list->next->content = ft_substr_ae(tmp, 1, ft_strlen_p(tmp) - 2);
			ft_free_alloc(tmp);
			tmp = ft_alloc_lst(ft_strlen_p((char *)list->content)
					+ ft_strlen_p((char *)list->next->content) + 3, 3);
			sprintf(tmp, "\"%s%s\"", (char *)list->content, (char *)list->next->content);
			ft_free_alloc(list->content);
			list->content = tmp;
			tmp_list = list->next;
			list->next = list->next->next;
			ft_free_alloc(tmp_list->content);
			ft_free_alloc(tmp_list);
		}
		list = list->next;
	}
}

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

t_list	*ft_split_tokenizer_lst(char *str)
{
	t_list	*list;
	int		i;
	int		start;

	list = NULL;
	i = 0;
	start = 0;
	while (str[i])
	{
		if (!ft_split_tokenizer_lst_while(str, &list, &i, &start))
			return (NULL);
	}
	if (i - start)
		ft_lstadd_back(&list, ft_lstnew_ae
			(ft_substr_ae(str, start, i - start)));
	put_quotes(list);
	if (!ft_check_token_list(list))
	{
		ft_free_alloc_lst_clear(&list, ft_free_alloc);
		return (NULL);
	}
	//ft_remove_spaces(&list);
	return (list);
}

int main()
{
	t_list *list;
	char *line;

	//line = ft_input("minishell$ ");
	line = readline("minishell$ ");
	add_history(line);
	while(line)
	{
		list = ft_split_tokenizer_lst(line);
		if (list)
			ft_print(list);
		free(line);		
		//line = ft_input("minishell$ ");
		line = readline("minishell$ ");
		if (!ft_strncmp_p(line, "exit", 4))
			break;
		add_history(line);
	}
	free(line);
	rl_clear_history();
	ft_alloc_lst(0,0);
	return (0);
}
